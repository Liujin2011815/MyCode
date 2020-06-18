/******************************************************************************
 *                                                                         
 * © Keysight Technologies 2010-2017
 *
 *****************************************************************************/

#ifndef __AGM9018_HEADER
#define __AGM9018_HEADER

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

#define AGM9018_ATTR_SPECIFIC_DRIVER_DESCRIPTION              (IVI_INHERENT_ATTR_BASE + 514L)  /* ViString, read-only */
#define AGM9018_ATTR_SPECIFIC_DRIVER_PREFIX                   (IVI_INHERENT_ATTR_BASE + 302L)  /* ViString, read-only */
#define AGM9018_ATTR_SPECIFIC_DRIVER_VENDOR                   (IVI_INHERENT_ATTR_BASE + 513L)  /* ViString, read-only */
#define AGM9018_ATTR_SPECIFIC_DRIVER_REVISION                 (IVI_INHERENT_ATTR_BASE + 551L)  /* ViString, read-only */
#define AGM9018_ATTR_SPECIFIC_DRIVER_CLASS_SPEC_MAJOR_VERSION (IVI_INHERENT_ATTR_BASE + 515L)  /* ViInt32, read-only */
#define AGM9018_ATTR_SPECIFIC_DRIVER_CLASS_SPEC_MINOR_VERSION (IVI_INHERENT_ATTR_BASE + 516L)  /* ViInt32, read-only */

/*- User Options */

#define AGM9018_ATTR_RANGE_CHECK                            (IVI_INHERENT_ATTR_BASE + 2L)  /* ViBoolean, read-write */
#define AGM9018_ATTR_QUERY_INSTRUMENT_STATUS                (IVI_INHERENT_ATTR_BASE + 3L)  /* ViBoolean, read-write */
#define AGM9018_ATTR_CACHE                                  (IVI_INHERENT_ATTR_BASE + 4L)  /* ViBoolean, read-write */
#define AGM9018_ATTR_SIMULATE                               (IVI_INHERENT_ATTR_BASE + 5L)  /* ViBoolean, read-write */
#define AGM9018_ATTR_RECORD_COERCIONS                       (IVI_INHERENT_ATTR_BASE + 6L)  /* ViBoolean, read-write */
#define AGM9018_ATTR_INTERCHANGE_CHECK                      (IVI_INHERENT_ATTR_BASE + 21L)  /* ViBoolean, read-write */

/*- Advanced Session Information */

#define AGM9018_ATTR_LOGICAL_NAME                           (IVI_INHERENT_ATTR_BASE + 305L)  /* ViString, read-only */
#define AGM9018_ATTR_IO_RESOURCE_DESCRIPTOR                 (IVI_INHERENT_ATTR_BASE + 304L)  /* ViString, read-only */
#define AGM9018_ATTR_DRIVER_SETUP                           (IVI_INHERENT_ATTR_BASE + 7L)  /* ViString, read-only */

/*- Driver Capabilities */

#define AGM9018_ATTR_GROUP_CAPABILITIES                     (IVI_INHERENT_ATTR_BASE + 401L)  /* ViString, read-only */
#define AGM9018_ATTR_SUPPORTED_INSTRUMENT_MODELS            (IVI_INHERENT_ATTR_BASE + 327L)  /* ViString, read-only */

/*- Instrument Identification */

#define AGM9018_ATTR_INSTRUMENT_FIRMWARE_REVISION           (IVI_INHERENT_ATTR_BASE + 510L)  /* ViString, read-only */
#define AGM9018_ATTR_INSTRUMENT_MANUFACTURER                (IVI_INHERENT_ATTR_BASE + 511L)  /* ViString, read-only */
#define AGM9018_ATTR_INSTRUMENT_MODEL                       (IVI_INHERENT_ATTR_BASE + 512L)  /* ViString, read-only */


/*===== Instrument-Specific Attributes =====================================*/

/*- Instrument Specific */

#define AGM9018_ATTR_PCIE_LINK                              (IVI_SPECIFIC_ATTR_BASE + 22L)  /* ViString, read-only */

/*- System */

