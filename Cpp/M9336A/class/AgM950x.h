/******************************************************************************
 *                                                                         
 * © Keysight Technologies 2011-2017
 *
 *****************************************************************************/

#ifndef __AGM950X_HEADER
#define __AGM950X_HEADER

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

#define AGM950X_ATTR_SPECIFIC_DRIVER_DESCRIPTION              (IVI_INHERENT_ATTR_BASE + 514L)  /* ViString, read-only */
#define AGM950X_ATTR_SPECIFIC_DRIVER_PREFIX                   (IVI_INHERENT_ATTR_BASE + 302L)  /* ViString, read-only */
#define AGM950X_ATTR_SPECIFIC_DRIVER_VENDOR                   (IVI_INHERENT_ATTR_BASE + 513L)  /* ViString, read-only */
#define AGM950X_ATTR_SPECIFIC_DRIVER_REVISION                 (IVI_INHERENT_ATTR_BASE + 551L)  /* ViString, read-only */
#define AGM950X_ATTR_SPECIFIC_DRIVER_CLASS_SPEC_MAJOR_VERSION (IVI_INHERENT_ATTR_BASE + 515L)  /* ViInt32, read-only */
#define AGM950X_ATTR_SPECIFIC_DRIVER_CLASS_SPEC_MINOR_VERSION (IVI_INHERENT_ATTR_BASE + 516L)  /* ViInt32, read-only */

/*- User Options */

#define AGM950X_ATTR_RANGE_CHECK                            (IVI_INHERENT_ATTR_BASE + 2L)  /* ViBoolean, read-write */
#define AGM950X_ATTR_QUERY_INSTRUMENT_STATUS                (IVI_INHERENT_ATTR_BASE + 3L)  /* ViBoolean, read-write */
#define AGM950X_ATTR_CACHE                                  (IVI_INHERENT_ATTR_BASE + 4L)  /* ViBoolean, read-write */
#define AGM950X_ATTR_SIMULATE                               (IVI_INHERENT_ATTR_BASE + 5L)  /* ViBoolean, read-write */
#define AGM950X_ATTR_RECORD_COERCIONS                       (IVI_INHERENT_ATTR_BASE + 6L)  /* ViBoolean, read-write */
#define AGM950X_ATTR_INTERCHANGE_CHECK                      (IVI_INHERENT_ATTR_BASE + 21L)  /* ViBoolean, read-write */

/*- Advanced Session Information */

#define AGM950X_ATTR_LOGICAL_NAME                           (IVI_INHERENT_ATTR_BASE + 305L)  /* ViString, read-only */
#define AGM950X_ATTR_IO_RESOURCE_DESCRIPTOR                 (IVI_INHERENT_ATTR_BASE + 304L)  /* ViString, read-only */
#define AGM950X_ATTR_DRIVER_SETUP                           (IVI_INHERENT_ATTR_BASE + 7L)  /* ViString, read-only */

/*- Driver Capabilities */

#define AGM950X_ATTR_GROUP_CAPABILITIES                     (IVI_INHERENT_ATTR_BASE + 401L)  /* ViString, read-only */
#define AGM950X_ATTR_SUPPORTED_INSTRUMENT_MODELS            (IVI_INHERENT_ATTR_BASE + 327L)  /* ViString, read-only */

/*- Instrument Identification */

#define AGM950X_ATTR_INSTRUMENT_FIRMWARE_REVISION           (IVI_INHERENT_ATTR_BASE + 510L)  /* ViString, read-only */
#define AGM950X_ATTR_INSTRUMENT_MANUFACTURER                (IVI_INHERENT_ATTR_BASE + 511L)  /* ViString, read-only */
#define AGM950X_ATTR_INSTRUMENT_MODEL                       (IVI_INHERENT_ATTR_BASE + 512L)  /* ViString, read-only */


/*===== Instrument-Specific Attributes =====================================*/

/*- ThresholdSensor */

