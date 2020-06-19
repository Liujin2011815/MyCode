#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include "AgMD2.h"
#include <fstream>


/// Initializes the driver, reads a few Identity interface properties, and performs a simple
/// acquisition.


// Utility function to check status error during driver API call.
void checkApiCall(ViStatus status, char const* functionName)
{
    ViInt32 ErrorCode;
    ViChar ErrorMessage[256];

    if (status > 0) // Warning occurred.
    {
        AgMD2_GetError(VI_NULL, &ErrorCode, sizeof(ErrorMessage), ErrorMessage);
        printf("** Warning during %s: 0x%08x, %s\n", functionName, ErrorCode, ErrorMessage);
    }
    else if (status < 0) // Error occurred.
    {
        AgMD2_GetError(VI_NULL, &ErrorCode, sizeof(ErrorMessage), ErrorMessage);
        printf("** Error during %s: 0x%08x, %s\n", functionName, ErrorCode, ErrorMessage);
        printf("\nDone - Press enter to exit");
        getchar();
        exit(-1);
    }
}

int _tmain(int argc, _TCHAR* argv[])
{
    ViSession session;
    ViChar str[128] = { '\0' };
    ViBoolean simulate;
    ViBoolean idQuery = VI_TRUE;
    ViBoolean reset   = VI_TRUE;
    ViInt32 timeoutInMs = 1000;
    ViInt64 const recordSize = 1000000;
    ViReal64 range = 1.0, offset = 0.0;
    ViInt32 coupling = AGMD2_VAL_VERTICAL_COUPLING_DC;
    ViInt64 arraySize = 0;
    ViInt16* dataArray;
    ViInt64 actualPoints = 0, firstValidPoint = 0;
    ViReal64 initialXOffset = 0.0, initialXTimeSeconds = 0.0, initialXTimeFraction = 0.0;
    ViReal64 xIncrement = 0.0, scaleFactor = 0.0, scaleOffset = 0.0;
    int currentPoint;

    // Edit resource and options as needed. Resource is ignored if option Simulate=true.
    char resource[] = "PXI31::0::0::INSTR";

    // An input signal is necessary if the example is run in non simulated mode, otherwise
    // the acquisition will time out.
    char options[] = "Simulate=false, DriverSetup= Model=U5303A";

    printf("  CPP_IVIC_SimpleAcquisition\n\n");
	

    // Initialize the driver. See driver help topic "Initializing the IVI-C Driver" for additional information.
    checkApiCall(AgMD2_InitWithOptions(resource, idQuery, reset, options, &session), "AgMD2_InitWithOptions");

    printf("Driver initialized \n");

    // Read and output a few attributes.
    checkApiCall(AgMD2_GetAttributeViString(session, "", AGMD2_ATTR_SPECIFIC_DRIVER_PREFIX, sizeof(str), str), "AgMD2_GetAttributeViString(AGMD2_ATTR_SPECIFIC_DRIVER_PREFIX)");
    printf("Driver prefix:      %s\n", str);
    checkApiCall(AgMD2_GetAttributeViString(session, "", AGMD2_ATTR_SPECIFIC_DRIVER_REVISION, sizeof(str), str), "AgMD2_GetAttributeViString(AGMD2_ATTR_SPECIFIC_DRIVER_REVISION)");
    printf("Driver revision:    %s\n", str);
    checkApiCall(AgMD2_GetAttributeViString(session, "", AGMD2_ATTR_SPECIFIC_DRIVER_VENDOR, sizeof(str), str), "AgMD2_GetAttributeViString(AGMD2_ATTR_SPECIFIC_DRIVER_VENDOR)");
    printf("Driver vendor:      %s\n", str);
    checkApiCall(AgMD2_GetAttributeViString(session, "", AGMD2_ATTR_SPECIFIC_DRIVER_DESCRIPTION, sizeof(str), str), "AgMD2_GetAttributeViString(AGMD2_ATTR_SPECIFIC_DRIVER_DESCRIPTION)");
    printf("Driver description: %s\n", str);
    checkApiCall(AgMD2_GetAttributeViString(session, "", AGMD2_ATTR_INSTRUMENT_MODEL, sizeof(str), str), "AgMD2_GetAttributeViString(AGMD2_ATTR_INSTRUMENT_MODEL)");
    printf("Instrument model:   %s\n", str);
    checkApiCall(AgMD2_GetAttributeViString(session, "", AGMD2_ATTR_INSTRUMENT_FIRMWARE_REVISION, sizeof(str), str), "AgMD2_GetAttributeViString(AGMD2_ATTR_INSTRUMENT_FIRMWARE_REVISION)");
    printf("Firmware revision:  %s\n", str);
    checkApiCall(AgMD2_GetAttributeViString(session, "", AGMD2_ATTR_INSTRUMENT_INFO_SERIAL_NUMBER_STRING, sizeof(str), str), "AgMD2_GetAttributeViString(AGMD2_ATTR_INSTRUMENT_INFO_SERIAL_NUMBER_STRING)");
    printf("Serial number:      %s\n", str);
    checkApiCall(AgMD2_GetAttributeViBoolean(session, "", AGMD2_ATTR_SIMULATE, &simulate), "AgMD2_GetAttributeViBoolean(AGMD2_ATTR_SIMULATE)");
    if (simulate == VI_TRUE)
        printf("\nSimulate:           True\n\n");
    else
        printf("\nSimulate:           False\n\n");

    // Configure the acquisition.
    printf("Configuring acquisition\n");
    printf("Range:              %g\n", range);
    printf("Offset:             %g\n", offset);
    printf("Coupling:           %s\n", coupling?"DC":"AC");
    checkApiCall(AgMD2_ConfigureChannel(session, "Channel1", range, offset, coupling, VI_TRUE), "AgMD2_ConfigureChannel");
    printf("Record size:        %d\n\n", recordSize);
    checkApiCall(AgMD2_SetAttributeViInt64(session, "", AGMD2_ATTR_RECORD_SIZE, recordSize), "AgMD2_SetAttributeViInt64(AGMD2_ATTR_RECORD_SIZE)");

	// Configure the acquisition
	//checkApiCall(AgMD2_ConfigureAcquisition(session,1, 481500, 80000000.0), "AgMD2_ConfigureAcquisition");
	//checkApiCall(AgMD2_SetAttributeViReal64(session, "", AGMD2_ATTR_SAMPLE_RATE, 1000), "AgMD2_SetAttributeViReal64(AGMD2_ATTR_SAMPLE_RATE)");

    // Configure the trigger.
    printf("Configuring trigger\n");
    checkApiCall(AgMD2_SetAttributeViString(session, "", AGMD2_ATTR_ACTIVE_TRIGGER_SOURCE, "Internal1"), "AgMD2_SetAttributeViString(AGMD2_ATTR_ACTIVE_TRIGGER_SOURCE)");

    // Calibrate the instrument.
    printf("Performing self-calibration\n");
    checkApiCall(AgMD2_SelfCalibrate(session), "AgMD2_SelfCalibrate");

    // Perform the acquisition.
    printf("Performing acquisition\n");
    checkApiCall(AgMD2_InitiateAcquisition(session), "AgMD2_InitiateAcquisition");
    checkApiCall(AgMD2_WaitForAcquisitionComplete(session, timeoutInMs), "AgMD2_WaitForAcquisitionComplete");
    printf("Acquisition completed\n");

    // Fetch the acquired data in array.
    checkApiCall(AgMD2_QueryMinWaveformMemory(session, 16, 1, 0, recordSize, &arraySize), "AgMD2_QueryMinWaveformMemory");
    dataArray = (ViInt16*)malloc((size_t)arraySize * sizeof(ViInt16));
    checkApiCall(AgMD2_FetchWaveformInt16(session, "Channel1", arraySize, dataArray,
        &actualPoints, &firstValidPoint,
        &initialXOffset, &initialXTimeSeconds, &initialXTimeFraction,
        &xIncrement, &scaleFactor, &scaleOffset), "AgMD2_FetchWaveformInt16");

	//output data to file
	using namespace std;
	ofstream OpenFile("C:\\Users\\Administrator\\Desktop\\C++example\\output.csv");

    // Convert data to Volts.
	ViReal64 valueInVolts;
    printf("Processing data\n");
    for (currentPoint = 0; currentPoint < actualPoints; ++currentPoint)
    {
        valueInVolts = dataArray[firstValidPoint + currentPoint] * scaleFactor + scaleOffset;
		OpenFile << valueInVolts << "\n";
    }
    printf("Processing completed\n");
	OpenFile.close();

    // Close the driver.
    checkApiCall(AgMD2_close(session), "AgMD2_close");
    printf("Driver closed \n");

    free(dataArray);
    printf("\nDone - Press enter to exit");
    getchar();

    return 0;
}

