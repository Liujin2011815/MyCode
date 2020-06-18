///////////////////////////////////////////////////////////////////////////////
//
//	This file defines the driver session class that is instantiated each time
//	the driver is initialized. 
//
#pragma once

#include <tchar.h>
#include <vcclr.h>
#include <msclr\marshal.h>
#include <msclr/marshal_cppstd.h>

using namespace nrt;
using namespace System;
using namespace Keysight::ModularInstruments;
using namespace Keysight::ModularInstruments::KtMAwg::API;
using namespace msclr::interop;

/// <summary>
/// This text must match between InitializeFundamental and IKtMAwgSystemSFP_Open
/// </summary>
/// <remarks>
/// Session.DriverSetup stores the keys as lower case in a case-sensitive dictionary.
/// The user can use any casing, but the lookups must be all lower case.
/// </remarks>
#define REQUESTED_INSTANCE_ID "requestedinstanceid"

/// <summary>
/// Driver open to automatically open LiveSFP after initializing the driver
/// </summary>
/// <remarks>
/// Session.DriverSetup stores the keys as lower case in a case-sensitive dictionary.
/// The user can use any casing, but the lookups must be all lower case.
/// </remarks>
#define AUTO_OPEN_SFP "opensfp"

class KtMAwgDriverSession : public nrt::DriverSession
{
private:
	gcroot<IInstrument^> mpInstrument;
    gcroot<IMAwg^> mpFundamental;
    gcroot<IModule^> mpPrimaryModule;
    gcroot<IModuleService^> mpPrimaryModuleService;
    gcroot<Keysight::ModularInstruments::Common::Sfp::ILiveSfp^> mpSfp;
    gcroot<Keysight::ModularInstruments::Common::Sfp::ILiveSfpFactory^> mpSfpFactory;
    bool mAutoOpenSfp;
    bool mSfpAutoRefreshEnabled;
    double mSfpRefreshPeriod;
    bool mSfpControlsEnabled;
	bool mIsArbitraryMode;
	bool mIsMarkerInitialized;
	bool mIsSequenceTriggerInitialized;


    /// <summary>
    /// mIsInstrumentOwner is used to indicate that this IVI driver instance is reusing
    /// another driver's instrument (typically for LiveSFP) and this driver should NOT
    /// close the instrument when disconnecting
    /// </summary>
    bool mIsInstrumentOwner;
    std::string mModuleList;

    /// <summary>
    /// Creation of the Fundamental objects
    /// </summary>
	ViStatus InitializeFundamental()
	{
        // Get the resource descriptor.. If the user specified an IVI Logical Name, Nimbus has
        // extracted the resource descriptor from the IVI Configuration Store.  NOTE: unlike
        // Hyper & Apogee, the module/instrument factory only accepts VISA address(es) so there
        // is no need to check the Logical Name (VISA address includes VISA aliases).
        LPCTSTR systemName = ResourceName().c_str();

        mpInstrument = nullptr;
        mpFundamental = nullptr;
        mpSfpFactory = nullptr;
        mpSfp = nullptr;
        mAutoOpenSfp = false;
        mSfpAutoRefreshEnabled = false;
        mSfpRefreshPeriod = 1.0;
        mSfpControlsEnabled = true;
		mIsArbitraryMode = true;
		mIsMarkerInitialized = false;
		mIsSequenceTriggerInitialized = false;

        // We need the factory for both finding existing instruments as well as creating new ones
		IInstrumentFactory^ pFactory = gcnew Keysight::ModularInstruments::KtMAwg::InstrumentFactory();
		//IInstrumentFactory^ pFactory = gcnew Keysight::ModularInstruments::KtMAwg::MAwgModule(1);

        // Special option to identify fundamental for LiveSFP (or other Fundamental reuse mechanisms)
        std::string key = REQUESTED_INSTANCE_ID;
        std::string value;
        if( GetDriverSetupOption( key, value ) )
        {
            int requestedInstanceId;
            if( _stscanf_s( value.c_str(), "%d", &requestedInstanceId ) == 1 )
            {
                // Of course the id must exist... (if it doesn't, mInstrument will be null and
                // we'll just fall into the normal handling and the user will get an error).
                mpInstrument = pFactory->Find( requestedInstanceId );
                mIsInstrumentOwner = false;
            }
        }

        if( static_cast<IInstrument^>(mpInstrument) == nullptr )
        {
            // NOTE: we used to explicitly list the keys and ask Nimbus for each value. Although this
            //       created a convenient place to list all the recognized keys, the real reason was
            //       because we hadn't figured out how to get everything following "DriverWrapper=".
            //       This is now available from DriverSetup so there is no longer a need to explicitly
            //       list the keys. Everything *after* "DriverSetup=" is passed to the fundamental
        	mpInstrument = pFactory->Create(marshal_as<String^>(systemName), SimulationEnabled(), marshal_as<String^>(DriverSetup().c_str()));
            mIsInstrumentOwner = true;
            key = AUTO_OPEN_SFP;
            if( GetDriverSetupOption( key, value ) )
            {
                std::transform(value.begin(), value.end(), value.begin(), ::tolower);
                mAutoOpenSfp = value == "1" || value == "true";
            }
        }

        // Some initialization for both reused and created fundamentals
        if( static_cast<IInstrument^>(mpInstrument) != nullptr )
        {
            // Figure out what the instrument is ... (cast to IInstrument^ is required because mpInstrument is wrapped with gcroot)
            mpFundamental = dynamic_cast<IMAwg^>( (IInstrument^)mpInstrument );

            // Cache a list of modules (for use in methods such as GetClockGenerator(), GetDynamicRepCapNames(), etc.)
            mModuleList = marshal_as<std::string>( mpInstrument->GetModules() );

            mpPrimaryModule = mpInstrument->GetModule(nullptr);
            mpPrimaryModuleService = mpInstrument->GetModuleService(nullptr);
        }

		return IVIC_SUCCESS;
	}