#define AGM950X_ATTR_THRESHOLDSENSOR_COUNT                           (IVI_SPECIFIC_ATTR_BASE + 1L)  /* ViInt32, read-only */
#define AGM950X_ATTR_THRESHOLDSENSOR_VALUE                           (IVI_SPECIFIC_ATTR_BASE + 2L)  /* ViReal64, read-only */
#define AGM950X_ATTR_THRESHOLDSENSOR_RAW_VALUE                       (IVI_SPECIFIC_ATTR_BASE + 3L)  /* ViInt32, read-only */
#define AGM950X_ATTR_THRESHOLDSENSOR_ID                              (IVI_SPECIFIC_ATTR_BASE + 4L)  /* ViInt32, read-only */
#define AGM950X_ATTR_THRESHOLDSENSOR_IPMB_ADDRESS                    (IVI_SPECIFIC_ATTR_BASE + 5L)  /* ViInt32, read-only */
#define AGM950X_ATTR_THRESHOLDSENSOR_MANUFACTURER_NAME               (IVI_SPECIFIC_ATTR_BASE + 7L)  /* ViString, read-only */
#define AGM950X_ATTR_THRESHOLDSENSOR_SLOT_NUMBER                     (IVI_SPECIFIC_ATTR_BASE + 8L)  /* ViInt32, read-only */
#define AGM950X_ATTR_THRESHOLDSENSOR_TYPE_STRING                     (IVI_SPECIFIC_ATTR_BASE + 9L)  /* ViString, read-only */
#define AGM950X_ATTR_THRESHOLDSENSOR_ALARM_CONDITION                 (IVI_SPECIFIC_ATTR_BASE + 10L)  /* ViInt32, read-only */
#define AGM950X_ATTR_THRESHOLDSENSOR_LUN                             (IVI_SPECIFIC_ATTR_BASE + 11L)  /* ViInt32, read-only */
#define AGM950X_ATTR_THRESHOLDSENSOR_TYPE                            (IVI_SPECIFIC_ATTR_BASE + 31L)  /* ViInt32, read-only */
#define AGM950X_ATTR_THRESHOLDSENSOR_NOMINAL_READING                 (IVI_SPECIFIC_ATTR_BASE + 32L)  /* ViReal64, read-only */
#define AGM950X_ATTR_THRESHOLDSENSOR_UPPER_NON_RECOVERABLE_THRESHOLD (IVI_SPECIFIC_ATTR_BASE + 33L)  /* ViReal64, read-only */
#define AGM950X_ATTR_THRESHOLDSENSOR_UPPER_CRITICAL_THRESHOLD        (IVI_SPECIFIC_ATTR_BASE + 34L)  /* ViReal64, read-only */
#define AGM950X_ATTR_THRESHOLDSENSOR_UPPER_NON_CRITICAL_THRESHOLD    (IVI_SPECIFIC_ATTR_BASE + 35L)  /* ViReal64, read-only */
#define AGM950X_ATTR_THRESHOLDSENSOR_LOWER_NON_RECOVERABLE_THRESHOLD (IVI_SPECIFIC_ATTR_BASE + 36L)  /* ViReal64, read-only */
#define AGM950X_ATTR_THRESHOLDSENSOR_LOWER_CRITICAL_THRESHOLD        (IVI_SPECIFIC_ATTR_BASE + 37L)  /* ViReal64, read-only */
#define AGM950X_ATTR_THRESHOLDSENSOR_LOWER_NON_CRITICAL_THRESHOLD    (IVI_SPECIFIC_ATTR_BASE + 38L)  /* ViReal64, read-only */
#define AGM950X_ATTR_THRESHOLDSENSOR_THRESHOLD_ENABLE_MASK           (IVI_SPECIFIC_ATTR_BASE + 39L)  /* ViInt32, read-only */
#define AGM950X_ATTR_THRESHOLDSENSOR_BELONGS_TO_ENTITY_FRU           (IVI_SPECIFIC_ATTR_BASE + 50L)  /* ViInt32, read-only */
#define AGM950X_ATTR_THRESHOLDSENSOR_EVENT_STATUS                    (IVI_SPECIFIC_ATTR_BASE + 51L)  /* ViInt32, read-only */

/*- FanTray */

#define AGM950X_ATTR_FANTRAY_COUNT                          (IVI_SPECIFIC_ATTR_BASE + 12L)  /* ViInt32, read-only */
#define AGM950X_ATTR_FANTRAY_CURRENT_SPEED_LEVEL            (IVI_SPECIFIC_ATTR_BASE + 13L)  /* ViInt32, read-write */
#define AGM950X_ATTR_FANTRAY_DYNAMIC_MINIMUM_FAN_LEVEL      (IVI_SPECIFIC_ATTR_BASE + 43L)  /* ViInt32, read-write */
#define AGM950X_ATTR_FANTRAY_MINIMUM_SPEED_LEVEL            (IVI_SPECIFIC_ATTR_BASE + 44L)  /* ViInt32, read-only */
#define AGM950X_ATTR_FANTRAY_MAXIMUM_SPEED_LEVEL            (IVI_SPECIFIC_ATTR_BASE + 45L)  /* ViInt32, read-only */
#define AGM950X_ATTR_FANTRAY_IPMB_ADDRESS                   (IVI_SPECIFIC_ATTR_BASE + 46L)  /* ViInt32, read-only */
#define AGM950X_ATTR_FANTRAY_FRU                            (IVI_SPECIFIC_ATTR_BASE + 47L)  /* ViInt32, read-only */

