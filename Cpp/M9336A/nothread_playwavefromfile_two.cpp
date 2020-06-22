#include "stdafx.h"
#include "atlstr.h"
#include <ctime>
#include "KtMAwg.h"

/**
*可以同时运行两路
*运行时间慢，程序运行时间为13S左右，效率低
*/
// catchError 功能函数定义，可打印错误码和错误信息
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

// 主函数（主线程）
int _tmain(int argc, _TCHAR* argv[])
{
	ViStatus status, status2;		
	ViSession session, session2;	// 内存空间分配, 每个 status 需要对应的 session
	ViChar str[128];
	ViInt32 ErrorCode;
	ViChar ErrorMessage[256];
	ViBoolean simulate;
	ViChar resourceName[256], resourceName2[256];

	strcpy_s(resourceName, sizeof(resourceName), "PXI16::0::0::INSTR"); // Use the hardware associated with the connection
	strcpy_s(resourceName2, sizeof(resourceName2), "PXI15::0::0::INSTR");

	char* options = "Simulate=false, DriverSetup=Model=M9336A, Trace=false"; 	//

	if (argc > 1)
	{
		size_t converted;
		wcstombs_s(&converted, resourceName, sizeof(resourceName), argv[1], sizeof(resourceName));
		wcstombs_s(&converted, resourceName2, sizeof(resourceName2), argv[1], sizeof(resourceName2));
		options = "Simulate=false, DriverSetup=UseLegacyV2RuntimeActivationPolicy=true, Model=M9336A, Trace=false";
	}

	ViBoolean idQuery = VI_TRUE;
	ViBoolean reset = VI_TRUE;

	printf("  C_Example2\n\n");
	printf("\tRuns in simulated mode if no command line parameter is provided.\n");
	printf("\tRun with resource string argument to use hardware.\n\n");

	// Initialize the driver.  See driver help topic "Initializing the IVI-C Driver" for additional information
	status = KtMAwg_InitWithOptions(resourceName, idQuery, reset, options, &session);
	status2 = KtMAwg_InitWithOptions(resourceName2, idQuery, reset, options, &session2);
	if (status || session == VI_NULL)
	{
		// Initialization failed
		KtMAwg_GetError(session, &ErrorCode, 255, ErrorMessage);
		printf("** InitWithOptions() Error: %d, %s\n", ErrorCode, ErrorMessage);
		printf("\nDone - Press Enter to Exit");
		getchar();
		return ErrorCode;
	}
	if (status2 || session2 == VI_NULL)
	{
		// Initialization failed
		KtMAwg_GetError(session2, &ErrorCode, 255, ErrorMessage);
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
	//status2
	status2 = KtMAwg_GetAttributeViString(session2, "", KTMAWG_ATTR_SPECIFIC_DRIVER_PREFIX, 127, str);
	catchError("KtMAwg_GetAttributeViString", session2, status2);
	printf("DRIVER_PREFIX:      %s\n", str);

	status2 = KtMAwg_GetAttributeViString(session2, "", KTMAWG_ATTR_SPECIFIC_DRIVER_REVISION, 127, str);
	catchError("KtMAwg_GetAttributeViString", session2, status2);
	printf("DRIVER_REVISION:    %s\n", str);

	status2 = KtMAwg_GetAttributeViString(session2, "", KTMAWG_ATTR_SPECIFIC_DRIVER_VENDOR, 127, str);
	catchError("KtMAwg_GetAttributeViString", session2, status2);
	printf("DRIVER_VENDOR:      %s\n", str);

	status2 = KtMAwg_GetAttributeViString(session2, "", KTMAWG_ATTR_SPECIFIC_DRIVER_DESCRIPTION, 127, str);
	catchError("KtMAwg_GetAttributeViString", session2, status2);
	printf("DRIVER_DESCRIPTION: %s\n", str);

	status2 = KtMAwg_GetAttributeViString(session2, "", KTMAWG_ATTR_INSTRUMENT_MODEL, 127, str);
	catchError("KtMAwg_GetAttributeViString", session2, status2);
	printf("INSTRUMENT_MODEL:   %s\n", str);

	status2 = KtMAwg_GetAttributeViString(session2, "", KTMAWG_ATTR_INSTRUMENT_FIRMWARE_REVISION, 127, str);
	catchError("KtMAwg_GetAttributeViString", session2, status2);
	printf("FIRMWARE_REVISION:  %s\n", str);

	status2 = KtMAwg_GetAttributeViString(session2, "", KTMAWG_ATTR_SERIAL_NUMBER, 127, str);
	catchError("KtMAwg_GetAttributeViString", session2, status2);
	printf("SERIAL_NUMBER:      %s\n", str);

	status2 = KtMAwg_GetAttributeViBoolean(session2, "", KTMAWG_ATTR_SIMULATE, &simulate);
	catchError("KtMAwg_GetAttributeViBoolean", session2, status2);

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
	char sineWavefromFilePath2[200];
	strncpy(sineWaveformFilePath, "C:\\Users\\Administrator\\Desktop\\C++example\\KtMAwg_Cpp_PlayWaveformFromFile\\Qam16_60M_Center_80M_Symbol.csv", 200);
	strncpy(sineWavefromFilePath2, "C:\\Users\\Administrator\\Desktop\\C++example\\KtMAwg_Cpp_PlayWaveformFromFile\\Qam16_60M_Center_80M_Symbol.csv", 200);

	// Create the waveform on all channels by setting second parameter to an empty string
	ViInt32 sineWaveformHandle;
	status = KtMAwg_WaveformCreateChannelWaveformFromFile(session, "", "SineWaveform", 0, sineWaveformFilePath, &sineWaveformHandle);
	catchError("KtMAwg_WaveformCreateChannelWaveformFromFile", session, status);
	//status2
	status2 = KtMAwg_WaveformCreateChannelWaveformFromFile(session2, "", "Qam16Waveform", 0, sineWavefromFilePath2, &sineWaveformHandle);
	catchError("KtMAwg_WaveformCreateChannelWaveformFromFile", session2, status2);

	//configure the output
	status = KtMAwg_ConfigureOperationMode(session, channelName, KTMAWG_VAL_OPERATE_CONTINUOUS);
	catchError("KtMAwg_ConfigureOperationMode", session, status);

	status = KtMAwg_OutputSetTerminalConfiguration(session, channelName, KTMAWG_VAL_TERMINAL_CONFIGURATION_DIFFERENTIAL);
	catchError("KtMAwg_OutputSetTerminalConfiguration", session, status);

	status = KtMAwg_ArbitrarySetHandle(session, channelName, sineWaveformHandle);
	catchError("KtMAwg_ArbitrarySetHandle", session, status);
	//status2
	status2 = KtMAwg_ConfigureOperationMode(session2, channelName, KTMAWG_VAL_OPERATE_CONTINUOUS);
	catchError("KtMAwg_ConfigureOperationMode", session2, status2);

	status2 = KtMAwg_OutputSetTerminalConfiguration(session2, channelName, KTMAWG_VAL_TERMINAL_CONFIGURATION_DIFFERENTIAL);
	catchError("KtMAwg_OutputSetTerminalConfiguration", session2, status2);

	status2 = KtMAwg_ArbitrarySetHandle(session2, channelName, sineWaveformHandle);
	catchError("KtMAwg_ArbitrarySetHandle", session2, status2);

	// Generation Settings Restrictions Enabled
	status = KtMAwg_EnableGenerationSettingsRestrictions(session);
	catchError("KtMAwg_EnableGenerationSettingsRestrictions", session, status);

	status2 = KtMAwg_EnableGenerationSettingsRestrictions(session2);
	catchError("KtMAwg_EnableGenerationSettingsRestrictions", session2, status2);

	// Configure the samplerate
	status = KtMAwg_ConfigureSampleRate(session, 1200000000);
	catchError("KtMAwg_ConfigureSampleRate", session, status);

	status2 = KtMAwg_ConfigureSampleRate(session2, 1200000000);
	catchError("KtMAwg_ConfigureSampleRate", session2, status2);

	// Configure the Crrection Filter Mode
	status = KtMAwg_CorrectionsSetFilterMode(session, channelName, KTMAWG_VAL_CORRECTION_FILTER_MODE_CALIBRATED);
	catchError("KtMAwg_CorrectionsSetFilterMode", session, status);

	status2 = KtMAwg_CorrectionsSetFilterMode(session2, channelName, KTMAWG_VAL_CORRECTION_FILTER_MODE_CALIBRATED);
	catchError("KtMAwg_CorrectionsSetFilterMode", session2, status2);

	// Set gain mode 
	status = KtMAwg_ArbitrarySetGainControl(session, channelName, KTMAWG_VAL_GAIN_CONTROL_COMPOSITE);
	catchError("KTMAWG_VAL_GAIN_CONTROL_COMPOSITE", session, status);

	status2 = KtMAwg_ArbitrarySetGainControl(session2, channelName, KTMAWG_VAL_GAIN_CONTROL_COMPOSITE);
	catchError("KTMAWG_VAL_GAIN_CONTROL_COMPOSITE", session2, status2);

	// set gain value
	status = KtMAwg_ArbitrarySetGain(session, channelName, 0.6);
	catchError("KtMAwg_ArbitrarySetGain", session, status);

	status2 = KtMAwg_ArbitrarySetGain(session2, channelName, 0.6);
	catchError("KtMAwg_ArbitrarySetGain", session2, status2);

	// set delay
	status = KtMAwg_OutputSetDelay(session, channelName, 0);
	catchError("KtMAwg_OutputSetDelay", session, status);

	status2 = KtMAwg_OutputSetDelay(session2, channelName, 0);
	catchError("KtMAwg_OutputSetDelay", session2, status2);

	// initial generation
	//status = KtMAwg_InitiateGeneration(session);
	//catchError("KtMAwg_InitiateGeneration", session, status);

	//status2 = KtMAwg_InitiateGeneration(session);
	//catchError("KtMAwg_InitiateGeneration", session, status2);

	// Output Enabled
	status = KtMAwg_ConfigureOutputEnabled(session, channelName, VI_TRUE);
	catchError("KtMAwg_ConfigureOutputEnabled", session, status);

	status2 = KtMAwg_ConfigureOutputEnabled(session2, channelName, VI_TRUE);
	catchError("KtMAwg_ConfigureOutputEnabled", session2, status2);

	// Resolve any settings conflicts and call Apply to push the new settings to the module
	status = KtMAwg_Resolve(session);
	catchError("KtMAwg_Resolve", session, status);

	status = KtMAwg_Apply(session);
	catchError("KtMAwg_Apply", session, status);

	status2 = KtMAwg_Resolve(session2);
	catchError("KtMAwg_Resolve", session2, status2);

	status2 = KtMAwg_Apply(session2);
	catchError("KtMAwg_Apply", session2, status2);

	// Play the waveform on channel
	status = KtMAwg_InitiateGenerationByChannel(session, channelName);
	catchError("KtMAwg_InitiateGenerationByChannel", session, status);

	status2 = KtMAwg_InitiateGenerationByChannel(session2, channelName);
	catchError("KtMAwg_InitiateGenerationByChannel", session2, status2);

	printf("\nWaveform is currently generating - Press enter to abort generation and close the driver.");
	getchar();

	//Abort generation on channel
	status = KtMAwg_AbortGenerationByChannel(session, channelName);
	catchError("KtMAwg_AbortGenerationByChannel", session, status);

	status2 = KtMAwg_AbortGenerationByChannel(session2, channelName);
	catchError("KtMAwg_AbortGenerationByChannel", session2, status2);

	// Close the driver
	status = KtMAwg_close(session);
	catchError("KtMAwg_close", session, status);

	status2 = KtMAwg_close(session2);
	catchError("KtMAwg_close", session2, status2);

	session = VI_NULL;
	session2 = VI_NULL;
	
	printf("Driver Closed \n");
	printf("\nDone - Press Enter to Exit");
	getchar();

	return 0;
}