    /// <summary>
    /// Close the instrument (if any) and release any other Fundamental resources.
    /// </summary>
    ViStatus CloseFundamental()
    {
		if ( static_cast<IInstrument^>(mpInstrument) != nullptr )
		{
            // Only close the instrument if this driver created it (vs. pulling it from IInstrumentFactory.Find())
            if( mIsInstrumentOwner )
            {
                // Release the LiveSfp instance (which contains the Application running the message loop)
                if( static_cast<Keysight::ModularInstruments::Common::Sfp::ILiveSfp^>(mpSfp) != nullptr )
                {
                    mpSfp->Exit();
                    mpSfp = nullptr;
                    mpInstrument->LiveSfp = nullptr;
                }
                // Release the LiveSfpFactory instance (which manages the AppDomain)
                if( static_cast<Keysight::ModularInstruments::Common::Sfp::ILiveSfpFactory^>(mpSfpFactory) != nullptr )
                {
                    // Unload() unloads the AppDomain
                    mpSfpFactory->Unload( mpInstrument->UniqueId );
                    mpSfpFactory = nullptr;
                }

                // Tell the MAwg object to release resources prior to destruction,
                // this will force the equivalent of a Dispose on the object.
                mpInstrument->Close();
            }
		}
        // Clear cached references...
        mpInstrument = nullptr;
        mpFundamental = nullptr;
        mpSfpFactory = nullptr;
        mpSfp = nullptr;

		return IVIC_SUCCESS;
    }

public:
	KtMAwgDriverSession(ViSession handle)
		: DriverSession(handle, 2000, 2000, 2000, false, 1000)
		// DriverSession(handle, VisaOpenTimeuout, SelfTestTimeout, ResetTimeout, InterchangeCheckSupported (always false), CoercionLogSize)
	{
		mpInstrument = nullptr;
	}

	virtual ViStatus InitializeIO() override
	{
		auto strResource = ResourceName();

		// This function establishes an I/O connection with the instrument.  For VISA-based drivers, this function
		// performs the viOpen call on the specified resource.  For custom I/O, this function performs whatever
		// tasks are necessary to establish the I/O connection, such as initializing a helper DLL.

		return InitializeFundamental();
	}

	virtual ViStatus CloseIO() override
	{
		// This function closes the I/O connection with the instrument.  For VISA-based drivers, this function
		// performs the viClose call on the I/O connection.  For custom I/O, this function performs whatever
		// cleanup tasks are necessary to free up whatever resources are held by the custom I/O implementation.
		//

        return CloseFundamental();
	}