/*- Slot */

#define AGM950X_ATTR_SLOT_COUNT                             (IVI_SPECIFIC_ATTR_BASE + 14L)  /* ViInt32, read-only */
#define AGM950X_ATTR_SLOT_PART_NUMBER                       (IVI_SPECIFIC_ATTR_BASE + 15L)  /* ViString, read-only */
#define AGM950X_ATTR_SLOT_PRODUCT_NAME                      (IVI_SPECIFIC_ATTR_BASE + 16L)  /* ViString, read-only */
#define AGM950X_ATTR_SLOT_REVISION                          (IVI_SPECIFIC_ATTR_BASE + 17L)  /* ViString, read-only */
#define AGM950X_ATTR_SLOT_SERIAL_NUMBER                     (IVI_SPECIFIC_ATTR_BASE + 18L)  /* ViString, read-only */
#define AGM950X_ATTR_SLOT_SLOT_NUMBER                       (IVI_SPECIFIC_ATTR_BASE + 19L)  /* ViInt32, read-only */
#define AGM950X_ATTR_SLOT_IS_PRESENT                        (IVI_SPECIFIC_ATTR_BASE + 20L)  /* ViBoolean, read-only */
#define AGM950X_ATTR_SLOT_IS_ACTIVE                         (IVI_SPECIFIC_ATTR_BASE + 21L)  /* ViBoolean, read-only */
#define AGM950X_ATTR_SLOT_HOT_SWAP_STATE                    (IVI_SPECIFIC_ATTR_BASE + 40L)  /* ViInt32, read-only */
#define AGM950X_ATTR_SLOT_IPMB_ADDRESS                      (IVI_SPECIFIC_ATTR_BASE + 52L)  /* ViInt32, read-only */
#define AGM950X_ATTR_SLOT_FRU                               (IVI_SPECIFIC_ATTR_BASE + 53L)  /* ViInt32, read-only */

/*- DiscreteSensor */

#define AGM950X_ATTR_DISCRETESENSOR_COUNT                   (IVI_SPECIFIC_ATTR_BASE + 22L)  /* ViInt32, read-only */
#define AGM950X_ATTR_DISCRETESENSOR_ID                      (IVI_SPECIFIC_ATTR_BASE + 23L)  /* ViInt32, read-only */
#define AGM950X_ATTR_DISCRETESENSOR_IPMB_ADDRESS            (IVI_SPECIFIC_ATTR_BASE + 24L)  /* ViInt32, read-only */
#define AGM950X_ATTR_DISCRETESENSOR_LUN                     (IVI_SPECIFIC_ATTR_BASE + 25L)  /* ViInt32, read-only */
#define AGM950X_ATTR_DISCRETESENSOR_MANUFACTURER_NAME       (IVI_SPECIFIC_ATTR_BASE + 26L)  /* ViString, read-only */
#define AGM950X_ATTR_DISCRETESENSOR_BITMAPPED_VALUE         (IVI_SPECIFIC_ATTR_BASE + 27L)  /* ViInt32, read-only */
#define AGM950X_ATTR_DISCRETESENSOR_SLOT_NUMBER             (IVI_SPECIFIC_ATTR_BASE + 28L)  /* ViInt32, read-only */
#define AGM950X_ATTR_DISCRETESENSOR_TYPE_STRING             (IVI_SPECIFIC_ATTR_BASE + 29L)  /* ViString, read-only */
#define AGM950X_ATTR_DISCRETESENSOR_TYPE                    (IVI_SPECIFIC_ATTR_BASE + 30L)  /* ViInt32, read-only */
#define AGM950X_ATTR_DISCRETESENSOR_BELONGS_TO_ENTITY_FRU   (IVI_SPECIFIC_ATTR_BASE + 54L)  /* ViInt32, read-only */
#define AGM950X_ATTR_DISCRETESENSOR_EVENT_STATUS            (IVI_SPECIFIC_ATTR_BASE + 55L)  /* ViInt32, read-only */

/*- System */

#define AGM950X_ATTR_SERIAL_NUMBER                          (IVI_SPECIFIC_ATTR_BASE + 41L)  /* ViString, read-only */
#define AGM950X_ATTR_TRACE_ENABLED                          (IVI_SPECIFIC_ATTR_BASE + 42L)  /* ViBoolean, read-write */


