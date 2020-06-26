#include "stdafx.h"
#include "atlstr.h"
#include <ctime>
#include "KtMAwg.h"
#include <thread>

// 可以运行，运行时间9分35秒
void catchError(char *routine, ViSession session, ViStatus status);

void pxi16_1()
{
	ViStatus status2;
	ViSession session2;

	ViChar resourceName2[256];

	strcpy_s(resourceName2, sizeof(resourceName2), "PXI15::0::0::INSTR"); // Use the hardware associated with the connection

	char* options2 = "Simulate=false, DriverSetup=Model=M9336A, Trace=false";

	ViBoolean idQuery = VI_TRUE;
	ViBoolean reset = VI_TRUE;

	// Initialize the driver.  See driver help topic "Initializing the IVI-C Driver" for additional information
	status2 = KtMAwg_InitWithOptions(resourceName2, idQuery, reset, options2, &session2);

	printf("Driver Initialized \n");



	// Play a waveform from a file

	// Specify the channel we'll play the waveform on
	char channelName2[20];

	strncpy(channelName2, "Channel1", 20);

	// Specify the file path
	char sineWaveformFilePath2[200];

	strncpy(sineWaveformFilePath2, "C:\\Users\\Administrator\\Desktop\\C++example\\KtMAwg_Cpp_PlayWaveformFromFile\\Qam16_60M_Center_80M_Symbol.csv", 200);


	// Create the waveform on all channels by setting second parameter to an empty string
	ViInt32 sineWaveformHandle2;
	status2 = KtMAwg_WaveformCreateChannelWaveformFromFile(session2, "", "SineWaveform", 0, sineWaveformFilePath2, &sineWaveformHandle2);

	//configure the output
	status2 = KtMAwg_ConfigureOperationMode(session2, channelName2, KTMAWG_VAL_OPERATE_CONTINUOUS);

	status2 = KtMAwg_OutputSetTerminalConfiguration(session2, channelName2, KTMAWG_VAL_TERMINAL_CONFIGURATION_DIFFERENTIAL);

	status2 = KtMAwg_ArbitrarySetHandle(session2, channelName2, sineWaveformHandle2);

	// Generation Settings Restrictions Enabled
	status2 = KtMAwg_EnableGenerationSettingsRestrictions(session2);

	// Configure the samplerate
	status2 = KtMAwg_ConfigureSampleRate(session2, 1200000000);

	// Configure the Crrection Filter Mode
	status2 = KtMAwg_CorrectionsSetFilterMode(session2, channelName2, KTMAWG_VAL_CORRECTION_FILTER_MODE_CALIBRATED);

	// Set gain mode 
	status2 = KtMAwg_ArbitrarySetGainControl(session2, channelName2, KTMAWG_VAL_GAIN_CONTROL_COMPOSITE);

	// set gain value
	status2 = KtMAwg_ArbitrarySetGain(session2, channelName2, 0.6);

	// set delay
	status2 = KtMAwg_OutputSetDelay(session2, channelName2, 0);

	// Output Enabled
	status2 = KtMAwg_ConfigureOutputEnabled(session2, channelName2, VI_TRUE);

	// Resolve any settings conflicts and call Apply to push the new settings to the module
	status2 = KtMAwg_Resolve(session2);

	status2 = KtMAwg_Apply(session2);

	// Play the waveform on channel one
	status2 = KtMAwg_InitiateGenerationByChannel(session2, channelName2);

	printf("\nWaveform is currently generating - Press enter to abort generation and close the driver.");
	getchar();

	//Abort generation on channel one
	status2 = KtMAwg_AbortGenerationByChannel(session2, channelName2);

	// Close the driver
	status2 = KtMAwg_close(session2);
	catchError("KtMAwg_close", session2, status2);

	session2 = VI_NULL;
	printf("Driver Closed \n");
	return;
}

