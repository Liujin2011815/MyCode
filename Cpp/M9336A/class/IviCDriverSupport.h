//-----------------------------------------------------------------------------
// IviCDriverSupport.h contains the common definitions, variables, and
// methods used to implement IVI-C (as part of IVI NET/C, not IVI COM/C).
//
// This file is normally included by Driver.cpp with:
//
//    typedef KtCornerstoneDriverSession* DriverSessionPtr;
//    #define ASSEMBLY_PATH_KEY "SOFTWARE\\Keysight\\Cornerstone"
//    #define ASSEMBLY_PATH_VALUE "AssemblyPath"
//    #define FUNDAMENTAL_ASSEMBLY_NAME "KtCornerstoneFundamental"
//    #define NOT_INITIALIZED_ERROR KTCORNERSTONE_ERROR_NOT_INITIALIZED
//    #include "..\..\..\..\software-core\include\IviCDriverSupport.h"
//
// The Truss Kits already use this for the *Driver projects -- so no action
// required if you cloned a Truss Kit.
//-----------------------------------------------------------------------------
#pragma once

using namespace System::Text::RegularExpressions;
using namespace Keysight::ModularInstruments::Core::Utility;

// Forward references...

/// <summary>
/// Translate a fundamental reported error number ((COMException)ex.ErrorCode) to the
/// corresponding IVI-C error.
/// </summary>
/// <param name="ex">the exception that defines/contains the error</param>
/// <param name="defaultError">the error to report if ((COMException)ex.ErrorCode) is not recognized</param>
/// <remarks>
/// The fundamental error code definitions (in ModularErrorEnums.cs) originally tracked the IVI-COM
/// error definitions from early projects (Mundaka). Unfortunately the IVI-C error numbers did not
/// exactly match the IVI-COM and, even worse, when we copied the error enums between projects Nimbus(?)
/// did not preserve the IVI-C error numbers ... as a result almost none of the existing projects have
/// the same IVI-C error numbers and those don't match IVI-COM.  The result is we must translate the
/// error number instead of simply casting them.
/// </remarks>
ViStatus TranslateFundamentalErrorToIviCError(Exception^ ex, ViStatus defaultError);

/// <summary>
/// IsLinkedAssembly identifies if 'shortName' identifies an assembly that is linked into
/// the fundamental assembly during obfuscation.  This is required to redirect requests
/// for the original assembly to the linked assembly (e.g. Keysight.ModularInstruments.Core
/// is satisfied by KtCornstoneFundamental)
/// </summary>
/// <param name="shortName">the short name of the assembly, e.g. Keysight.ModularInstruments.Core</param>
/// <returns>true if shortName describes one of the assemblies linked into the fundamental</returns>
bool IsLinkedAssembly(String^);