/**************************************************************************** 
 *------------------------ Attribute Value Defines -------------------------* 
 ****************************************************************************/

/*- Defined values for 
	attribute AGM950X_ATTR_THRESHOLDSENSOR_ALARM_CONDITION
	parameter AlarmCondition in function AgM950x_ThresholdSensorGetReading */

#define AGM950X_VAL_ALARM_CONDITION_NOMINAL                 5
#define AGM950X_VAL_ALARM_CONDITION_LOWER_NON_CRITICAL      4
#define AGM950X_VAL_ALARM_CONDITION_LOWER_CRITICAL          3
#define AGM950X_VAL_ALARM_CONDITION_LOWER_NON_RECOVERABLE   2
#define AGM950X_VAL_ALARM_CONDITION_UPPER_NON_CRITICAL      6
#define AGM950X_VAL_ALARM_CONDITION_UPPER_CRITICAL          7
#define AGM950X_VAL_ALARM_CONDITION_UPPER_NON_RECOVERABLE   8

/*- Defined values for 
	attribute AGM950X_ATTR_SLOT_HOT_SWAP_STATE
	parameter HotSwapState in function AgM950x_SlotGetHotSwapState */

#define AGM950X_VAL_HOT_SWAP_STATE_NOT_PRESENT              0
#define AGM950X_VAL_HOT_SWAP_STATE_PRESENT                  1
#define AGM950X_VAL_HOT_SWAP_STATE_ACTIVATION_REQUEST       2
#define AGM950X_VAL_HOT_SWAP_STATE_ACTIVATION_IN_PROGRESS   3
#define AGM950X_VAL_HOT_SWAP_STATE_ACTIVE                   4
#define AGM950X_VAL_HOT_SWAP_STATE_DEACTIVATION_REQUEST     5
#define AGM950X_VAL_HOT_SWAP_STATE_DEACTIVATION_IN_PROGRESS 6
#define AGM950X_VAL_HOT_SWAP_STATE_COMMUNICATION_LOST       7

/*- Defined values for 
	attribute AGM950X_ATTR_THRESHOLDSENSOR_THRESHOLD_ENABLE_MASK
	parameter ThresholdEnableMask in function AgM950x_ThresholdSensorGetThresholds */

#define AGM950X_VAL_ALARM_ENABLE_MASK_UPPER_NON_RECOVERABLE 32
#define AGM950X_VAL_ALARM_ENABLE_MASK_LOWER_NON_RECOVERABLE 16
#define AGM950X_VAL_ALARM_ENABLE_MASK_UPPER_CRITICAL        8
#define AGM950X_VAL_ALARM_ENABLE_MASK_LOWER_CRITICAL        4
#define AGM950X_VAL_ALARM_ENABLE_MASK_UPPER_NON_CRITICAL    2
#define AGM950X_VAL_ALARM_ENABLE_MASK_LOWER_NON_CRITICAL    1

/*- Defined values for 
	attribute AGM950X_ATTR_THRESHOLDSENSOR_EVENT_STATUS
	attribute AGM950X_ATTR_DISCRETESENSOR_EVENT_STATUS
	parameter EventStatus in function AgM950x_ThresholdSensorGetEventStatus
	parameter EventStatus in function AgM950x_DiscreteSensorGetEventStatus */

#define AGM950X_VAL_SENSOR_EVENT_STATUS_MESSAGES_ENABLED    128
#define AGM950X_VAL_SENSOR_EVENT_STATUS_SCANNING_ENABLED    64
#define AGM950X_VAL_SENSOR_EVENT_STATUS_UNAVAILABLE         32


/**************************************************************************** 
 *---------------- Instrument Driver Function Declarations -----------------* 
 ****************************************************************************/

/*- AgM950x */

ViStatus _VI_FUNC AgM950x_init ( ViRsrc ResourceName, ViBoolean IdQuery, ViBoolean Reset, ViSession* Vi );
ViStatus _VI_FUNC AgM950x_close ( ViSession Vi );
ViStatus _VI_FUNC AgM950x_InitWithOptions ( ViRsrc ResourceName, ViBoolean IdQuery, ViBoolean Reset, ViConstString OptionsString, ViSession* Vi );

/*- Utility */

