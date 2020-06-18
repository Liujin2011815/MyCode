/******************************************************************************
 *                                                                         
 * Copyright 2016, Keysight Technologies
 *
 *****************************************************************************/

#ifndef __KTMPXICHASSIS_HEADER
#define __KTMPXICHASSIS_HEADER

#include <ivivisatype.h>

#if defined(__cplusplus) || defined(__cplusplus__)
extern "C" {
#endif

/**************************************************************************** 
 *---------------------------- Attribute Defines ---------------------------* 
 ****************************************************************************/
#ifndef IVI_ATTR_BASE
#define IVI_ATTR_BASE                 1000000
#endif

#ifndef IVI_INHERENT_ATTR_BASE		        
#define IVI_INHERENT_ATTR_BASE        (IVI_ATTR_BASE +  50000)   /* base for inherent capability attributes */
#endif

#ifndef IVI_CLASS_ATTR_BASE           
#define IVI_CLASS_ATTR_BASE           (IVI_ATTR_BASE + 250000)   /* base for IVI-defined class attributes */
#endif

#ifndef IVI_LXISYNC_ATTR_BASE         
#define IVI_LXISYNC_ATTR_BASE         (IVI_ATTR_BASE + 950000)   /* base for IviLxiSync attributes */
#endif

#ifndef IVI_SPECIFIC_ATTR_BASE        
#define IVI_SPECIFIC_ATTR_BASE        (IVI_ATTR_BASE + 150000)   /* base for attributes of specific drivers */
#endif


/*===== IVI Inherent Instrument Attributes ==============================*/    

/*- Driver Identification */

#define KTMPXICHASSIS_ATTR_SPECIFIC_DRIVER_DESCRIPTION              (IVI_INHERENT_ATTR_BASE + 514L)  /* ViString, read-only */
#define KTMPXICHASSIS_ATTR_SPECIFIC_DRIVER_PREFIX                   (IVI_INHERENT_ATTR_BASE + 302L)  /* ViString, read-only */
#define KTMPXICHASSIS_ATTR_SPECIFIC_DRIVER_VENDOR                   (IVI_INHERENT_ATTR_BASE + 513L)  /* ViString, read-only */
#define KTMPXICHASSIS_ATTR_SPECIFIC_DRIVER_REVISION                 (IVI_INHERENT_ATTR_BASE + 551L)  /* ViString, read-only */
#define KTMPXICHASSIS_ATTR_SPECIFIC_DRIVER_CLASS_SPEC_MAJOR_VERSION (IVI_INHERENT_ATTR_BASE + 515L)  /* ViInt32, read-only */
#define KTMPXICHASSIS_ATTR_SPECIFIC_DRIVER_CLASS_SPEC_MINOR_VERSION (IVI_INHERENT_ATTR_BASE + 516L)  /* ViInt32, read-only */

/*- User Options */

#define KTMPXICHASSIS_ATTR_RANGE_CHECK                      (IVI_INHERENT_ATTR_BASE + 2L)  /* ViBoolean, read-write */
#define KTMPXICHASSIS_ATTR_QUERY_INSTRUMENT_STATUS          (IVI_INHERENT_ATTR_BASE + 3L)  /* ViBoolean, read-write */
#define KTMPXICHASSIS_ATTR_CACHE                            (IVI_INHERENT_ATTR_BASE + 4L)  /* ViBoolean, read-write */
#define KTMPXICHASSIS_ATTR_SIMULATE                         (IVI_INHERENT_ATTR_BASE + 5L)  /* ViBoolean, read-write */
#define KTMPXICHASSIS_ATTR_RECORD_COERCIONS                 (IVI_INHERENT_ATTR_BASE + 6L)  /* ViBoolean, read-write */
#define KTMPXICHASSIS_ATTR_INTERCHANGE_CHECK                (IVI_INHERENT_ATTR_BASE + 21L)  /* ViBoolean, read-write */

/*- Advanced Session Information */

#define KTMPXICHASSIS_ATTR_LOGICAL_NAME                     (IVI_INHERENT_ATTR_BASE + 305L)  /* ViString, read-only */
#define KTMPXICHASSIS_ATTR_IO_RESOURCE_DESCRIPTOR           (IVI_INHERENT_ATTR_BASE + 304L)  /* ViString, read-only */
#define KTMPXICHASSIS_ATTR_DRIVER_SETUP                     (IVI_INHERENT_ATTR_BASE + 7L)  /* ViString, read-only */

/*- Driver Capabilities */

#define KTMPXICHASSIS_ATTR_GROUP_CAPABILITIES               (IVI_INHERENT_ATTR_BASE + 401L)  /* ViString, read-only */
#define KTMPXICHASSIS_ATTR_SUPPORTED_INSTRUMENT_MODELS      (IVI_INHERENT_ATTR_BASE + 327L)  /* ViString, read-only */

/*- Instrument Identification */

#define KTMPXICHASSIS_ATTR_INSTRUMENT_FIRMWARE_REVISION     (IVI_INHERENT_ATTR_BASE + 510L)  /* ViString, read-only */
#define KTMPXICHASSIS_ATTR_INSTRUMENT_MANUFACTURER          (IVI_INHERENT_ATTR_BASE + 511L)  /* ViString, read-only */
#define KTMPXICHASSIS_ATTR_INSTRUMENT_MODEL                 (IVI_INHERENT_ATTR_BASE + 512L)  /* ViString, read-only */


/*===== Instrument-Specific Attributes =====================================*/

/*- System */

#define KTMPXICHASSIS_ATTR_SYSTEM_SERIAL_NUMBER             (IVI_SPECIFIC_ATTR_BASE + 3L)  /* ViString, read-only */
#define KTMPXICHASSIS_ATTR_SYSTEM_UPTIME                    (IVI_SPECIFIC_ATTR_BASE + 4L)  /* ViReal64, read-only */
#define KTMPXICHASSIS_ATTR_SYSTEM_SELF_TEST_ERROR_COUNT     (IVI_SPECIFIC_ATTR_BASE + 5L)  /* ViInt32, read-only */
#define KTMPXICHASSIS_ATTR_SYSTEM_CHASSIS_NUMBER            (IVI_SPECIFIC_ATTR_BASE + 58L)  /* ViInt32, read-only */
#define KTMPXICHASSIS_ATTR_SYSTEM_IDENTIFY                  (IVI_SPECIFIC_ATTR_BASE + 59L)  /* ViBoolean, read-write */

/*- SystemSlot */

#define KTMPXICHASSIS_ATTR_SYSTEM_SLOT_PCIE_LINK            (IVI_SPECIFIC_ATTR_BASE + 6L)  /* ViString, read-only */
#define KTMPXICHASSIS_ATTR_SYSTEM_SLOT_PCIE_LINK_MODE       (IVI_SPECIFIC_ATTR_BASE + 65L)  /* ViInt32, read-only */

/*- PCIeNegotiatedLink */

#define KTMPXICHASSIS_ATTR_SYSTEM_SLOT_PCIE_NEGOTIATED_LINK_COUNT (IVI_SPECIFIC_ATTR_BASE + 66L)  /* ViInt32, read-only */
#define KTMPXICHASSIS_ATTR_SYSTEM_SLOT_NEGOTIATED_LINK_SPEED      (IVI_SPECIFIC_ATTR_BASE + 67L)  /* ViInt32, read-only */
#define KTMPXICHASSIS_ATTR_SYSTEM_SLOT_NEGOTIATED_LINK_WIDTH      (IVI_SPECIFIC_ATTR_BASE + 68L)  /* ViInt32, read-only */

/*- TemperatureSensor */

#define KTMPXICHASSIS_ATTR_TEMPERATURE_SENSOR_COUNT         (IVI_SPECIFIC_ATTR_BASE + 7L)  /* ViInt32, read-only */
#define KTMPXICHASSIS_ATTR_TEMPERATURE                      (IVI_SPECIFIC_ATTR_BASE + 19L)  /* ViReal64, read-only */

/*- Alarm */

#define KTMPXICHASSIS_ATTR_TEMPERATURE_ALARM_ENABLED         (IVI_SPECIFIC_ATTR_BASE + 9L)  /* ViBoolean, read-write */
#define KTMPXICHASSIS_ATTR_TEMPERATURE_ALARM_MAX_TEMPERATURE (IVI_SPECIFIC_ATTR_BASE + 10L)  /* ViInt32, read-write */
#define KTMPXICHASSIS_ATTR_TEMPERATURE_ALARM_OCCURRED        (IVI_SPECIFIC_ATTR_BASE + 11L)  /* ViBoolean, read-only */

/*- VoltageRail */

#define KTMPXICHASSIS_ATTR_VOLTAGE_RAIL_COUNT               (IVI_SPECIFIC_ATTR_BASE + 12L)  /* ViInt32, read-only */
#define KTMPXICHASSIS_ATTR_VOLTAGE_EXPECTED                 (IVI_SPECIFIC_ATTR_BASE + 13L)  /* ViReal64, read-only */
#define KTMPXICHASSIS_ATTR_VOLTAGE                          (IVI_SPECIFIC_ATTR_BASE + 14L)  /* ViReal64, read-only */

/*- Alarm */

#define KTMPXICHASSIS_ATTR_VOLTAGE_ALARM_LOWER_LIMIT        (IVI_SPECIFIC_ATTR_BASE + 15L)  /* ViReal64, read-write */
#define KTMPXICHASSIS_ATTR_VOLTAGE_ALARM_UPPER_LIMIT        (IVI_SPECIFIC_ATTR_BASE + 16L)  /* ViReal64, read-write */
#define KTMPXICHASSIS_ATTR_VOLTAGE_ALARM_ENABLED            (IVI_SPECIFIC_ATTR_BASE + 17L)  /* ViBoolean, read-write */
#define KTMPXICHASSIS_ATTR_VOLTAGE_ALARM_OCCURRED           (IVI_SPECIFIC_ATTR_BASE + 18L)  /* ViBoolean, read-only */

/*- ReferenceClock */

#define KTMPXICHASSIS_ATTR_REFCLK_SOURCE                    (IVI_SPECIFIC_ATTR_BASE + 25L)  /* ViInt32, read-write */
#define KTMPXICHASSIS_ATTR_REFCLK_SOURCE_AUTO               (IVI_SPECIFIC_ATTR_BASE + 26L)  /* ViBoolean, read-write */
#define KTMPXICHASSIS_ATTR_REFCLK_IS_PHASE_LOCKED           (IVI_SPECIFIC_ATTR_BASE + 51L)  /* ViBoolean, read-only */

/*- Alarm */

#define KTMPXICHASSIS_ATTR_REFCLK_ALARM_ENABLED             (IVI_SPECIFIC_ATTR_BASE + 28L)  /* ViBoolean, read-write */
#define KTMPXICHASSIS_ATTR_REFCLK_ALARM_OCCURRED            (IVI_SPECIFIC_ATTR_BASE + 29L)  /* ViBoolean, read-only */

/*- FanTray */

#define KTMPXICHASSIS_ATTR_FAN_TRAY_COUNT                   (IVI_SPECIFIC_ATTR_BASE + 30L)  /* ViInt32, read-only */

/*- Fan */

#define KTMPXICHASSIS_ATTR_FAN_TRAY_FAN_COUNT               (IVI_SPECIFIC_ATTR_BASE + 31L)  /* ViInt32, read-only */
#define KTMPXICHASSIS_ATTR_FAN_TRAY_FAN_RPM                 (IVI_SPECIFIC_ATTR_BASE + 32L)  /* ViInt32, read-only */

/*- Alarm */

#define KTMPXICHASSIS_ATTR_FAN_TRAY_ALARM_ENABLED           (IVI_SPECIFIC_ATTR_BASE + 33L)  /* ViBoolean, read-write */
#define KTMPXICHASSIS_ATTR_FAN_TRAY_ALARM_MIN_RPM           (IVI_SPECIFIC_ATTR_BASE + 34L)  /* ViInt32, read-write */
#define KTMPXICHASSIS_ATTR_FAN_TRAY_ALARM_OCCURRED          (IVI_SPECIFIC_ATTR_BASE + 35L)  /* ViBoolean, read-only */

/*- Control */

#define KTMPXICHASSIS_ATTR_FAN_CONTROL_AUTO                 (IVI_SPECIFIC_ATTR_BASE + 52L)  /* ViBoolean, read-only */
#define KTMPXICHASSIS_ATTR_FAN_CONTROL_MAX_RPM_TEMPERATURE  (IVI_SPECIFIC_ATTR_BASE + 53L)  /* ViInt32, read-write */

/*- ExternalSignals */

#define KTMPXICHASSIS_ATTR_EXTERNAL_SIGNALS_CLOCK_OUTPUT_ENABLED (IVI_SPECIFIC_ATTR_BASE + 50L)  /* ViBoolean, read-write */

/*- TriggerPort */

#define KTMPXICHASSIS_ATTR_TRIGGER_PORT_COUNT                             (IVI_SPECIFIC_ATTR_BASE + 54L)  /* ViInt32, read-only */
#define KTMPXICHASSIS_ATTR_TRIGGER_PORT_DRIVE_TYPE                        (IVI_SPECIFIC_ATTR_BASE + 55L)  /* ViInt32, read-write */
#define KTMPXICHASSIS_ATTR_TRIGGER_PORT_CONNECTED_PXI_TRIGGER_BUS_SEGMENT (IVI_SPECIFIC_ATTR_BASE + 69L)  /* ViInt32, read-only */

/*- Input */

#define KTMPXICHASSIS_ATTR_TRIGGER_PORT_INPUT_DESTINATION   (IVI_SPECIFIC_ATTR_BASE + 56L)  /* ViInt32, read-write */

/*- Output */

#define KTMPXICHASSIS_ATTR_TRIGGER_PORT_OUTPUT_SOURCE       (IVI_SPECIFIC_ATTR_BASE + 57L)  /* ViInt32, read-write */

/*- PeripheralSlot */

#define KTMPXICHASSIS_ATTR_PERIPHERALSLOT_COUNT             (IVI_SPECIFIC_ATTR_BASE + 60L)  /* ViInt32, read-only */
#define KTMPXICHASSIS_ATTR_PCIE_MAXIMUM_LINK_SPEED          (IVI_SPECIFIC_ATTR_BASE + 61L)  /* ViInt32, read-only */
#define KTMPXICHASSIS_ATTR_PCIE_MAXIMUM_LINK_WIDTH          (IVI_SPECIFIC_ATTR_BASE + 62L)  /* ViInt32, read-only */
#define KTMPXICHASSIS_ATTR_PCIE_NEGOTIATED_LINK_SPEED       (IVI_SPECIFIC_ATTR_BASE + 63L)  /* ViInt32, read-only */
#define KTMPXICHASSIS_ATTR_PCIE_NEGOTIATED_LINK_WIDTH       (IVI_SPECIFIC_ATTR_BASE + 64L)  /* ViInt32, read-only */


/**************************************************************************** 
 *------------------------ Attribute Value Defines -------------------------* 
 ****************************************************************************/

/*- Defined values for */

#define KTMPXICHASSIS_VAL_STATUS_BYTE_FLAGS_USER0                 1
#define KTMPXICHASSIS_VAL_STATUS_BYTE_FLAGS_USER1                 2
#define KTMPXICHASSIS_VAL_STATUS_BYTE_FLAGS_USER2                 4
#define KTMPXICHASSIS_VAL_STATUS_BYTE_FLAGS_USER3                 8
#define KTMPXICHASSIS_VAL_STATUS_BYTE_FLAGS_MESSAGE_AVAILABLE     16
#define KTMPXICHASSIS_VAL_STATUS_BYTE_FLAGS_EVENT_STATUS_REGISTER 32
#define KTMPXICHASSIS_VAL_STATUS_BYTE_FLAGS_REQUESTING_SERVICE    64
#define KTMPXICHASSIS_VAL_STATUS_BYTE_FLAGS_USER7                 128

/*- Defined values for 
	attribute KTMPXICHASSIS_ATTR_SYSTEM_SLOT_NEGOTIATED_LINK_SPEED
	attribute KTMPXICHASSIS_ATTR_PCIE_MAXIMUM_LINK_SPEED
	attribute KTMPXICHASSIS_ATTR_PCIE_NEGOTIATED_LINK_SPEED */

#define KTMPXICHASSIS_VAL_PCIE_LINK_SPEED_NO_CONNECTION        0
#define KTMPXICHASSIS_VAL_PCIE_LINK_SPEED_GEN1_2_5_GT_PER_SEC  1
#define KTMPXICHASSIS_VAL_PC_IE_LINK_SPEED_GEN2_5_0_GT_PER_SEC 2
#define KTMPXICHASSIS_VAL_PCIE_LINK_SPEED_GEN3_8_0_GT_PER_SEC  3

/*- Defined values for */

#define KTMPXICHASSIS_VAL_FLASH_WRITE_TYPE_MODE1            1
#define KTMPXICHASSIS_VAL_FLASH_WRITE_TYPE_MODE2            2
#define KTMPXICHASSIS_VAL_FLASH_WRITE_TYPE_MODE3            3
#define KTMPXICHASSIS_VAL_FLASH_WRITE_TYPE_MODE4            4
#define KTMPXICHASSIS_VAL_FLASH_WRITE_TYPE_MODE5            5

/*- Defined values for 
	attribute KTMPXICHASSIS_ATTR_REFCLK_SOURCE */

#define KTMPXICHASSIS_VAL_REF_CLOCK_SOURCE_INTERNAL         0
#define KTMPXICHASSIS_VAL_REF_CLOCK_SOURCE_EXTERNAL         1
#define KTMPXICHASSIS_VAL_REF_CLOCK_SOURCE_TIMING_MODULE    2

/*- Defined values for 
	attribute KTMPXICHASSIS_ATTR_TRIGGER_PORT_INPUT_DESTINATION
	attribute KTMPXICHASSIS_ATTR_TRIGGER_PORT_OUTPUT_SOURCE */

#define KTMPXICHASSIS_VAL_TRIGGER_NONE                      0
#define KTMPXICHASSIS_VAL_TRIGGER_PXI_TRIG0                 1
#define KTMPXICHASSIS_VAL_TRIGGER_PXI_TRIG1                 2
#define KTMPXICHASSIS_VAL_TRIGGER_PXI_TRIG2                 4
#define KTMPXICHASSIS_VAL_TRIGGER_PXI_TRIG3                 8
#define KTMPXICHASSIS_VAL_TRIGGER_PXI_TRIG4                 16
#define KTMPXICHASSIS_VAL_TRIGGER_PXI_TRIG5                 32
#define KTMPXICHASSIS_VAL_TRIGGER_PXI_TRIG6                 64
#define KTMPXICHASSIS_VAL_TRIGGER_PXI_TRIG7                 128

/*- Defined values for 
	attribute KTMPXICHASSIS_ATTR_TRIGGER_PORT_DRIVE_TYPE */

#define KTMPXICHASSIS_VAL_TRIGGER_PORT_DRIVE_TYPE_INPUT            0
#define KTMPXICHASSIS_VAL_TRIGGER_PORT_DRIVE_TYPE_PUSH_PULL_OUTPUT 1


/**************************************************************************** 
 *---------------- Instrument Driver Function Declarations -----------------* 
 ****************************************************************************/

/*- KtMPxiChassis */

ViStatus _VI_FUNC KtMPxiChassis_init(ViRsrc ResourceName, ViBoolean IdQuery, ViBoolean Reset, ViSession* Vi);
ViStatus _VI_FUNC KtMPxiChassis_close(ViSession Vi);
ViStatus _VI_FUNC KtMPxiChassis_InitWithOptions(ViRsrc ResourceName, ViBoolean IdQuery, ViBoolean Reset, ViConstString OptionsString, ViSession* Vi);

/*- System */

ViStatus _VI_FUNC KtMPxiChassis_SystemSelfTestErrorQuery(ViSession Vi, ViInt32* ErrorCode, ViInt32 ErrorMessageBufferSize, ViChar ErrorMessage[]);

/*- PCIeNegotiatedLink */

ViStatus _VI_FUNC KtMPxiChassis_GetPCIeNegotiatedLinkName(ViSession Vi, ViInt32 Index, ViInt32 NameBufferSize, ViChar Name[]);

/*- TemperatureSensor */

ViStatus _VI_FUNC KtMPxiChassis_GetTemperatureSensorName(ViSession Vi, ViInt32 Index, ViInt32 NameBufferSize, ViChar Name[]);
ViStatus _VI_FUNC KtMPxiChassis_GetTemperature(ViSession Vi, ViConstString TemperatureSensor, ViReal64* Temperature);

/*- Alarm */

ViStatus _VI_FUNC KtMPxiChassis_TemperatureAlarmClear(ViSession Vi);
ViStatus _VI_FUNC KtMPxiChassis_TemperatureAlarmConfigure(ViSession Vi, ViBoolean Enabled, ViInt32 MaxTemperature);
ViStatus _VI_FUNC KtMPxiChassis_GetTemperatureAlarm(ViSession Vi, ViBoolean* AlarmOccurred);

/*- VoltageRail */

ViStatus _VI_FUNC KtMPxiChassis_GetVoltageRailName(ViSession Vi, ViInt32 Index, ViInt32 NameBufferSize, ViChar Name[]);
ViStatus _VI_FUNC KtMPxiChassis_GetVoltage(ViSession Vi, ViConstString VoltageRail, ViReal64* Voltage);
ViStatus _VI_FUNC KtMPxiChassis_GetVoltageExpected(ViSession Vi, ViConstString VoltageRail, ViReal64* VoltageExpected);

/*- Alarm */

ViStatus _VI_FUNC KtMPxiChassis_VoltageAlarmClear(ViSession Vi, ViConstString VoltageRail);
ViStatus _VI_FUNC KtMPxiChassis_VoltageAlarmConfigure(ViSession Vi, ViConstString VoltageRail, ViBoolean Enabled, ViReal64 LowerLimit, ViReal64 UpperLevel);
ViStatus _VI_FUNC KtMPxiChassis_GetVoltageAlarm(ViSession Vi, ViConstString VoltageRail, ViBoolean* AlarmOccurred);

/*- Alarm */

ViStatus _VI_FUNC KtMPxiChassis_RefClkAlarmClear(ViSession Vi);
ViStatus _VI_FUNC KtMPxiChassis_GetRefClkAlarm(ViSession Vi, ViBoolean* AlarmOccurred);

/*- FanTray */

ViStatus _VI_FUNC KtMPxiChassis_GetFanTrayName(ViSession Vi, ViInt32 Index, ViInt32 NameBufferSize, ViChar Name[]);

/*- Fan */

ViStatus _VI_FUNC KtMPxiChassis_GetFanName(ViSession Vi, ViConstString FanTray, ViInt32 Index, ViInt32 NameBufferSize, ViChar Name[]);
ViStatus _VI_FUNC KtMPxiChassis_GetFanRPM(ViSession Vi, ViConstString Fan, ViInt32* FanRPM);

/*- Alarm */

ViStatus _VI_FUNC KtMPxiChassis_FanTrayAlarmClear(ViSession Vi, ViConstString FanTray);
ViStatus _VI_FUNC KtMPxiChassis_FanTrayAlarmConfigure(ViSession Vi, ViConstString FanTray, ViBoolean Enabled, ViInt32 MinRPM);
ViStatus _VI_FUNC KtMPxiChassis_GetFanTrayAlarm(ViSession Vi, ViConstString FanTray, ViBoolean* AlarmOccurred);

/*- TriggerPort */

ViStatus _VI_FUNC KtMPxiChassis_GetTriggerPortName(ViSession Vi, ViInt32 Index, ViInt32 NameBufferSize, ViChar Name[]);

/*- PeripheralSlot */

ViStatus _VI_FUNC KtMPxiChassis_GetPeripheralSlotName(ViSession Vi, ViInt32 Index, ViInt32 NameBufferSize, ViChar Name[]);

/*- Utility */

ViStatus _VI_FUNC KtMPxiChassis_revision_query(ViSession Vi, ViChar DriverRev[], ViChar InstrRev[]);
ViStatus _VI_FUNC KtMPxiChassis_error_message(ViSession Vi, ViStatus ErrorCode, ViChar ErrorMessage[]);
ViStatus _VI_FUNC KtMPxiChassis_GetError(ViSession Vi, ViStatus* ErrorCode, ViInt32 ErrorDescriptionBufferSize, ViChar ErrorDescription[]);
ViStatus _VI_FUNC KtMPxiChassis_ClearError(ViSession Vi);
ViStatus _VI_FUNC KtMPxiChassis_GetNextCoercionRecord(ViSession Vi, ViInt32 CoercionRecordBufferSize, ViChar CoercionRecord[]);
ViStatus _VI_FUNC KtMPxiChassis_InvalidateAllAttributes(ViSession Vi);
ViStatus _VI_FUNC KtMPxiChassis_Disable(ViSession Vi);
ViStatus _VI_FUNC KtMPxiChassis_error_query(ViSession Vi, ViInt32* ErrorCode, ViChar ErrorMessage[]);
ViStatus _VI_FUNC KtMPxiChassis_LockSession(ViSession Vi, ViBoolean* CallerHasLock);
ViStatus _VI_FUNC KtMPxiChassis_reset(ViSession Vi);
ViStatus _VI_FUNC KtMPxiChassis_ResetWithDefaults(ViSession Vi);
ViStatus _VI_FUNC KtMPxiChassis_self_test(ViSession Vi, ViInt16* TestResult, ViChar TestMessage[]);
ViStatus _VI_FUNC KtMPxiChassis_UnlockSession(ViSession Vi, ViBoolean* CallerHasLock);

/*- Attribute Accessors */

ViStatus _VI_FUNC KtMPxiChassis_GetAttributeViInt32(ViSession Vi, ViConstString RepCapIdentifier, ViAttr AttributeID, ViInt32* AttributeValue);
ViStatus _VI_FUNC KtMPxiChassis_GetAttributeViReal64(ViSession Vi, ViConstString RepCapIdentifier, ViAttr AttributeID, ViReal64* AttributeValue);
ViStatus _VI_FUNC KtMPxiChassis_GetAttributeViBoolean(ViSession Vi, ViConstString RepCapIdentifier, ViAttr AttributeID, ViBoolean* AttributeValue);
ViStatus _VI_FUNC KtMPxiChassis_GetAttributeViSession(ViSession Vi, ViConstString RepCapIdentifier, ViAttr AttributeID, ViSession* AttributeValue);
ViStatus _VI_FUNC KtMPxiChassis_GetAttributeViString(ViSession Vi, ViConstString RepCapIdentifier, ViAttr AttributeID, ViInt32 AttributeValueBufferSize, ViChar AttributeValue[]);
ViStatus _VI_FUNC KtMPxiChassis_SetAttributeViInt32(ViSession Vi, ViConstString RepCapIdentifier, ViAttr AttributeID, ViInt32 AttributeValue);
ViStatus _VI_FUNC KtMPxiChassis_SetAttributeViReal64(ViSession Vi, ViConstString RepCapIdentifier, ViAttr AttributeID, ViReal64 AttributeValue);
ViStatus _VI_FUNC KtMPxiChassis_SetAttributeViBoolean(ViSession Vi, ViConstString RepCapIdentifier, ViAttr AttributeID, ViBoolean AttributeValue);
ViStatus _VI_FUNC KtMPxiChassis_SetAttributeViSession(ViSession Vi, ViConstString RepCapIdentifier, ViAttr AttributeID, ViSession AttributeValue);
ViStatus _VI_FUNC KtMPxiChassis_SetAttributeViString(ViSession Vi, ViConstString RepCapIdentifier, ViAttr AttributeID, ViConstString AttributeValue);


/**************************************************************************** 
 *----------------- Instrument Error And Completion Codes ------------------* 
 ****************************************************************************/
#ifndef _IVIC_ERROR_BASE_DEFINES_
#define _IVIC_ERROR_BASE_DEFINES_

#define IVIC_WARN_BASE                           (0x3FFA0000L)
#define IVIC_CROSS_CLASS_WARN_BASE               (IVIC_WARN_BASE + 0x1000)
#define IVIC_CLASS_WARN_BASE                     (IVIC_WARN_BASE + 0x2000)
#define IVIC_SPECIFIC_WARN_BASE                  (IVIC_WARN_BASE + 0x4000)

#define IVIC_ERROR_BASE                          (0xBFFA0000L)
#define IVIC_CROSS_CLASS_ERROR_BASE              (IVIC_ERROR_BASE + 0x1000)
#define IVIC_CLASS_ERROR_BASE                    (IVIC_ERROR_BASE + 0x2000)
#define IVIC_SPECIFIC_ERROR_BASE                 (IVIC_ERROR_BASE + 0x4000)
#define IVIC_LXISYNC_ERROR_BASE                  (IVIC_ERROR_BASE + 0x2000)

#endif


#define KTMPXICHASSIS_ERROR_CANNOT_RECOVER                       (IVIC_ERROR_BASE + 0x0000)
#define KTMPXICHASSIS_ERROR_INSTRUMENT_STATUS                    (IVIC_ERROR_BASE + 0x0001)
#define KTMPXICHASSIS_ERROR_CANNOT_OPEN_FILE                     (IVIC_ERROR_BASE + 0x0002)
#define KTMPXICHASSIS_ERROR_READING_FILE                         (IVIC_ERROR_BASE + 0x0003)
#define KTMPXICHASSIS_ERROR_WRITING_FILE                         (IVIC_ERROR_BASE + 0x0004)
#define KTMPXICHASSIS_ERROR_INVALID_PATHNAME                     (IVIC_ERROR_BASE + 0x000B)
#define KTMPXICHASSIS_ERROR_INVALID_ATTRIBUTE                    (IVIC_ERROR_BASE + 0x000C)
#define KTMPXICHASSIS_ERROR_IVI_ATTR_NOT_WRITABLE                (IVIC_ERROR_BASE + 0x000D)
#define KTMPXICHASSIS_ERROR_IVI_ATTR_NOT_READABLE                (IVIC_ERROR_BASE + 0x000E)
#define KTMPXICHASSIS_ERROR_INVALID_VALUE                        (IVIC_ERROR_BASE + 0x0010)
#define KTMPXICHASSIS_ERROR_FUNCTION_NOT_SUPPORTED               (IVIC_ERROR_BASE + 0x0011)
#define KTMPXICHASSIS_ERROR_ATTRIBUTE_NOT_SUPPORTED              (IVIC_ERROR_BASE + 0x0012)
#define KTMPXICHASSIS_ERROR_VALUE_NOT_SUPPORTED                  (IVIC_ERROR_BASE + 0x0013)
#define KTMPXICHASSIS_ERROR_TYPES_DO_NOT_MATCH                   (IVIC_ERROR_BASE + 0x0015)
#define KTMPXICHASSIS_ERROR_NOT_INITIALIZED                      (IVIC_ERROR_BASE + 0x001D)
#define KTMPXICHASSIS_ERROR_UNKNOWN_CHANNEL_NAME                 (IVIC_ERROR_BASE + 0x0020)
#define KTMPXICHASSIS_ERROR_TOO_MANY_OPEN_FILES                  (IVIC_ERROR_BASE + 0x0023)
#define KTMPXICHASSIS_ERROR_CHANNEL_NAME_REQUIRED                (IVIC_ERROR_BASE + 0x0044)
#define KTMPXICHASSIS_ERROR_MISSING_OPTION_NAME                  (IVIC_ERROR_BASE + 0x0049)
#define KTMPXICHASSIS_ERROR_MISSING_OPTION_VALUE                 (IVIC_ERROR_BASE + 0x004A)
#define KTMPXICHASSIS_ERROR_BAD_OPTION_NAME                      (IVIC_ERROR_BASE + 0x004B)
#define KTMPXICHASSIS_ERROR_BAD_OPTION_VALUE                     (IVIC_ERROR_BASE + 0x004C)
#define KTMPXICHASSIS_ERROR_OUT_OF_MEMORY                        (IVIC_ERROR_BASE + 0x0056)
#define KTMPXICHASSIS_ERROR_OPERATION_PENDING                    (IVIC_ERROR_BASE + 0x0057)
#define KTMPXICHASSIS_ERROR_NULL_POINTER                         (IVIC_ERROR_BASE + 0x0058)
#define KTMPXICHASSIS_ERROR_UNEXPECTED_RESPONSE                  (IVIC_ERROR_BASE + 0x0059)
#define KTMPXICHASSIS_ERROR_FILE_NOT_FOUND                       (IVIC_ERROR_BASE + 0x005B)
#define KTMPXICHASSIS_ERROR_INVALID_FILE_FORMAT                  (IVIC_ERROR_BASE + 0x005C)
#define KTMPXICHASSIS_ERROR_STATUS_NOT_AVAILABLE                 (IVIC_ERROR_BASE + 0x005D)
#define KTMPXICHASSIS_ERROR_ID_QUERY_FAILED                      (IVIC_ERROR_BASE + 0x005E)
#define KTMPXICHASSIS_ERROR_RESET_FAILED                         (IVIC_ERROR_BASE + 0x005F)
#define KTMPXICHASSIS_ERROR_RESOURCE_UNKNOWN                     (IVIC_ERROR_BASE + 0x0060)
#define KTMPXICHASSIS_ERROR_ALREADY_INITIALIZED                  (IVIC_ERROR_BASE + 0x0061)
#define KTMPXICHASSIS_ERROR_CANNOT_CHANGE_SIMULATION_STATE       (IVIC_ERROR_BASE + 0x0062)
#define KTMPXICHASSIS_ERROR_INVALID_NUMBER_OF_LEVELS_IN_SELECTOR (IVIC_ERROR_BASE + 0x0063)
#define KTMPXICHASSIS_ERROR_INVALID_RANGE_IN_SELECTOR            (IVIC_ERROR_BASE + 0x0064)
#define KTMPXICHASSIS_ERROR_UNKOWN_NAME_IN_SELECTOR              (IVIC_ERROR_BASE + 0x0065)
#define KTMPXICHASSIS_ERROR_BADLY_FORMED_SELECTOR                (IVIC_ERROR_BASE + 0x0066)
#define KTMPXICHASSIS_ERROR_UNKNOWN_PHYSICAL_IDENTIFIER          (IVIC_ERROR_BASE + 0x0067)
#define KTMPXICHASSIS_ERROR_INVALID_SESSION_HANDLE               (IVIC_ERROR_BASE + 0x1190)



#define KTMPXICHASSIS_SUCCESS                               0
#define KTMPXICHASSIS_WARN_NSUP_ID_QUERY                    (IVIC_WARN_BASE + 0x0065)
#define KTMPXICHASSIS_WARN_NSUP_RESET                       (IVIC_WARN_BASE + 0x0066)
#define KTMPXICHASSIS_WARN_NSUP_SELF_TEST                   (IVIC_WARN_BASE + 0x0067)
#define KTMPXICHASSIS_WARN_NSUP_ERROR_QUERY                 (IVIC_WARN_BASE + 0x0068)
#define KTMPXICHASSIS_WARN_NSUP_REV_QUERY                   (IVIC_WARN_BASE + 0x0069)



#define KTMPXICHASSIS_ERROR_IO_GENERAL                      (IVIC_SPECIFIC_ERROR_BASE + 0x0214)
#define KTMPXICHASSIS_ERROR_IO_TIMEOUT                      (IVIC_SPECIFIC_ERROR_BASE + 0x0215)
#define KTMPXICHASSIS_ERROR_CHASSIS_API                     (IVIC_SPECIFIC_ERROR_BASE + 0x0216)
#define KTMPXICHASSIS_ERROR_VISA_API                        (IVIC_SPECIFIC_ERROR_BASE + 0x0217)



#define KTMPXICHASSIS_WARN_SELF_TEST_RECOMMENDED            (IVIC_SPECIFIC_WARN_BASE + 0x0001)


/**************************************************************************** 
 *---------------------------- End Include File ----------------------------* 
 ****************************************************************************/
#if defined(__cplusplus) || defined(__cplusplus__)
}
#endif
#endif // __KTMPXICHASSIS_HEADER