// Useful macros...
#define TrySession(method) \
    const char * METHOD = method; \
    try { \
        DriverSessionPtr pSession; \
	    auto status = GetDriverSession(Vi, &pSession); \
        ReturnOnError(status);

#define TryInstrument(method) \
    const char * METHOD = method; \
    try { \
        IInstrument^ pInstrument; \
	    auto status = GetInstrument(Vi, pInstrument); \
        ReturnOnError(status);

#define TryPrimaryModule(method) \
    const char * METHOD = method; \
    try { \
        IModule^ pModule; \
	    auto status = GetPrimaryModule(Vi, pModule); \
        ReturnOnError(status);

#define TryPrimaryModuleService(method) \
    const char * METHOD = method; \
    try { \
        IModuleService^ pService; \
	    auto status = GetPrimaryModuleService(Vi, pService); \
        ReturnOnError(status);

#define CatchException(error, method)	\
        status = PollInstrumentErrors(Vi); \
        return status; \
    } catch (Exception^ ex) { return ReportException(Vi, error, ex, method); }

#define CatchExceptionNoPoll(error, method)	\
        return status; \
    } catch (Exception^ ex) { return ReportException(Vi, error, ex, method); }


/// <summary>
/// GetInstrument retrieves the IInstrument^ associated with the driver session, Vi
/// </summary>
/// <param name="Vi">session handle</param>
/// <param name="pInstrument"></param>
/// <returns>VI_SUCCESS if no errors</returns>
static ViStatus GetInstrument(ViSession Vi, IInstrument^ & pInstrument )
{
    DriverSessionPtr pSession = nullptr;
    auto status = GetDriverSession(Vi, &pSession);

    if (status != VI_SUCCESS || pSession == nullptr)
    {
        return ReportErrorEx(Vi, NOT_INITIALIZED_ERROR, "Failed to retrieve driver session.");
    }

    pInstrument = pSession->GetInstrument();
    if (pInstrument == nullptr)
    {
        return ReportErrorEx(Vi, NOT_INITIALIZED_ERROR, "Failed to retrieve driver (instrument).");
    }
    return status;
}

/// <summary>
/// GetPrimaryModule retrieves the IModule^ associated with the driver session, Vi
/// </summary>
/// <param name="Vi">session handle</param>
/// <param name="pModule"></param>
/// <returns>VI_SUCCESS if no errors</returns>
static ViStatus GetPrimaryModule(ViSession Vi, IModule^ & pModule )
{
    DriverSessionPtr pSession = nullptr;
    auto status = GetDriverSession(Vi, &pSession);

    if (status != VI_SUCCESS || pSession == nullptr)
    {
        return ReportErrorEx(Vi, NOT_INITIALIZED_ERROR, "Failed to retrieve driver session.");
    }

    pModule = pSession->GetPrimaryModule();
    if (pModule == nullptr)
    {
        return ReportErrorEx(Vi, NOT_INITIALIZED_ERROR, "Failed to retrieve driver (module).");
    }
    return status;
}

/// <summary>
/// GetPrimaryModuleService retrieves the IModuleService^ associated with the driver session, Vi
/// </summary>
/// <param name="Vi">session handle</param>
/// <param name="pService"></param>
/// <returns>VI_SUCCESS if no errors</returns>
static ViStatus GetPrimaryModuleService(ViSession Vi, IModuleService^ & pService )
{
    DriverSessionPtr pSession = nullptr;
    auto status = GetDriverSession(Vi, &pSession);

    if (status != VI_SUCCESS || pSession == nullptr)
    {
        return ReportErrorEx(Vi, NOT_INITIALIZED_ERROR, "Failed to retrieve driver session.");
    }

    pService = pSession->GetPrimaryModuleService();
    if (pService == nullptr)
    {
        return ReportErrorEx(Vi, NOT_INITIALIZED_ERROR, "Failed to retrieve driver (module).");
    }
    return status;
}

/// <summary>
/// GetSfp retrieves the ILiveSfp^ associated with the driver session, Vi
/// </summary>
/// <param name="Vi">session handle</param>
/// <param name="pSfp"></param>
/// <returns>VI_SUCCESS if no errors</returns>
static ViStatus GetSfp(ViSession Vi, Keysight::ModularInstruments::Common::Sfp::ILiveSfp^ & pSfp )
{
    DriverSessionPtr pSession = nullptr;
    auto status = GetDriverSession(Vi, &pSession);

    if (status != VI_SUCCESS || pSession == nullptr)
    {
        return ReportErrorEx(Vi, NOT_INITIALIZED_ERROR, "Failed to retrieve driver session.");
    }

    pSfp = pSession->GetSfp();

    // NOTE: pSfp == nullptr is not an error ... just indicates the user hasn't opened the Live SFP yet
    //if (pSfp == nullptr)
    //{
    //    return ReportErrorEx(Vi, NOT_INITIALIZED_ERROR, "Failed to retrieve driver (sfp).");
    //}
    return status;
}

/// <summary>
/// Report the error and message from an exception via ReportErrorEx().
/// </summary>
/// <param name="Vi">session handle</param>
/// <param name="errorNumber">error identifier ... should correspond to a value from the IVI-C Designer Error Enum</param>
/// <param name="message">the message extracted from the exception ... supplied as 'strElaboration' to ReportErrorEx</param>
/// <param name="...">values used by the formatting message associated with errorNumber</param>
/// <remarks>
/// The parameters supplied in the varargs (...) MUST satisfy the formatting message associated
/// with errorNumber otherwise a memory access violation may occur.
/// </remarks>
static ViStatus ReportExceptionEx(ViSession Vi, ViStatus errorNumber, std::string message, ...)
{
    DriverSession* pSession = nullptr;
    auto status = GetDriverSession(Vi, &pSession);
    assert(pSession != nullptr  && "Failed to retrieve driver session.");

    if (status == VI_SUCCESS && pSession != nullptr)
    {
        va_list argList;
        va_start(argList, message);
        status = pSession->ReportErrorEx( errorNumber, message, argList );
        va_end(argList);
    }
    return status;
}

/// <summary>
/// Report an exception.  This will translate the error identified by the exception to the
/// IVI-C equivalent then call ReportExceptionEx.
/// </summary>
/// <param name="Vi">session handle</param>
/// <param name="defaultError">the error to report of ex.ErrorCode is not recognized</param>
/// <param name="ex">the exception to report</param>
/// <remarks>
/// There are several signatures of ReportException instead of using varargs because
/// a signature with both generic parameters (Exception^) and varargs (...) is invalid.
/// </remarks>
static ViStatus ReportException(ViSession Vi, ViStatus defaultError, Exception^ ex)
{
    ViStatus error = TranslateFundamentalErrorToIviCError(ex, defaultError);
    // To minimize the chance of crashing if the developer didn't supply the arguments
    // required by the formatting of error, supply additional arguments ("").
    return ReportExceptionEx(Vi, error, marshal_as<std::string>(ex->Message), "", "", "", "");
}

/// <summary>
/// Report an exception.  This will translate the error identified by the exception to the
/// IVI-C equivalent then call ReportExceptionEx.
/// </summary>
/// <param name="Vi">session handle</param>
/// <param name="defaultError">the error to report of ex.ErrorCode is not recognized</param>
/// <param name="ex">the exception to report</param>
/// <param name="method">typically method name ... actual use depends on formatting of error</param>
/// <remarks>
/// There are several signatures of ReportException instead of using varargs because
/// a signature with both generic parameters (Exception^) and varargs (...) is invalid.
/// </remarks>
static ViStatus ReportException(ViSession Vi, ViStatus defaultError, Exception^ ex, LPCSTR method)
{
    ViStatus error = TranslateFundamentalErrorToIviCError(ex, defaultError);
    // To minimize the chance of crashing if the developer didn't supply the arguments
    // required by the formatting of error, supply additional arguments ("").
    return ReportExceptionEx(Vi, error, marshal_as<std::string>(ex->Message), method, "", "", "");
}

/// <summary>
/// Report an exception.  This will translate the error identified by the exception to the
/// IVI-C equivalent then call ReportExceptionEx.
/// </summary>
/// <param name="Vi">session handle</param>
/// <param name="defaultError">the error to report of ex.ErrorCode is not recognized</param>
/// <param name="ex">the exception to report</param>
/// <param name="parameter">typically parameter name ... actual use depends on formatting of error</param>
/// <param name="method">typically method name ... actual use depends on formatting of error</param>
/// <remarks>
/// There are several signatures of ReportException instead of using varargs because
/// a signature with both generic parameters (Exception^) and varargs (...) is invalid.
/// </remarks>
static ViStatus ReportException(ViSession Vi, ViStatus defaultError, Exception^ ex, LPCSTR parameter, LPCSTR method)
{
    ViStatus error = TranslateFundamentalErrorToIviCError(ex, defaultError);
    // To minimize the chance of crashing if the developer didn't supply the arguments
    // required by the formatting of error, supply additional arguments ("").
    return ReportExceptionEx(Vi, error, marshal_as<std::string>(ex->Message), parameter, method, "", "");
}

/// <summary>
/// Report an exception.  This will translate the error identified by the exception to the
/// IVI-C equivalent then call ReportExceptionEx.
/// </summary>
/// <param name="Vi">session handle</param>
/// <param name="defaultError">the error to report of ex.ErrorCode is not recognized</param>
/// <param name="ex">the exception to report</param>
/// <param name="parameter">typically parameter name ... actual use depends on formatting of error</param>
/// <param name="value">typically parameter value ... actual use depends on formatting of error</param>
/// <param name="method">typically method name ... actual use depends on formatting of error</param>
/// <remarks>
/// There are several signatures of ReportException instead of using varargs because
/// a signature with both generic parameters (Exception^) and varargs (...) is invalid.
/// </remarks>
static ViStatus ReportException(ViSession Vi, ViStatus defaultError, Exception^ ex, LPCSTR parameter, LPCSTR value, LPCSTR method)
{
    ViStatus error = TranslateFundamentalErrorToIviCError(ex, defaultError);
    // To minimize the chance of crashing if the developer didn't supply the arguments
    // required by the formatting of error, supply additional arguments ("").
    return ReportExceptionEx(Vi, error, marshal_as<std::string>(ex->Message), parameter, value, method, "");
}

/// <summary>
/// Report an exception.  This will translate the error identified by the exception to the
/// IVI-C equivalent then call ReportExceptionEx.
/// </summary>
/// <param name="Vi">session handle</param>
/// <param name="defaultError">the error to report of ex.ErrorCode is not recognized</param>
/// <param name="ex">the exception to report</param>
/// <param name="one">passed to ReportExceptionEx as 1st vararg parameter</param>
/// <param name="two">passed to ReportExceptionEx as 2nd vararg parameter</param>
/// <param name="three">passed to ReportExceptionEx as 3rd vararg parameter</param>
/// <param name="four">passed to ReportExceptionEx as 4th vararg parameter</param>
/// <remarks>
/// There are several signatures of ReportException instead of using varargs because
/// a signature with both generic parameters (Exception^) and varargs (...) is invalid.
/// </remarks>
static ViStatus ReportException(ViSession Vi, ViStatus defaultError, Exception^ ex, LPCSTR one, LPCSTR two, LPCSTR three, LPCSTR four)
{
    ViStatus error = TranslateFundamentalErrorToIviCError(ex, defaultError);
    return ReportExceptionEx(Vi, error, marshal_as<std::string>(ex->Message), one, two, three, four);
}

// mIsResolverRegistered indicates if ResolveAssembly has been registered...
static bool mIsResolverRegistered = false;

/// <summary>
/// ResolveAssembly is called when .NET needs a helping hand finding an assembly
/// that has already been loaded.  This usually happens because the object was
/// serialized with a different version of the assembly.
/// 
/// Usage...
///    try {
///      AppDomain.CurrentDomain.AssemblyResolve += Support.ResolveAssembly;
///      // ... deserialize...
///    }
///    finally { AppDomain.CurrentDomain.AssemblyResolve -= Support.ResolveAssembly; }
/// 
/// </summary>
/// <param name="sender"></param>
/// <param name="args"></param>
/// <returns></returns>
System::Reflection::Assembly^ ResolveAssembly(Object^ Sender, ResolveEventArgs^ args)
{
    array<System::Reflection::Assembly^, 1>^ assemblies = AppDomain::CurrentDomain->GetAssemblies();

    // First, look for exact match with already loaded assembly
    for each(System::Reflection::Assembly^ assembly in assemblies)
    {
        if (args->Name->Equals(assembly->FullName, StringComparison::InvariantCultureIgnoreCase))
        {
            return assembly;
        }
    }

    // It is possible the caller only specified the name ... so don't count on version being non-null!
    array<String^, 1>^ requestedDetails = args->Name->Split(',');
    String^ requestedShortName = requestedDetails[0];
    String^ requestedVersion = (requestedDetails->Length > 1) ? requestedDetails[1] : String::Empty;

    // If we're in the development environment, ignore the requested version
    String^ path = System::IO::Path::GetDirectoryName(System::Reflection::Assembly::GetExecutingAssembly()->Location);
    if( ! String::IsNullOrEmpty( path ) &&
        Regex::IsMatch( path, "(Debug|Release|Test)", RegexOptions::CultureInvariant | RegexOptions::IgnoreCase ) )
    {
        requestedVersion = String::Empty;
    }

    // Next, look for a partial match with already loaded assembly. Name must always match. If
    // the caller specified a verison, that must match too!
    for each(System::Reflection::Assembly^ assembly in assemblies)
	{
		array<String^, 1>^ details = assembly->FullName->Split(',');
        if (requestedShortName->Equals(details[0], StringComparison::InvariantCultureIgnoreCase) &&
            (String::IsNullOrEmpty(requestedVersion) || requestedVersion->Equals(details[1], StringComparison::InvariantCultureIgnoreCase)))
		{
			return assembly;
		}
	}

    // Try LoadFrom( path of executing assembly )
	try
	{
        String^ filepath = String::Format(marshal_as<String^>("{0}\\{1}.dll"), path, requestedShortName);
        if (System::IO::File::Exists(filepath))
        {
            // Load the assembly ... but, if the version was specified, only return it
            // if the version also matches
            System::Reflection::Assembly^ candidate = System::Reflection::Assembly::LoadFrom(filepath);
            if (String::IsNullOrEmpty(requestedVersion) || candidate->FullName->Equals(args->Name, StringComparison::InvariantCultureIgnoreCase))
            {
                return candidate;
            }
        }
	}
	catch (Exception^ ex)
	{
	}

    // Try LoadFrom( well known locations )
    try
    {
        Microsoft::Win32::RegistryKey^ key = Microsoft::Win32::Registry::LocalMachine->OpenSubKey(marshal_as<String^>(ASSEMBLY_PATH_KEY));
        if (key != nullptr)
        {
            Object^ value = key->GetValue(marshal_as<String^>(ASSEMBLY_PATH_VALUE));
            if (value != nullptr)
            {
                array<String^,1>^ locations = String::Format( marshal_as<String^>("{0}"), value )->Split( ',' );
                int n = locations->GetLength( 0 );
                for( int j = 0; j < n; j++ )
                {
                    String^ filepath = String::Format(marshal_as<String^>("{0}\\{1}.dll"), locations[j], requestedShortName);
                    // Load the assembly ... but, if the version was specified, only return it
                    // if it is a perfect match
                    if( System::IO::File::Exists( filepath ) )
                    {
                        System::Reflection::Assembly^ candidate = System::Reflection::Assembly::LoadFrom(filepath);
                        if (String::IsNullOrEmpty(requestedVersion) || candidate->FullName->Equals(args->Name, StringComparison::InvariantCultureIgnoreCase))
                        {
                            return candidate;
                        }
                    }
                }
            }
        }
    }
    catch (Exception^ ex)
    {
    }

    // If all of the above have failed, check for the special case of assemblies that were linked into
    // KtCornerstoneFundamental as part of Obfuscation and return the fundamental assembly instead
    try
    {
        if ( ! String::IsNullOrEmpty(requestedVersion) && IsLinkedAssembly(requestedShortName))
        {
            String^ fundamentalName = FUNDAMENTAL_ASSEMBLY_NAME;
            String^ fundamentalFullName = args->Name->Replace( requestedShortName, fundamentalName );
            for each(System::Reflection::Assembly^ assembly in assemblies)
            {
                if (fundamentalFullName->Equals( assembly->FullName, StringComparison::InvariantCultureIgnoreCase ))
                {
                    return assembly;
                }
            }
        }
                    
    }
    catch (Exception^ ex)
    {
    }

    // If all of the above have failed, check for the special case of a renamed CommonSFP
    try
    {
        if ( String::IsNullOrEmpty(requestedVersion) /* only if don't care about version */ &&
            Regex::IsMatch( requestedShortName, "\\.CommonSFP$", RegexOptions::CultureInvariant | RegexOptions::IgnoreCase ) )
        {
            return ResolveAssembly( Sender, gcnew ResolveEventArgs( "CommonSFP", args->RequestingAssembly ) );
        }                    
    }
    catch (Exception^ ex)
    {
    }

    return nullptr;
}