#define AGM9018_ATTR_SERIAL_NUMBER                          (IVI_SPECIFIC_ATTR_BASE + 1L)  /* ViString, read-only */
#define AGM9018_ATTR_TRACE_ENABLED                          (IVI_SPECIFIC_ATTR_BASE + 2L)  /* ViBoolean, read-write */
#define AGM9018_ATTR_SYSTEM_UPTIME                          (IVI_SPECIFIC_ATTR_BASE + 29L)  /* ViReal64, read-only */
#define AGM9018_ATTR_SELFTEST_ERROR_COUNT                   (IVI_SPECIFIC_ATTR_BASE + 34L)  /* ViInt32, read-only */

/*- TemperatureSensor */

#define AGM9018_ATTR_TEMPERATURESENSOR_COUNT                (IVI_SPECIFIC_ATTR_BASE + 3L)  /* ViInt32, read-only */
#define AGM9018_ATTR_TEMPERATURE                            (IVI_SPECIFIC_ATTR_BASE + 12L)  /* ViReal64, read-only */

/*- Alarm */

#define AGM9018_ATTR_TEMPERATURE_ALARM_OCCURRED             (IVI_SPECIFIC_ATTR_BASE + 8L)  /* ViBoolean, read-only */
#define AGM9018_ATTR_TEMPERATURE_ALARM_ENABLED              (IVI_SPECIFIC_ATTR_BASE + 9L)  /* ViBoolean, read-write */
#define AGM9018_ATTR_TEMPERATURE_ALARM_MAX_TEMPERATURE      (IVI_SPECIFIC_ATTR_BASE + 10L)  /* ViInt32, read-write */

/*- Fan */

#define AGM9018_ATTR_FAN_COUNT                              (IVI_SPECIFIC_ATTR_BASE + 4L)  /* ViInt32, read-only */
#define AGM9018_ATTR_FAN_RPM                                (IVI_SPECIFIC_ATTR_BASE + 13L)  /* ViInt32, read-only */

/*- Alarm */

#define AGM9018_ATTR_FAN_ALARM_OCCURRED                     (IVI_SPECIFIC_ATTR_BASE + 5L)  /* ViBoolean, read-only */
#define AGM9018_ATTR_FAN_ALARM_ENABLED                      (IVI_SPECIFIC_ATTR_BASE + 6L)  /* ViBoolean, read-write */
#define AGM9018_ATTR_FAN_ALARM_MIN_RPM                      (IVI_SPECIFIC_ATTR_BASE + 7L)  /* ViInt32, read-write */

/*- Control */

#define AGM9018_ATTR_FAN_CONTROL_AUTO                       (IVI_SPECIFIC_ATTR_BASE + 33L)  /* ViBoolean, read-only */
#define AGM9018_ATTR_FAN_CONTROL_MAX_RPM_TEMPERATURE        (IVI_SPECIFIC_ATTR_BASE + 14L)  /* ViInt32, read-write */

/*- ReferenceClock */

#define AGM9018_ATTR_REFCLK_SOURCE                          (IVI_SPECIFIC_ATTR_BASE + 20L)  /* ViInt32, read-only */

/*- Alarm */

#define AGM9018_ATTR_REFCLK_ALARM_OCCURRED                  (IVI_SPECIFIC_ATTR_BASE + 31L)  /* ViBoolean, read-only */
#define AGM9018_ATTR_REFCLK_ALARM_ENABLED                   (IVI_SPECIFIC_ATTR_BASE + 32L)  /* ViBoolean, read-write */

/*- VoltageRail */

#define AGM9018_ATTR_VOLTAGERAIL_COUNT                      (IVI_SPECIFIC_ATTR_BASE + 23L)  /* ViInt32, read-only */
#define AGM9018_ATTR_VOLTAGE                                (IVI_SPECIFIC_ATTR_BASE + 28L)  /* ViReal64, read-only */
#define AGM9018_ATTR_EXPECTED_VOLTAGE                       (IVI_SPECIFIC_ATTR_BASE + 30L)  /* ViReal64, read-only */

/*- Alarm */

#define AGM9018_ATTR_VOLTAGE_ALARM_OCCURRED                 (IVI_SPECIFIC_ATTR_BASE + 24L)  /* ViBoolean, read-only */
#define AGM9018_ATTR_VOLTAGE_ALARM_ENABLED                  (IVI_SPECIFIC_ATTR_BASE + 25L)  /* ViBoolean, read-write */
#define AGM9018_ATTR_VOLTAGE_ALARM_UPPER_LIMIT              (IVI_SPECIFIC_ATTR_BASE + 26L)  /* ViReal64, read-write */
#define AGM9018_ATTR_VOLTAGE_ALARM_LOWER_LIMIT              (IVI_SPECIFIC_ATTR_BASE + 27L)  /* ViReal64, read-write */