	virtual ViStatus ClearIOStatus() override
	{
		// This functions clears the status of the I/O connection to remove any errors that may have occurred before
		// the driver was initialized.  This improves the ability of the driver to initialize when the instrument
		// is already in an error state.  In 488.2-compliant devices, this function sends the *CLS command.

        // For modular systems, clear the error queue
        int code;
        String^ message;
        do
        {
            mpInstrument->ErrorQuery(code, message);
        } while (code != 0);

        return VI_SUCCESS;
	}

	virtual ViStatus GetIdentificationInfo(std::string& strManufacturer, std::string& strModel, std::string& strSerialNumber, std::string& strFirmwareRevision) override
	{
		// This function returns basic information about the instrument.  In 488.2-compliance devices, this function
		// parses the results of the *IDN? query.

        strManufacturer = "Keysight Technologies";
        strModel = marshal_as<std::string>(mpInstrument->ModelNumber);
        strSerialNumber = marshal_as<std::string>(mpInstrument->SerialNumber);
        strFirmwareRevision = marshal_as<std::string>(mpInstrument->FirmwareRevision);

        return VI_SUCCESS;
	}

	virtual ViStatus PollInstrumentErrors() override
	{
		if (!QueryInstrStatusEnabled())
		{
			// User has not enabled polling, so just return without doing anything.
			return VI_SUCCESS;
		}

		// This function queries the status system of the instrument to determine if an error occurred.  In 488.2-compliant
		// devices, this function performs a *ESR? query.

        // TODO: Most modular systems do not have an *ESR? equivalent (no way to peek at the error queue)
        //       If your system supports this, return IVIC_ERROR_INSTRUMENT_STATUS on any error
		// return IVIC_ERROR_INSTRUMENT_STATUS;
        return VI_SUCCESS;
	}

    IInstrument^ GetInstrument()
    {
        return mpInstrument;
    }

    IMAwg^ GetFundamental()
    {
        return mpFundamental;
    }

    IModule^ GetPrimaryModule()
    {
        return mpPrimaryModule;
    }

    IModuleService^ GetPrimaryModuleService()
    {
        return mpPrimaryModuleService;
    }

    Keysight::ModularInstruments::Common::Sfp::ILiveSfp^ GetSfp()
    {
        if( static_cast<Keysight::ModularInstruments::Common::Sfp::ILiveSfp^>(mpSfp) == nullptr )
        {
            if( static_cast<IInstrument^>(mpInstrument) != nullptr )
            {
                mpSfp = dynamic_cast<Keysight::ModularInstruments::Common::Sfp::ILiveSfp^>( mpInstrument->LiveSfp );
            }
        }
        return mpSfp;
    }

    void SetSfp(Keysight::ModularInstruments::Common::Sfp::ILiveSfp^ pSfp)
    {
        mpSfp = pSfp;
        mpInstrument->LiveSfp = pSfp;
    }

    Keysight::ModularInstruments::Common::Sfp::ILiveSfpFactory^ GetSfpFactory()
    {
        return mpSfpFactory;
    }

    void SetSfpFactory(Keysight::ModularInstruments::Common::Sfp::ILiveSfpFactory^ pFactory)
    {
        mpSfpFactory = pFactory;
    }

    bool GetAutoOpenSfp() { return mAutoOpenSfp; }

    void SetAutoOpenSfp(bool value) { mAutoOpenSfp = value; }

    bool GetSfpAutoRefreshEnabled() { return mSfpAutoRefreshEnabled; }

    void SetSfpAutoRefreshEnabled(bool value) { mSfpAutoRefreshEnabled = value; }

    double GetSfpRefreshPeriod() { return mSfpRefreshPeriod; }

    void SetSfpRefreshPeriod(double value) { mSfpRefreshPeriod = value; }

    bool GetSfpControlsEnabled() { return mSfpControlsEnabled; }

    void SetSfpControlsEnabled(bool value) { mSfpControlsEnabled = value; }

	bool GetIsArbitraryMode() { return mIsArbitraryMode; }

	void SetIsArbitraryMode(bool value) { mIsArbitraryMode = value; }

	bool GetIsMarkerInitialized() { return mIsMarkerInitialized; }

	void SetIsMarkerInitialized(bool value) { mIsMarkerInitialized = value; }

	bool GetIsSequenceTriggerInitialized() { return mIsSequenceTriggerInitialized; }

	void SetIsSequenceTriggerInitialized(bool value) { mIsSequenceTriggerInitialized = value; }

    bool IsInstrumentOwner() { return mIsInstrumentOwner; }
};