ViStatus _VI_FUNC AgM950x_revision_query ( ViSession Vi, ViChar DriverRev[], ViChar InstrRev[] );
ViStatus _VI_FUNC AgM950x_error_message ( ViSession Vi, ViStatus ErrorCode, ViChar ErrorMessage[] );
ViStatus _VI_FUNC AgM950x_GetError ( ViSession Vi, ViStatus* ErrorCode, ViInt32 ErrorDescriptionBufferSize, ViChar ErrorDescription[] );
ViStatus _VI_FUNC AgM950x_ClearError ( ViSession Vi );
ViStatus _VI_FUNC AgM950x_ClearInterchangeWarnings ( ViSession Vi );
ViStatus _VI_FUNC AgM950x_GetNextCoercionRecord ( ViSession Vi, ViInt32 CoercionRecordBufferSize, ViChar CoercionRecord[] );
ViStatus _VI_FUNC AgM950x_GetNextInterchangeWarning ( ViSession Vi, ViInt32 InterchangeWarningBufferSize, ViChar InterchangeWarning[] );
ViStatus _VI_FUNC AgM950x_InvalidateAllAttributes ( ViSession Vi );
ViStatus _VI_FUNC AgM950x_ResetInterchangeCheck ( ViSession Vi );
ViStatus _VI_FUNC AgM950x_Disable ( ViSession Vi );
ViStatus _VI_FUNC AgM950x_error_query ( ViSession Vi, ViInt32* ErrorCode, ViChar ErrorMessage[] );
ViStatus _VI_FUNC AgM950x_LockSession ( ViSession Vi, ViBoolean* CallerHasLock );
ViStatus _VI_FUNC AgM950x_reset ( ViSession Vi );
ViStatus _VI_FUNC AgM950x_ResetWithDefaults ( ViSession Vi );
ViStatus _VI_FUNC AgM950x_self_test ( ViSession Vi, ViInt16* TestResult, ViChar TestMessage[] );
ViStatus _VI_FUNC AgM950x_UnlockSession ( ViSession Vi, ViBoolean* CallerHasLock );

/*- Attribute Accessors */

ViStatus _VI_FUNC AgM950x_GetAttributeViInt32 ( ViSession Vi, ViConstString RepCapIdentifier, ViAttr AttributeID, ViInt32* AttributeValue );
ViStatus _VI_FUNC AgM950x_GetAttributeViReal64 ( ViSession Vi, ViConstString RepCapIdentifier, ViAttr AttributeID, ViReal64* AttributeValue );
ViStatus _VI_FUNC AgM950x_GetAttributeViBoolean ( ViSession Vi, ViConstString RepCapIdentifier, ViAttr AttributeID, ViBoolean* AttributeValue );
ViStatus _VI_FUNC AgM950x_GetAttributeViSession ( ViSession Vi, ViConstString RepCapIdentifier, ViAttr AttributeID, ViSession* AttributeValue );
ViStatus _VI_FUNC AgM950x_GetAttributeViString ( ViSession Vi, ViConstString RepCapIdentifier, ViAttr AttributeID, ViInt32 AttributeValueBufferSize, ViChar AttributeValue[] );
ViStatus _VI_FUNC AgM950x_SetAttributeViInt32 ( ViSession Vi, ViConstString RepCapIdentifier, ViAttr AttributeID, ViInt32 AttributeValue );
ViStatus _VI_FUNC AgM950x_SetAttributeViReal64 ( ViSession Vi, ViConstString RepCapIdentifier, ViAttr AttributeID, ViReal64 AttributeValue );
ViStatus _VI_FUNC AgM950x_SetAttributeViBoolean ( ViSession Vi, ViConstString RepCapIdentifier, ViAttr AttributeID, ViBoolean AttributeValue );
ViStatus _VI_FUNC AgM950x_SetAttributeViSession ( ViSession Vi, ViConstString RepCapIdentifier, ViAttr AttributeID, ViSession AttributeValue );
ViStatus _VI_FUNC AgM950x_SetAttributeViString ( ViSession Vi, ViConstString RepCapIdentifier, ViAttr AttributeID, ViConstString AttributeValue );

/*- ThresholdSensor */