/**************************************************************************** 
 *------------------------ Attribute Value Defines -------------------------* 
 ****************************************************************************/

/*- Defined values for 
	attribute AGM9018_ATTR_REFCLK_SOURCE */

#define AGM9018_VAL_REF_CLOCK_SOURCE_INTERNAL               0
#define AGM9018_VAL_REF_CLOCK_SOURCE_EXTERNAL               1
#define AGM9018_VAL_REF_CLOCK_SOURCE_TIMING_MODULE          2

/*- Defined values for 
	parameter BusConfiguration in function AgM9018_TriggerBusConnect
	parameter BusConfiguration in function AgM9018_TriggerBusConnection */

#define AGM9018_VAL_TRIG_BUS_ISOLATE_ALL                    0
#define AGM9018_VAL_TRIG_BUS_1_TO2                          1
#define AGM9018_VAL_TRIG_BUS_1_TO2_TO3                      2
#define AGM9018_VAL_TRIG_BUS_2_TO1                          3
#define AGM9018_VAL_TRIG_BUS_2_TO3                          4
#define AGM9018_VAL_TRIG_BUS_2_TO1_AND3                     5
#define AGM9018_VAL_TRIG_BUS_3_TO2                          6
#define AGM9018_VAL_TRIG_BUS_3_TO2_TO1                      7


/**************************************************************************** 
 *---------------- Instrument Driver Function Declarations -----------------* 
 ****************************************************************************/

/*- AgM9018 */

ViStatus _VI_FUNC AgM9018_init ( ViRsrc ResourceName, ViBoolean IdQuery, ViBoolean Reset, ViSession* Vi );
ViStatus _VI_FUNC AgM9018_close ( ViSession Vi );
ViStatus _VI_FUNC AgM9018_InitWithOptions ( ViRsrc ResourceName, ViBoolean IdQuery, ViBoolean Reset, ViConstString OptionsString, ViSession* Vi );

/*- Utility */

ViStatus _VI_FUNC AgM9018_revision_query ( ViSession Vi, ViChar DriverRev[], ViChar InstrRev[] );
ViStatus _VI_FUNC AgM9018_error_message ( ViSession Vi, ViStatus ErrorCode, ViChar ErrorMessage[] );
ViStatus _VI_FUNC AgM9018_GetError ( ViSession Vi, ViStatus* ErrorCode, ViInt32 ErrorDescriptionBufferSize, ViChar ErrorDescription[] );
ViStatus _VI_FUNC AgM9018_ClearError ( ViSession Vi );
ViStatus _VI_FUNC AgM9018_ClearInterchangeWarnings ( ViSession Vi );
ViStatus _VI_FUNC AgM9018_GetNextCoercionRecord ( ViSession Vi, ViInt32 CoercionRecordBufferSize, ViChar CoercionRecord[] );
ViStatus _VI_FUNC AgM9018_GetNextInterchangeWarning ( ViSession Vi, ViInt32 InterchangeWarningBufferSize, ViChar InterchangeWarning[] );
ViStatus _VI_FUNC AgM9018_InvalidateAllAttributes ( ViSession Vi );
ViStatus _VI_FUNC AgM9018_ResetInterchangeCheck ( ViSession Vi );
ViStatus _VI_FUNC AgM9018_Disable ( ViSession Vi );
ViStatus _VI_FUNC AgM9018_error_query ( ViSession Vi, ViInt32* ErrorCode, ViChar ErrorMessage[] );
ViStatus _VI_FUNC AgM9018_LockSession ( ViSession Vi, ViBoolean* CallerHasLock );
ViStatus _VI_FUNC AgM9018_reset ( ViSession Vi );
ViStatus _VI_FUNC AgM9018_ResetWithDefaults ( ViSession Vi );
ViStatus _VI_FUNC AgM9018_self_test ( ViSession Vi, ViInt16* TestResult, ViChar TestMessage[] );
ViStatus _VI_FUNC AgM9018_UnlockSession ( ViSession Vi, ViBoolean* CallerHasLock );

/*- Attribute Accessors */