int _tmain(int argc, _TCHAR* argv[])
{
	ViStatus status;
	ViSession session;
	ViChar str[128];
	ViInt32 ErrorCode;
	ViChar ErrorMessage[256];
	ViBoolean simulate;
	ViChar resourceName[256];

	strcpy_s(resourceName, sizeof(resourceName), "PXI16::0::0::INSTR"); // Use the hardware associated with the connection

	
	char* options = "Simulate=false, DriverSetup=Model=M9336A, Trace=false"; 

	if (argc > 1)
	{
		size_t converted;
		wcstombs_s(&converted, resourceName, sizeof(resourceName), argv[1], sizeof(resourceName));
		options = "Simulate=false, DriverSetup=UseLegacyV2RuntimeActivationPolicy=true, Model=M9336A, Trace=false";
	}

	ViBoolean idQuery = VI_TRUE;
	ViBoolean reset = VI_TRUE;

	printf("  C_Example2\n\n");
	printf("\tRuns in simulated mode if no command line parameter is provided.\n");
	printf("\tRun with resource string argument to use hardware.\n\n");

	// Initialize the driver.  See driver help topic "Initializing the IVI-C Driver" for additional information
	status = KtMAwg_InitWithOptions(resourceName, idQuery, reset, options, &session);
	std::thread pxi16first(pxi16_1);

	if (status || session == VI_NULL)
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
	catchError("KtMAwg_GetAttributeViString", session, status);
	printf("DRIVER_PREFIX:      %s\n", str);

	status = KtMAwg_GetAttributeViString(session, "", KTMAWG_ATTR_SPECIFIC_DRIVER_REVISION, 127, str);
	catchError("KtMAwg_GetAttributeViString", session, status);
	printf("DRIVER_REVISION:    %s\n", str);

	status = KtMAwg_GetAttributeViString(session, "", KTMAWG_ATTR_SPECIFIC_DRIVER_VENDOR, 127, str);
	catchError("KtMAwg_GetAttributeViString", session, status);
	printf("DRIVER_VENDOR:      %s\n", str);

	status = KtMAwg_GetAttributeViString(session, "", KTMAWG_ATTR_SPECIFIC_DRIVER_DESCRIPTION, 127, str);
	catchError("KtMAwg_GetAttributeViString", session, status);
	printf("DRIVER_DESCRIPTION: %s\n", str);

	status = KtMAwg_GetAttributeViString(session, "", KTMAWG_ATTR_INSTRUMENT_MODEL, 127, str);
	catchError("KtMAwg_GetAttributeViString", session, status);
	printf("INSTRUMENT_MODEL:   %s\n", str);

	status = KtMAwg_GetAttributeViString(session, "", KTMAWG_ATTR_INSTRUMENT_FIRMWARE_REVISION, 127, str);
	catchError("KtMAwg_GetAttributeViString", session, status);
	printf("FIRMWARE_REVISION:  %s\n", str);

	status = KtMAwg_GetAttributeViString(session, "", KTMAWG_ATTR_SERIAL_NUMBER, 127, str);
	catchError("KtMAwg_GetAttributeViString", session, status);
	printf("SERIAL_NUMBER:      %s\n", str);

	status = KtMAwg_GetAttributeViBoolean(session, "", KTMAWG_ATTR_SIMULATE, &simulate);
	catchError("KtMAwg_GetAttributeViBoolean", session, status);


	if (simulate == VI_TRUE)
		printf("\nSIMULATE:           True\n\n");
	else
		printf("SIMULATE:           False\n\n");


	// Play a waveform from a file

	// Specify the channel we'll play the waveform on
	char channelName[20];

	strncpy(channelName, "Channel1", 20);

	// Specify the file path
	char sineWaveformFilePath[200];

	strncpy(sineWaveformFilePath, "C:\\Users\\Administrator\\Desktop\\C++example\\KtMAwg_Cpp_PlayWaveformFromFile\\Qam16_60M_Center_80M_Symbol.csv", 200);

	// Create the waveform on all channels by setting second parameter to an empty string
	ViInt32 sineWaveformHandle;
	status = KtMAwg_WaveformCreateChannelWaveformFromFile(session, "", "SineWaveform", 0, sineWaveformFilePath, &sineWaveformHandle);
	catchError("KtMAwg_WaveformCreateChannelWaveformFromFile", session, status);

	//configure the output
	status = KtMAwg_ConfigureOperationMode(session, channelName, KTMAWG_VAL_OPERATE_CONTINUOUS);
	catchError("KtMAwg_ConfigureOperationMode", session, status);

	status = KtMAwg_OutputSetTerminalConfiguration(session, channelName, KTMAWG_VAL_TERMINAL_CONFIGURATION_DIFFERENTIAL);
	catchError("KtMAwg_OutputSetTerminalConfiguration", session, status);

	status = KtMAwg_ArbitrarySetHandle(session, channelName, sineWaveformHandle);
	catchError("KtMAwg_ArbitrarySetHandle", session, status);


	// Generation Settings Restrictions Enabled
	status = KtMAwg_EnableGenerationSettingsRestrictions(session);
	catchError("KtMAwg_EnableGenerationSettingsRestrictions", session, status);



	// Configure the samplerate
	status = KtMAwg_ConfigureSampleRate(session, 1200000000);
	catchError("KtMAwg_ConfigureSampleRate", session, status);


	// Configure the Crrection Filter Mode
	status = KtMAwg_CorrectionsSetFilterMode(session, channelName, KTMAWG_VAL_CORRECTION_FILTER_MODE_CALIBRATED);
	catchError("KtMAwg_CorrectionsSetFilterMode", session, status);


	// Set gain mode 
	status = KtMAwg_ArbitrarySetGainControl(session, channelName, KTMAWG_VAL_GAIN_CONTROL_COMPOSITE);
	catchError("KTMAWG_VAL_GAIN_CONTROL_COMPOSITE", session, status);


	// set gain value
	status = KtMAwg_ArbitrarySetGain(session, channelName, 0.6);
	catchError("KtMAwg_ArbitrarySetGain", session, status);

	// set delay
	status = KtMAwg_OutputSetDelay(session, channelName, 0);
	catchError("KtMAwg_OutputSetDelay", session, status);

	// Output Enabled
	status = KtMAwg_ConfigureOutputEnabled(session, channelName, VI_TRUE);
	catchError("KtMAwg_ConfigureOutputEnabled", session, status);

	// Resolve any settings conflicts and call Apply to push the new settings to the module
	status = KtMAwg_Resolve(session);
	catchError("KtMAwg_Resolve", session, status);

	status = KtMAwg_Apply(session);
	catchError("KtMAwg_Apply", session, status);

	// Play the waveform on channel one
	status = KtMAwg_InitiateGenerationByChannel(session, channelName);
	catchError("KtMAwg_InitiateGenerationByChannel", session, status);

	//
	pxi16first.join();

	//Abort generation on channel one
	status = KtMAwg_AbortGenerationByChannel(session, channelName);
	catchError("KtMAwg_AbortGenerationByChannel", session, status);

	// Close the driver
	status = KtMAwg_close(session);
	catchError("KtMAwg_close", session, status);

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
	if (status == VI_SUCCESS)
	{
		return;
	}

	// No session handle, will be impossible to query the driver for errors.
	if (session == VI_NULL)
	{
		printf("** Error, Unable to query driver for errors, the VISA session is null.\n");
		printf("\nAbort - Press Enter to Exit");
		getchar();
		exit(1);
	}

	KtMAwg_GetError(session, &ErrorCode, 255, ErrorMessage);
	printf("** %s() Error: %d, %s\n", routine, ErrorCode, ErrorMessage);

	status = KtMAwg_close(session); // Try to close the driver session before exit. 
	if (status)
	{
		KtMAwg_GetError(session, &ErrorCode, 255, ErrorMessage);
		printf("** %s() Error: %d, %s\n", routine, ErrorCode, ErrorMessage);
	}
	else
	{
		printf("Driver Closed \n");
	}

	printf("\nAbort - Press Enter to Exit");
	getchar();
	exit(1);
}