ViStatus _VI_FUNC AgM950x_GetThresholdSensorName ( ViSession Vi, ViInt32 Index, ViInt32 NameBufferSize, ViChar Name[] );
ViStatus _VI_FUNC AgM950x_ThresholdSensorGetLocation ( ViSession Vi, ViConstString ThresholdSensor, ViInt32* SlotNumber, ViInt32* IPMBAddress, ViInt32* LUN, ViInt32* ID );
ViStatus _VI_FUNC AgM950x_ThresholdSensorGetReading ( ViSession Vi, ViConstString ThresholdSensor, ViReal64* Value, ViInt32* AlarmCondition );
ViStatus _VI_FUNC AgM950x_ThresholdSensorGetThresholds ( ViSession Vi, ViConstString ThresholdSensor, ViReal64* LowerNonRecoverableThreshold, ViReal64* LowerCriticalThreshold, ViReal64* LowerNonCriticalThreshold, ViReal64* UpperNonCriticalThreshold, ViReal64* UpperCriticalThreshold, ViReal64* UpperNonRecoverableThreshold, ViInt32* ThresholdEnableMask );
ViStatus _VI_FUNC AgM950x_ThresholdSensorGetID ( ViSession Vi, ViConstString ThresholdSensor, ViInt32* ID );
ViStatus _VI_FUNC AgM950x_ThresholdSensorGetIPMBAddress ( ViSession Vi, ViConstString ThresholdSensor, ViInt32* IPMBAddress );
ViStatus _VI_FUNC AgM950x_ThresholdSensorGetLUN ( ViSession Vi, ViConstString ThresholdSensor, ViInt32* LUN );
ViStatus _VI_FUNC AgM950x_ThresholdSensorGetManufacturerName ( ViSession Vi, ViConstString ThresholdSensor, ViInt32 ManufacturerNameBufferSize, ViChar ManufacturerName[] );
ViStatus _VI_FUNC AgM950x_ThresholdSensorGetSlotNumber ( ViSession Vi, ViConstString ThresholdSensor, ViInt32* SlotNumber );
ViStatus _VI_FUNC AgM950x_ThresholdSensorGetValue ( ViSession Vi, ViConstString ThresholdSensor, ViReal64* Value );
ViStatus _VI_FUNC AgM950x_ThresholdSensorGetNominalReading ( ViSession Vi, ViConstString ThresholdSensor, ViReal64* NominalReading );
ViStatus _VI_FUNC AgM950x_ThresholdSensorGetEventStatus ( ViSession Vi, ViConstString ThresholdSensor, ViInt32* EventStatus );
ViStatus _VI_FUNC AgM950x_ThresholdSensorGetBelongsToEntityFRU ( ViSession Vi, ViConstString ThresholdSensor, ViInt32* BelongsToEntityFRU );

/*- FanTray */

ViStatus _VI_FUNC AgM950x_GetFanTrayName ( ViSession Vi, ViInt32 Index, ViInt32 NameBufferSize, ViChar Name[] );
ViStatus _VI_FUNC AgM950x_FanTrayGetMaximumSpeedLevel ( ViSession Vi, ViConstString FanTray, ViInt32* MaximumSpeedLevel );
ViStatus _VI_FUNC AgM950x_FanTrayGetMinimumSpeedLevel ( ViSession Vi, ViConstString FanTray, ViInt32* MinimumSpeedLevel );
ViStatus _VI_FUNC AgM950x_FanTrayGetIPMBAddress ( ViSession Vi, ViConstString FanTray, ViInt32* IPMBAddress );
ViStatus _VI_FUNC AgM950x_FanTrayGetFRU ( ViSession Vi, ViConstString FanTray, ViInt32* FRU );
ViStatus _VI_FUNC AgM950x_FanTrayGetDynamicMinimumFanLevel ( ViSession Vi, ViConstString FanTray, ViInt32* DynamicMinimumFanLevel );
ViStatus _VI_FUNC AgM950x_FanTraySetDynamicMinimumFanLevel ( ViSession Vi, ViConstString FanTray, ViInt32 DynamicMinimumFanLevel );
ViStatus _VI_FUNC AgM950x_FanTrayGetCurrentSpeedLevel ( ViSession Vi, ViConstString FanTray, ViInt32* CurrentSpeedLevel );
ViStatus _VI_FUNC AgM950x_FanTraySetCurrentSpeedLevel ( ViSession Vi, ViConstString FanTray, ViInt32 CurrentSpeedLevel );

/*- Slot */

ViStatus _VI_FUNC AgM950x_GetSlotName ( ViSession Vi, ViInt32 Index, ViInt32 NameBufferSize, ViChar Name[] );
ViStatus _VI_FUNC AgM950x_SlotGetHotSwapState ( ViSession Vi, ViConstString Slot, ViInt32* HotSwapState );
ViStatus _VI_FUNC AgM950x_SlotGetIsActive ( ViSession Vi, ViConstString Slot, ViBoolean* IsActive );
ViStatus _VI_FUNC AgM950x_SlotGetIsPresent ( ViSession Vi, ViConstString Slot, ViBoolean* IsPresent );
ViStatus _VI_FUNC AgM950x_SlotGetProductInformation ( ViSession Vi, ViConstString Slot, ViInt32 PartNumberBufferSize, ViChar PartNumber[], ViInt32 ProductNameBufferSize, ViChar ProductName[], ViInt32 RevisionBufferSize, ViChar Revision[], ViInt32 SerialNumberBufferSize, ViChar SerialNumber[] );
ViStatus _VI_FUNC AgM950x_SlotGetSlotNumber ( ViSession Vi, ViConstString Slot, ViInt32* SlotNumber );
ViStatus _VI_FUNC AgM950x_SlotGetIPMBAddress ( ViSession Vi, ViConstString Slot, ViInt32* IPMBAddress );
ViStatus _VI_FUNC AgM950x_SlotGetFRU ( ViSession Vi, ViConstString Slot, ViInt32* FRU );