ViStatus _VI_FUNC AgM9018_GetAttributeViInt32 ( ViSession Vi, ViConstString RepCapIdentifier, ViAttr AttributeID, ViInt32* AttributeValue );
ViStatus _VI_FUNC AgM9018_GetAttributeViReal64 ( ViSession Vi, ViConstString RepCapIdentifier, ViAttr AttributeID, ViReal64* AttributeValue );
ViStatus _VI_FUNC AgM9018_GetAttributeViBoolean ( ViSession Vi, ViConstString RepCapIdentifier, ViAttr AttributeID, ViBoolean* AttributeValue );
ViStatus _VI_FUNC AgM9018_GetAttributeViSession ( ViSession Vi, ViConstString RepCapIdentifier, ViAttr AttributeID, ViSession* AttributeValue );
ViStatus _VI_FUNC AgM9018_GetAttributeViString ( ViSession Vi, ViConstString RepCapIdentifier, ViAttr AttributeID, ViInt32 AttributeValueBufferSize, ViChar AttributeValue[] );
ViStatus _VI_FUNC AgM9018_SetAttributeViInt32 ( ViSession Vi, ViConstString RepCapIdentifier, ViAttr AttributeID, ViInt32 AttributeValue );
ViStatus _VI_FUNC AgM9018_SetAttributeViReal64 ( ViSession Vi, ViConstString RepCapIdentifier, ViAttr AttributeID, ViReal64 AttributeValue );
ViStatus _VI_FUNC AgM9018_SetAttributeViBoolean ( ViSession Vi, ViConstString RepCapIdentifier, ViAttr AttributeID, ViBoolean AttributeValue );
ViStatus _VI_FUNC AgM9018_SetAttributeViSession ( ViSession Vi, ViConstString RepCapIdentifier, ViAttr AttributeID, ViSession AttributeValue );
ViStatus _VI_FUNC AgM9018_SetAttributeViString ( ViSession Vi, ViConstString RepCapIdentifier, ViAttr AttributeID, ViConstString AttributeValue );

/*- System */

ViStatus _VI_FUNC AgM9018_SelfTestErrorQuery ( ViSession Vi, ViInt32* ErrorCode, ViInt32 ErrorMessageBufferSize, ViChar ErrorMessage[] );

/*- TemperatureSensor */

ViStatus _VI_FUNC AgM9018_GetTemperatureSensorName ( ViSession Vi, ViInt32 Index, ViInt32 NameBufferSize, ViChar Name[] );
ViStatus _VI_FUNC AgM9018_GetTemperature ( ViSession Vi, ViConstString TemperatureSensor, ViReal64* Temperature );

/*- Alarm */

ViStatus _VI_FUNC AgM9018_TemperatureAlarmClear ( ViSession Vi );
ViStatus _VI_FUNC AgM9018_GetTemperatureAlarm ( ViSession Vi, ViBoolean* AlarmOccurred );
ViStatus _VI_FUNC AgM9018_TemperatureAlarmConfigure ( ViSession Vi, ViBoolean Enabled, ViInt32 MaxTemperature );

/*- Fan */

ViStatus _VI_FUNC AgM9018_GetFanName ( ViSession Vi, ViInt32 Index, ViInt32 NameBufferSize, ViChar Name[] );
ViStatus _VI_FUNC AgM9018_GetFanRPM ( ViSession Vi, ViConstString Fan, ViInt32* RPM );

/*- Alarm */

ViStatus _VI_FUNC AgM9018_FanAlarmClear ( ViSession Vi );
ViStatus _VI_FUNC AgM9018_GetFanAlarm ( ViSession Vi, ViBoolean* AlarmOccurred );
ViStatus _VI_FUNC AgM9018_FanAlarmConfigure ( ViSession Vi, ViBoolean Enabled, ViInt32 MinRPM );

/*- Alarm */

ViStatus _VI_FUNC AgM9018_RefClkAlarmClear ( ViSession Vi );
ViStatus _VI_FUNC AgM9018_GetRefClkAlarm ( ViSession Vi, ViBoolean* AlarmOccurred );

/*- TriggerBus */

ViStatus _VI_FUNC AgM9018_TriggerBusConnect ( ViSession Vi, ViInt32 Trig, ViInt32 BusConfiguration );
ViStatus _VI_FUNC AgM9018_TriggerBusDisconnect ( ViSession Vi );
ViStatus _VI_FUNC AgM9018_TriggerBusConnectDefault ( ViSession Vi );
ViStatus _VI_FUNC AgM9018_TriggerBusConnection ( ViSession Vi, ViInt32 Trig, ViInt32* BusConfiguration );

/*- VoltageRail */

