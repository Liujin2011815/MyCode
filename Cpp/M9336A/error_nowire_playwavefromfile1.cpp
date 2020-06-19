
#include "stdafx.h"
#include <atlstr.h>
#include <ctime>
#include "KtMAwg.h"

	/**
	 * Òì³£ÍË³ö£¬KtMAwg_InitWithOptions³ö´í
	 */
	 
// Forward references
void catchError(char *routine, ViSession session, ViStatus status);


int _tmain(int argc, _TCHAR* argv[])
{
	ViStatus status, status2, status3;
	ViSession session;
	ViChar str[128];
	ViInt32 ErrorCode;
	ViChar ErrorMessage[256];
	ViBoolean simulate;
    ViChar resourceName[256];

	/**
	 * resourceName can changed to PXI15::0::0::INSTR ; PXI16::0::0::INSTR ; 
	 * They correspond to different boards.
     */
    strcpy_s(resourceName, sizeof(resourceName), "PXI16::0::0::INSTR");

	char* options = "Simulate=true, DriverSetup=Model=M9336A, Trace=false";

	if (argc > 1)
	{
        size_t converted;
		wcstombs_s(&converted, resourceName, sizeof(resourceName), argv[1], sizeof(resourceName));
    	options  = "Simulate=false, DriverSetup=UseLegacyV2RuntimeActivationPolicy=true, Model=M9336A, Trace=false";
	}

	ViBoolean idQuery = VI_TRUE;
	ViBoolean reset   = VI_TRUE;

	printf("  C_Example1\n\n");
    printf("\tRuns in simulated mode if no command line parameter is provided.\n");
    printf("\tRun with resource string argument to use hardware.\n\n");

	// Initialize the driver with options 
	status = KtMAwg_InitWithOptions(resourceName, idQuery, reset, options, &session);
	
	//
	status2 = KtMAwg_InitWithOptions(resourceName, idQuery, reset, options, &session);

	if (status || session == VI_NULL)
	{
		// Initialization failed
		KtMAwg_GetError(session, &ErrorCode, 255, ErrorMessage);
		printf("** InitWithOptions() Error: %d, %s\n", ErrorCode, ErrorMessage);
		printf("\nDone - Press Enter to Exit");
		getchar();
		return ErrorCode;
	}

	//
	if (status2 || session == VI_NULL)
	{
		// Initialization failed
		KtMAwg_GetError(session, &ErrorCode, 255, ErrorMessage);
		printf("** InitWithOptions() Error: %d, %s\n", ErrorCode, ErrorMessage);
		printf("\nDone - Press Enter to Exit");
		getchar();
		return ErrorCode;
	}

	printf("Driver Initialized \n");

	// Read and output a few attributes
	// Return status checking omitted for example clarity
	status = KtMAwg_GetAttributeViString(session, "", KTMAWG_ATTR_SPECIFIC_DRIVER_PREFIX, 127, str);
	catchError("KtMAwg_GetAttributeViString",session,status);
	printf("DRIVER_PREFIX:      %s\n", str);

	status = KtMAwg_GetAttributeViString(session, "", KTMAWG_ATTR_SPECIFIC_DRIVER_REVISION, 127, str);
	catchError("KtMAwg_GetAttributeViString",session,status);
	printf("DRIVER_REVISION:    %s\n", str);

	status = KtMAwg_GetAttributeViString(session, "", KTMAWG_ATTR_SPECIFIC_DRIVER_VENDOR, 127, str);
	catchError("KtMAwg_GetAttributeViString",session,status);
	printf("DRIVER_VENDOR:      %s\n", str);

	status = KtMAwg_GetAttributeViString(session, "", KTMAWG_ATTR_SPECIFIC_DRIVER_DESCRIPTION, 127, str);
	catchError("KtMAwg_GetAttributeViString",session,status);
	printf("DRIVER_DESCRIPTION: %s\n", str);

	status = KtMAwg_GetAttributeViString(session, "", KTMAWG_ATTR_INSTRUMENT_MODEL, 127, str);
	catchError("KtMAwg_GetAttributeViString",session,status);
	printf("INSTRUMENT_MODEL:   %s\n", str);

	status = KtMAwg_GetAttributeViString(session, "", KTMAWG_ATTR_INSTRUMENT_FIRMWARE_REVISION, 127, str);
	catchError("KtMAwg_GetAttributeViString",session,status);
	printf("FIRMWARE_REVISION:  %s\n", str);

	status = KtMAwg_GetAttributeViString(session, "", KTMAWG_ATTR_SERIAL_NUMBER, 127, str);
	catchError("KtMAwg_GetAttributeViString",session,status);
	printf("SERIAL_NUMBER:      %s\n", str);

	status = KtMAwg_GetAttributeViBoolean(session, "", KTMAWG_ATTR_SIMULATE, &simulate);
	catchError("KtMAwg_GetAttributeViBoolean",session,status);
	if (simulate == VI_TRUE)
		printf("\nSIMULATE:           True\n\n");
	else
		printf("SIMULATE:           False\n\n");


	// Play a waveform from a file

	// Specify the channel we'll play the waveform on. It can be Channel1 , Channel2 , Channel3 .
	char channelName[20];
	char channelName2[20];
	char channelName3[20];
	strncpy_s(channelName, "Channel1", 20);	
	strncpy_s(channelName2, "Channel2", 20);
	strncpy_s(channelName3, "Channel3", 20);

	// Specify the file path
	char sineWaveformFilePath[200];
	strncpy_s(sineWaveformFilePath,"C:\\Users\\Administrator\\Desktop\\C++example\\KtMAwg_Cpp_PlayWaveformFromFile\\Qam16_60M_Center_80M_Symbol.csv", 200);

	// Create the waveform on all channels by setting second parameter to an empty string
	ViInt32 sineWaveformHandle;
	status = KtMAwg_WaveformCreateChannelWaveformFromFile(session, "", "SineWaveform", 0, sineWaveformFilePath, &sineWaveformHandle);
	catchError("KtMAwg_WaveformCreateChannelWaveformFromFile", session, status);
	
	//
	status2 = KtMAwg_WaveformCreateChannelWaveformFromFile(session, "", "SineWaveform2", 0, sineWaveformFilePath, &sineWaveformHandle);
	catchError("KtMAwg_WaveformCreateChannelWaveformFromFile", session, status2);

	//configure the output
	status = KtMAwg_ConfigureOperationMode(session, channelName, KTMAWG_VAL_OPERATE_CONTINUOUS);
	catchError("KtMAwg_ConfigureOperationMode", session, status);
	
	status = KtMAwg_OutputSetTerminalConfiguration(session, channelName, KTMAWG_VAL_TERMINAL_CONFIGURATION_DIFFERENTIAL);
	catchError("KtMAwg_OutputSetTerminalConfiguration", session, status);
	
	status = KtMAwg_ConfigureOutputEnabled(session, channelName, VI_TRUE);
	catchError("KtMAwg_ConfigureOutputEnabled", session, status);

	status = KtMAwg_ArbitrarySetHandle(session, channelName, sineWaveformHandle);
	catchError("KtMAwg_ArbitrarySetHandle", session, status);

	//
	status2 = KtMAwg_ConfigureOperationMode(session, channelName2, KTMAWG_VAL_OPERATE_CONTINUOUS);
	catchError("KtMAwg_ConfigureOperationMode", session, status2);

	status2 = KtMAwg_OutputSetTerminalConfiguration(session, channelName2, KTMAWG_VAL_TERMINAL_CONFIGURATION_DIFFERENTIAL);
	catchError("KtMAwg_OutputSetTerminalConfiguration", session, status2);

	status2 = KtMAwg_ConfigureOutputEnabled(session, channelName2, VI_TRUE);
	catchError("KtMAwg_ConfigureOutputEnabled", session, status2);

	status2 = KtMAwg_ArbitrarySetHandle(session, channelName2, sineWaveformHandle);
	catchError("KtMAwg_ArbitrarySetHandle", session, status2);

	// Generation Settings Restrictions Enabled
	status = KtMAwg_EnableGenerationSettingsRestrictions(session);
	catchError("KtMAwg_EnableGenerationSettingsRestrictions", session, status);

	//
	status2 = KtMAwg_EnableGenerationSettingsRestrictions(session);
	catchError("KtMAwg_EnableGenerationSettingsRestrictions", session, status2);

	// Configure the SampleRate
	status = KtMAwg_ConfigureSampleRate(session, 1200000000);		// The unit is Sa/s
	catchError("KtMAwg_ConfigureSampleRate", session, status);

	//
	status2 = KtMAwg_ConfigureSampleRate(session, 1200000000);		// The unit is Sa/s
	catchError("KtMAwg_ConfigureSampleRate", session, status2);

	// Configure the Crrection Filter Mode
	status = KtMAwg_CorrectionsSetFilterMode(session, channelName, KTMAWG_VAL_CORRECTION_FILTER_MODE_CALIBRATED);
	catchError("KtMAwg_CorrectionsSetFilterMode", session, status);

	//
	status2 = KtMAwg_CorrectionsSetFilterMode(session, channelName2, KTMAWG_VAL_CORRECTION_FILTER_MODE_CALIBRATED);
	catchError("KtMAwg_CorrectionsSetFilterMode", session, status2);


	// Set gain mode 
	status = KtMAwg_ArbitrarySetGainControl(session, channelName, KTMAWG_VAL_GAIN_CONTROL_COMPOSITE);
	catchError("KTMAWG_VAL_GAIN_CONTROL_COMPOSITE", session, status);

	//
	status2 = KtMAwg_ArbitrarySetGainControl(session, channelName, KTMAWG_VAL_GAIN_CONTROL_COMPOSITE);
	catchError("KTMAWG_VAL_GAIN_CONTROL_COMPOSITE", session, status2);

	// set gain value
	status = KtMAwg_ArbitrarySetGain(session, channelName, 0.6);
	catchError("KtMAwg_ArbitrarySetGain", session, status);

	//
	status2 = KtMAwg_ArbitrarySetGain(session, channelName2, 0.6);
	catchError("KtMAwg_ArbitrarySetGain", session, status2);


	// set gain mode
	// status = KtMAwg_SetAttributeViReal64(session, channelName, KTMAWG_ATTR_ARB_GAIN, 0.5);


	// set delay
	status = KtMAwg_OutputSetDelay(session, channelName, 0);
	catchError("KtMAwg_OutputSetDelay", session, status);

	//
	status2 = KtMAwg_OutputSetDelay(session, channelName2, 0);
	catchError("KtMAwg_OutputSetDelay", session, status2);

	// initial generation
	status = KtMAwg_InitiateGeneration(session);
	catchError("KtMAwg_InitiateGeneration", session, status);

	//
	status2 = KtMAwg_InitiateGeneration(session);
	catchError("KtMAwg_InitiateGeneration", session, status2);

	// Output Enabled
	status = KtMAwg_ConfigureOutputEnabled(session, channelName, VI_TRUE);
	catchError("KtMAwg_ConfigureOutputEnabled", session, status);

	//
	status2 = KtMAwg_ConfigureOutputEnabled(session, channelName2, VI_TRUE);
	catchError("KtMAwg_ConfigureOutputEnabled", session, status2);

	//status = KtMAwg_SetAttributeViReal64(session, channelName, KTMAWG_ATTR_ARB_GAIN, KTMAWG_VAL_GAIN_CONTROL_COMPOSITE);
	//catchError("KtMAwg_SetAttributeViReal64", session, status);


	// Resolve any settings conflicts and call Apply to push the new settings to the module
	status = KtMAwg_Resolve(session);
	catchError("KtMAwg_Resolve", session, status);

	status = KtMAwg_Apply(session);
	catchError("KtMAwg_Apply", session, status);

	//
	status2 = KtMAwg_Resolve(session);
	catchError("KtMAwg_Resolve", session, status2);

	status2 = KtMAwg_Apply(session);
	catchError("KtMAwg_Apply", session, status2);

	// Play the waveform on channel 
	status = KtMAwg_InitiateGenerationByChannel(session, channelName);
	catchError("KtMAwg_InitiateGenerationByChannel", session, status);

	//
	status2 = KtMAwg_InitiateGenerationByChannel(session, channelName2);
	catchError("KtMAwg_InitiateGenerationByChannel", session, status2);

	printf("\nWaveform is currently generating - Press enter to abort generation and close the driver.");
	getchar();

	//Abort generation on channel 
	status = KtMAwg_AbortGenerationByChannel(session, channelName);
	catchError("KtMAwg_AbortGenerationByChannel", session, status);

	//
	status2 = KtMAwg_AbortGenerationByChannel(session, channelName2);
	catchError("KtMAwg_AbortGenerationByChannel", session, status2);

	// Close the driver
	status = KtMAwg_close(session);
	catchError("KtMAwg_close",session,status);

	//
	status2 = KtMAwg_close(session);
	catchError("KtMAwg_close", session, status2);

	session = VI_NULL;
	printf("Driver Closed \n");
	printf("\nDone - Press Enter to Exit");
	getchar();

	return 0;
}

void catchError(char *routine, ViSession session, ViStatus status)
{
    ViInt32 ErrorCode;
    ViChar ErrorMessage[256];

    // No error, just return
    if( status == VI_SUCCESS )
    {
        return;
    }

    // No session handle, will be impossible to query the driver for errors.
    if( session == VI_NULL )
    {
        printf( "** Error, Unable to query driver for errors, the VISA session is null.\n" );
        printf( "\nAbort - Press Enter to Exit" );
        getchar();
        exit(1);
    }

    KtMAwg_GetError(session, &ErrorCode, 255, ErrorMessage);
    printf( "** %s() Error: %d, %s\n", routine, ErrorCode, ErrorMessage);

    status = KtMAwg_close(session); // Try to close the driver session before exit. 
    if(status)
    {
        KtMAwg_GetError(session, &ErrorCode, 255, ErrorMessage);
        printf( "** %s() Error: %d, %s\n", routine, ErrorCode, ErrorMessage);
    }
    else
    {
        printf( "Driver Closed \n" );
    }

    printf( "\nAbort - Press Enter to Exit" );
    getchar();
    exit(1);
}