/*- DiscreteSensor */

ViStatus _VI_FUNC AgM950x_GetDiscreteSensorName ( ViSession Vi, ViInt32 Index, ViInt32 NameBufferSize, ViChar Name[] );
ViStatus _VI_FUNC AgM950x_DiscreteSensorGetReading ( ViSession Vi, ViConstString DiscreteSensor, ViInt32* BitmappedValue );
ViStatus _VI_FUNC AgM950x_DiscreteSensorGetLocation ( ViSession Vi, ViConstString DiscreteSensor, ViInt32* SlotNumber, ViInt32* IPMBAddress, ViInt32* LUN, ViInt32* ID );
ViStatus _VI_FUNC AgM950x_DiscreteSensorGetEventStatus ( ViSession Vi, ViConstString DiscreteSensor, ViInt32* EventStatus );
ViStatus _VI_FUNC AgM950x_DiscreteSensorGetBelongsToEntityFRU ( ViSession Vi, ViConstString DiscreteSensor, ViInt32* BelongsToEntityFRU );


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


#define AGM950X_ERROR_CANNOT_RECOVER                        (IVIC_ERROR_BASE + 0x0000)
#define AGM950X_ERROR_INSTRUMENT_STATUS                     (IVIC_ERROR_BASE + 0x0001)
#define AGM950X_ERROR_CANNOT_OPEN_FILE                      (IVIC_ERROR_BASE + 0x0002)
#define AGM950X_ERROR_READING_FILE                          (IVIC_ERROR_BASE + 0x0003)
#define AGM950X_ERROR_WRITING_FILE                          (IVIC_ERROR_BASE + 0x0004)
#define AGM950X_ERROR_INVALID_PATHNAME                      (IVIC_ERROR_BASE + 0x000B)
#define AGM950X_ERROR_INVALID_VALUE                         (IVIC_ERROR_BASE + 0x0010)
#define AGM950X_ERROR_FUNCTION_NOT_SUPPORTED                (IVIC_ERROR_BASE + 0x0011)
#define AGM950X_ERROR_ATTRIBUTE_NOT_SUPPORTED               (IVIC_ERROR_BASE + 0x0012)
#define AGM950X_ERROR_VALUE_NOT_SUPPORTED                   (IVIC_ERROR_BASE + 0x0013)
#define AGM950X_ERROR_NOT_INITIALIZED                       (IVIC_ERROR_BASE + 0x001D)
#define AGM950X_ERROR_UNKNOWN_CHANNEL_NAME                  (IVIC_ERROR_BASE + 0x0020)
#define AGM950X_ERROR_TOO_MANY_OPEN_FILES                   (IVIC_ERROR_BASE + 0x0023)
#define AGM950X_ERROR_CHANNEL_NAME_REQUIRED                 (IVIC_ERROR_BASE + 0x0044)
#define AGM950X_ERROR_MISSING_OPTION_NAME                   (IVIC_ERROR_BASE + 0x0049)
#define AGM950X_ERROR_MISSING_OPTION_VALUE                  (IVIC_ERROR_BASE + 0x004A)
#define AGM950X_ERROR_BAD_OPTION_NAME                       (IVIC_ERROR_BASE + 0x004B)
#define AGM950X_ERROR_BAD_OPTION_VALUE                      (IVIC_ERROR_BASE + 0x004C)
#define AGM950X_ERROR_OUT_OF_MEMORY                         (IVIC_ERROR_BASE + 0x0056)
#define AGM950X_ERROR_OPERATION_PENDING                     (IVIC_ERROR_BASE + 0x0057)
#define AGM950X_ERROR_NULL_POINTER                          (IVIC_ERROR_BASE + 0x0058)
#define AGM950X_ERROR_UNEXPECTED_RESPONSE                   (IVIC_ERROR_BASE + 0x0059)
#define AGM950X_ERROR_FILE_NOT_FOUND                        (IVIC_ERROR_BASE + 0x005B)
#define AGM950X_ERROR_INVALID_FILE_FORMAT                   (IVIC_ERROR_BASE + 0x005C)
#define AGM950X_ERROR_STATUS_NOT_AVAILABLE                  (IVIC_ERROR_BASE + 0x005D)
#define AGM950X_ERROR_ID_QUERY_FAILED                       (IVIC_ERROR_BASE + 0x005E)
#define AGM950X_ERROR_RESET_FAILED                          (IVIC_ERROR_BASE + 0x005F)
#define AGM950X_ERROR_RESOURCE_UNKNOWN                      (IVIC_ERROR_BASE + 0x0060)
#define AGM950X_ERROR_ALREADY_INITIALIZED                   (IVIC_ERROR_BASE + 0x0061)
#define AGM950X_ERROR_CANNOT_CHANGE_SIMULATION_STATE        (IVIC_ERROR_BASE + 0x0062)
#define AGM950X_ERROR_INVALID_NUMBER_OF_LEVELS_IN_SELECTOR  (IVIC_ERROR_BASE + 0x0063)
#define AGM950X_ERROR_INVALID_RANGE_IN_SELECTOR             (IVIC_ERROR_BASE + 0x0064)
#define AGM950X_ERROR_UNKOWN_NAME_IN_SELECTOR               (IVIC_ERROR_BASE + 0x0065)
#define AGM950X_ERROR_BADLY_FORMED_SELECTOR                 (IVIC_ERROR_BASE + 0x0066)
#define AGM950X_ERROR_UNKNOWN_PHYSICAL_IDENTIFIER           (IVIC_ERROR_BASE + 0x0067)
#define AGM950X_ERROR_INVALID_ATTRIBUTE                     (IVIC_ERROR_BASE + 0x000C)
#define AGM950X_ERROR_TYPES_DO_NOT_MATCH                    (IVIC_ERROR_BASE + 0x0015)
#define AGM950X_ERROR_IVI_ATTR_NOT_WRITABLE                 (IVIC_ERROR_BASE + 0x000D)
#define AGM950X_ERROR_IVI_ATTR_NOT_READABLE                 (IVIC_ERROR_BASE + 0x000E)
#define AGM950X_ERROR_INVALID_SESSION_HANDLE                (IVIC_ERROR_BASE + 0x1190)