ViStatus _VI_FUNC AgM9018_GetVoltageRailName ( ViSession Vi, ViInt32 Index, ViInt32 NameBufferSize, ViChar Name[] );
ViStatus _VI_FUNC AgM9018_GetVoltage ( ViSession Vi, ViConstString VoltageRail, ViReal64* Voltage );
ViStatus _VI_FUNC AgM9018_GetExpectedVoltage ( ViSession Vi, ViConstString VoltageRail, ViReal64* ExpectedVoltage );

/*- Alarm */

ViStatus _VI_FUNC AgM9018_VoltageAlarmClear ( ViSession Vi, ViConstString VoltageRail );
ViStatus _VI_FUNC AgM9018_GetVoltageAlarm ( ViSession Vi, ViConstString VoltageRail, ViBoolean* AlarmOccurred );
ViStatus _VI_FUNC AgM9018_VoltageAlarmConfigure ( ViSession Vi, ViConstString VoltageRail, ViBoolean Enabled, ViReal64 LowerLimit, ViReal64 UpperLimit );


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


#define AGM9018_ERROR_CANNOT_RECOVER                        (IVIC_ERROR_BASE + 0x0000)
#define AGM9018_ERROR_INSTRUMENT_STATUS                     (IVIC_ERROR_BASE + 0x0001)
#define AGM9018_ERROR_CANNOT_OPEN_FILE                      (IVIC_ERROR_BASE + 0x0002)
#define AGM9018_ERROR_READING_FILE                          (IVIC_ERROR_BASE + 0x0003)
#define AGM9018_ERROR_WRITING_FILE                          (IVIC_ERROR_BASE + 0x0004)
#define AGM9018_ERROR_INVALID_PATHNAME                      (IVIC_ERROR_BASE + 0x000B)
#define AGM9018_ERROR_INVALID_VALUE                         (IVIC_ERROR_BASE + 0x0010)
#define AGM9018_ERROR_FUNCTION_NOT_SUPPORTED                (IVIC_ERROR_BASE + 0x0011)
#define AGM9018_ERROR_ATTRIBUTE_NOT_SUPPORTED               (IVIC_ERROR_BASE + 0x0012)
#define AGM9018_ERROR_VALUE_NOT_SUPPORTED                   (IVIC_ERROR_BASE + 0x0013)
#define AGM9018_ERROR_NOT_INITIALIZED                       (IVIC_ERROR_BASE + 0x001D)
#define AGM9018_ERROR_UNKNOWN_CHANNEL_NAME                  (IVIC_ERROR_BASE + 0x0020)
#define AGM9018_ERROR_TOO_MANY_OPEN_FILES                   (IVIC_ERROR_BASE + 0x0023)
#define AGM9018_ERROR_CHANNEL_NAME_REQUIRED                 (IVIC_ERROR_BASE + 0x0044)
#define AGM9018_ERROR_MISSING_OPTION_NAME                   (IVIC_ERROR_BASE + 0x0049)
#define AGM9018_ERROR_MISSING_OPTION_VALUE                  (IVIC_ERROR_BASE + 0x004A)
#define AGM9018_ERROR_BAD_OPTION_NAME                       (IVIC_ERROR_BASE + 0x004B)
#define AGM9018_ERROR_BAD_OPTION_VALUE                      (IVIC_ERROR_BASE + 0x004C)
#define AGM9018_ERROR_OUT_OF_MEMORY                         (IVIC_ERROR_BASE + 0x0056)
#define AGM9018_ERROR_OPERATION_PENDING                     (IVIC_ERROR_BASE + 0x0057)
#define AGM9018_ERROR_NULL_POINTER                          (IVIC_ERROR_BASE + 0x0058)
#define AGM9018_ERROR_UNEXPECTED_RESPONSE                   (IVIC_ERROR_BASE + 0x0059)
#define AGM9018_ERROR_FILE_NOT_FOUND                        (IVIC_ERROR_BASE + 0x005B)
#define AGM9018_ERROR_INVALID_FILE_FORMAT                   (IVIC_ERROR_BASE + 0x005C)
#define AGM9018_ERROR_STATUS_NOT_AVAILABLE                  (IVIC_ERROR_BASE + 0x005D)
#define AGM9018_ERROR_ID_QUERY_FAILED                       (IVIC_ERROR_BASE + 0x005E)
#define AGM9018_ERROR_RESET_FAILED                          (IVIC_ERROR_BASE + 0x005F)
#define AGM9018_ERROR_RESOURCE_UNKNOWN                      (IVIC_ERROR_BASE + 0x0060)
#define AGM9018_ERROR_ALREADY_INITIALIZED                   (IVIC_ERROR_BASE + 0x0061)
#define AGM9018_ERROR_CANNOT_CHANGE_SIMULATION_STATE        (IVIC_ERROR_BASE + 0x0062)
#define AGM9018_ERROR_INVALID_NUMBER_OF_LEVELS_IN_SELECTOR  (IVIC_ERROR_BASE + 0x0063)
#define AGM9018_ERROR_INVALID_RANGE_IN_SELECTOR             (IVIC_ERROR_BASE + 0x0064)
#define AGM9018_ERROR_UNKOWN_NAME_IN_SELECTOR               (IVIC_ERROR_BASE + 0x0065)
#define AGM9018_ERROR_BADLY_FORMED_SELECTOR                 (IVIC_ERROR_BASE + 0x0066)
#define AGM9018_ERROR_UNKNOWN_PHYSICAL_IDENTIFIER           (IVIC_ERROR_BASE + 0x0067)
#define AGM9018_ERROR_INVALID_ATTRIBUTE                     (IVIC_ERROR_BASE + 0x000C)
#define AGM9018_ERROR_TYPES_DO_NOT_MATCH                    (IVIC_ERROR_BASE + 0x0015)
#define AGM9018_ERROR_IVI_ATTR_NOT_WRITABLE                 (IVIC_ERROR_BASE + 0x000D)
#define AGM9018_ERROR_IVI_ATTR_NOT_READABLE                 (IVIC_ERROR_BASE + 0x000E)
#define AGM9018_ERROR_INVALID_SESSION_HANDLE                (IVIC_ERROR_BASE + 0x1190)