#define AGM950X_SUCCESS                                     0
#define AGM950X_WARN_NSUP_ID_QUERY                          (IVIC_WARN_BASE + 0x0065)
#define AGM950X_WARN_NSUP_RESET                             (IVIC_WARN_BASE + 0x0066)
#define AGM950X_WARN_NSUP_SELF_TEST                         (IVIC_WARN_BASE + 0x0067)
#define AGM950X_WARN_NSUP_ERROR_QUERY                       (IVIC_WARN_BASE + 0x0068)
#define AGM950X_WARN_NSUP_REV_QUERY                         (IVIC_WARN_BASE + 0x0069)



#define AGM950X_ERROR_IO_GENERAL                            (IVIC_SPECIFIC_ERROR_BASE + 0x0214)
#define AGM950X_ERROR_IO_TIMEOUT                            (IVIC_SPECIFIC_ERROR_BASE + 0x0215)
#define AGM950X_ERROR_MODEL_NOT_SUPPORTED                   (IVIC_SPECIFIC_ERROR_BASE + 0x0216)
#define AGM950X_ERROR_PERSONALITY_NOT_ACTIVE                (IVIC_SPECIFIC_ERROR_BASE + 0x0211)
#define AGM950X_ERROR_PERSONALITY_NOT_LICENSED              (IVIC_SPECIFIC_ERROR_BASE + 0x0213)
#define AGM950X_ERROR_PERSONALITY_NOT_INSTALLED             (IVIC_SPECIFIC_ERROR_BASE + 0x0212)
#define AGM950X_ERROR_VISA_API                              (IVIC_SPECIFIC_ERROR_BASE + 0x0001)
#define AGM950X_ERROR_CHASSIS_API                           (IVIC_SPECIFIC_ERROR_BASE + 0x0002)
#define AGM950X_ERROR_UNEXPECTED                            (IVIC_SPECIFIC_ERROR_BASE + 0x0003)
#define AGM950X_ERROR_INTERNAL_SW                           (IVIC_SPECIFIC_ERROR_BASE + 0x0004)




/**************************************************************************** 
 *---------------------------- End Include File ----------------------------* 
 ****************************************************************************/
#if defined(__cplusplus) || defined(__cplusplus__)
}
#endif
#endif // __AGM950X_HEADER