#define AGM9018_SUCCESS                                     0
#define AGM9018_WARN_NSUP_ID_QUERY                          (IVIC_WARN_BASE + 0x0065)
#define AGM9018_WARN_NSUP_RESET                             (IVIC_WARN_BASE + 0x0066)
#define AGM9018_WARN_NSUP_SELF_TEST                         (IVIC_WARN_BASE + 0x0067)
#define AGM9018_WARN_NSUP_ERROR_QUERY                       (IVIC_WARN_BASE + 0x0068)
#define AGM9018_WARN_NSUP_REV_QUERY                         (IVIC_WARN_BASE + 0x0069)



#define AGM9018_ERROR_IO_GENERAL                            (IVIC_SPECIFIC_ERROR_BASE + 0x0214)
#define AGM9018_ERROR_IO_TIMEOUT                            (IVIC_SPECIFIC_ERROR_BASE + 0x0215)
#define AGM9018_ERROR_MODEL_NOT_SUPPORTED                   (IVIC_SPECIFIC_ERROR_BASE + 0x0216)
#define AGM9018_ERROR_PERSONALITY_NOT_ACTIVE                (IVIC_SPECIFIC_ERROR_BASE + 0x0211)
#define AGM9018_ERROR_PERSONALITY_NOT_LICENSED              (IVIC_SPECIFIC_ERROR_BASE + 0x0213)
#define AGM9018_ERROR_PERSONALITY_NOT_INSTALLED             (IVIC_SPECIFIC_ERROR_BASE + 0x0212)
#define AGM9018_ERROR_VISA_API                              (IVIC_SPECIFIC_ERROR_BASE + 0x0001)
#define AGM9018_ERROR_CHASSIS_API                           (IVIC_SPECIFIC_ERROR_BASE + 0x0002)
#define AGM9018_ERROR_UNEXPECTED                            (IVIC_SPECIFIC_ERROR_BASE + 0x0003)
#define AGM9018_ERROR_INTERNAL_SW                           (IVIC_SPECIFIC_ERROR_BASE + 0x0004)
#define AGM9018_ERROR_SELF_TEST_RECOMMENDED                 (IVIC_SPECIFIC_ERROR_BASE + 0x0005)
#define AGM9018_ERROR_TRIGGER_MANAGER_INIT_FAILED           (IVIC_SPECIFIC_ERROR_BASE + 0x0384)




/**************************************************************************** 
 *---------------------------- End Include File ----------------------------* 
 ****************************************************************************/
#if defined(__cplusplus) || defined(__cplusplus__)
}
#endif
#endif // __AGM9018_HEADER
