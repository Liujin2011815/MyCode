/******************************************************************************
 *                                                                         
 * © Keysight Technologies 2014-2018
 *
 *****************************************************************************/

#ifndef __AGPXIPC_HEADER
#define __AGPXIPC_HEADER

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

#define AGPXIPC_ATTR_SPECIFIC_DRIVER_DESCRIPTION              (IVI_INHERENT_ATTR_BASE + 514L)  /* ViString, read-only */
#define AGPXIPC_ATTR_SPECIFIC_DRIVER_PREFIX                   (IVI_INHERENT_ATTR_BASE + 302L)  /* ViString, read-only */
#define AGPXIPC_ATTR_SPECIFIC_DRIVER_VENDOR                   (IVI_INHERENT_ATTR_BASE + 513L)  /* ViString, read-only */
#define AGPXIPC_ATTR_SPECIFIC_DRIVER_REVISION                 (IVI_INHERENT_ATTR_BASE + 551L)  /* ViString, read-only */
#define AGPXIPC_ATTR_SPECIFIC_DRIVER_CLASS_SPEC_MAJOR_VERSION (IVI_INHERENT_ATTR_BASE + 515L)  /* ViInt32, read-only */
#define AGPXIPC_ATTR_SPECIFIC_DRIVER_CLASS_SPEC_MINOR_VERSION (IVI_INHERENT_ATTR_BASE + 516L)  /* ViInt32, read-only */

/*- User Options */

#define AGPXIPC_ATTR_RANGE_CHECK                            (IVI_INHERENT_ATTR_BASE + 2L)  /* ViBoolean, read-write */
#define AGPXIPC_ATTR_QUERY_INSTRUMENT_STATUS                (IVI_INHERENT_ATTR_BASE + 3L)  /* ViBoolean, read-write */
#define AGPXIPC_ATTR_CACHE                                  (IVI_INHERENT_ATTR_BASE + 4L)  /* ViBoolean, read-write */
#define AGPXIPC_ATTR_SIMULATE                               (IVI_INHERENT_ATTR_BASE + 5L)  /* ViBoolean, read-write */
#define AGPXIPC_ATTR_RECORD_COERCIONS                       (IVI_INHERENT_ATTR_BASE + 6L)  /* ViBoolean, read-write */
#define AGPXIPC_ATTR_INTERCHANGE_CHECK                      (IVI_INHERENT_ATTR_BASE + 21L)  /* ViBoolean, read-write */

/*- Advanced Session Information */

#define AGPXIPC_ATTR_LOGICAL_NAME                           (IVI_INHERENT_ATTR_BASE + 305L)  /* ViString, read-only */
#define AGPXIPC_ATTR_IO_RESOURCE_DESCRIPTOR                 (IVI_INHERENT_ATTR_BASE + 304L)  /* ViString, read-only */
#define AGPXIPC_ATTR_DRIVER_SETUP                           (IVI_INHERENT_ATTR_BASE + 7L)  /* ViString, read-only */

/*- Driver Capabilities */

#define AGPXIPC_ATTR_GROUP_CAPABILITIES                     (IVI_INHERENT_ATTR_BASE + 401L)  /* ViString, read-only */
#define AGPXIPC_ATTR_SUPPORTED_INSTRUMENT_MODELS            (IVI_INHERENT_ATTR_BASE + 327L)  /* ViString, read-only */

/*- Instrument Identification */

#define AGPXIPC_ATTR_INSTRUMENT_FIRMWARE_REVISION           (IVI_INHERENT_ATTR_BASE + 510L)  /* ViString, read-only */
#define AGPXIPC_ATTR_INSTRUMENT_MANUFACTURER                (IVI_INHERENT_ATTR_BASE + 511L)  /* ViString, read-only */
#define AGPXIPC_ATTR_INSTRUMENT_MODEL                       (IVI_INHERENT_ATTR_BASE + 512L)  /* ViString, read-only */


/*===== Instrument-Specific Attributes =====================================*/

/*- System */

#define AGPXIPC_ATTR_SERIAL_NUMBER                          (IVI_SPECIFIC_ATTR_BASE + 1L)  /* ViString, read-only */
#define AGPXIPC_ATTR_TRACE_ENABLED                          (IVI_SPECIFIC_ATTR_BASE + 2L)  /* ViBoolean, read-write */

/*- TriggerRouting */

#define AGPXIPC_ATTR_TRIGGERROUTING_ENABLED                      (IVI_SPECIFIC_ATTR_BASE + 3L)  /* ViBoolean, read-only */
#define AGPXIPC_ATTR_TRIGGERROUTING_SOFTWARE_ROUTE_TRIGGER_STATE (IVI_SPECIFIC_ATTR_BASE + 5L)  /* ViBoolean, read-write */
#define AGPXIPC_ATTR_TRIGGERROUTING_ROUTE_CONFIGURATION          (IVI_SPECIFIC_ATTR_BASE + 6L)  /* ViInt32, read-only */
#define AGPXIPC_ATTR_TRIGGERROUTING_PXI_TRIG                     (IVI_SPECIFIC_ATTR_BASE + 7L)  /* ViInt32, read-only */


/**************************************************************************** 
 *------------------------ Attribute Value Defines -------------------------* 
 ****************************************************************************/

/*- Defined values for 
	attribute AGPXIPC_ATTR_TRIGGERROUTING_ROUTE_CONFIGURATION
	parameter RouteConfiguration in function AgPxiPc_TriggerRoutingSetRoute
	parameter RouteConfiguration in function AgPxiPc_TriggerRoutingGetRoute
	parameter RouteConfiguration in function AgPxiPc_TriggerRoutingGetRouteConfiguration */

#define AGPXIPC_VAL_TRIGGER_ROUTE_EXTERNAL_TO_TRIGGER_BUS              0
#define AGPXIPC_VAL_TRIGGER_ROUTE_TRIGGER_BUS_TO_EXTERNAL              1
#define AGPXIPC_VAL_TRIGGER_ROUTE_SOFTWARE_TO_TRIGGER_BUS              2
#define AGPXIPC_VAL_TRIGGER_ROUTE_SOFTWARE_TO_TRIGGER_BUS_AND_EXTERNAL 3
#define AGPXIPC_VAL_TRIGGER_ROUTE_NONE                                 4

/*- Defined values for 
	attribute AGPXIPC_ATTR_TRIGGERROUTING_PXI_TRIG
	parameter PxiTrig in function AgPxiPc_TriggerRoutingSetRoute
	parameter PxiTrig in function AgPxiPc_TriggerRoutingGetRoute
	parameter PxiTrig in function AgPxiPc_TriggerRoutingGetPxiTrig */

#define AGPXIPC_VAL_PXI_TRIG0                               0
#define AGPXIPC_VAL_PXI_TRIG1                               1
#define AGPXIPC_VAL_PXI_TRIG2                               2
#define AGPXIPC_VAL_PXI_TRIG3                               3
#define AGPXIPC_VAL_PXI_TRIG4                               4
#define AGPXIPC_VAL_PXI_TRIG5                               5
#define AGPXIPC_VAL_PXI_TRIG6                               6
#define AGPXIPC_VAL_PXI_TRIG7                               7
#define AGPXIPC_VAL_PXI_TRIG_NONE                           8

/*- Defined values for */

#define AGPXIPC_VAL_FLASH_WRITE_TYPE_MODE1                  1
#define AGPXIPC_VAL_FLASH_WRITE_TYPE_MODE2                  2


/**************************************************************************** 
 *---------------- Instrument Driver Function Declarations -----------------* 
 ****************************************************************************/

/*- AgPxiPc */

ViStatus _VI_FUNC AgPxiPc_init ( ViRsrc ResourceName, ViBoolean IdQuery, ViBoolean Reset, ViSession* Vi );
ViStatus _VI_FUNC AgPxiPc_close ( ViSession Vi );
ViStatus _VI_FUNC AgPxiPc_InitWithOptions ( ViRsrc ResourceName, ViBoolean IdQuery, ViBoolean Reset, ViConstString OptionsString, ViSession* Vi );

/*- Utility */

ViStatus _VI_FUNC AgPxiPc_revision_query ( ViSession Vi, ViChar DriverRev[], ViChar InstrRev[] );
ViStatus _VI_FUNC AgPxiPc_error_message ( ViSession Vi, ViStatus ErrorCode, ViChar ErrorMessage[] );
ViStatus _VI_FUNC AgPxiPc_GetError ( ViSession Vi, ViStatus* ErrorCode, ViInt32 ErrorDescriptionBufferSize, ViChar ErrorDescription[] );
ViStatus _VI_FUNC AgPxiPc_ClearError ( ViSession Vi );
ViStatus _VI_FUNC AgPxiPc_ClearInterchangeWarnings ( ViSession Vi );
ViStatus _VI_FUNC AgPxiPc_GetNextCoercionRecord ( ViSession Vi, ViInt32 CoercionRecordBufferSize, ViChar CoercionRecord[] );
ViStatus _VI_FUNC AgPxiPc_GetNextInterchangeWarning ( ViSession Vi, ViInt32 InterchangeWarningBufferSize, ViChar InterchangeWarning[] );
ViStatus _VI_FUNC AgPxiPc_InvalidateAllAttributes ( ViSession Vi );
ViStatus _VI_FUNC AgPxiPc_ResetInterchangeCheck ( ViSession Vi );
ViStatus _VI_FUNC AgPxiPc_Disable ( ViSession Vi );
ViStatus _VI_FUNC AgPxiPc_error_query ( ViSession Vi, ViInt32* ErrorCode, ViChar ErrorMessage[] );
ViStatus _VI_FUNC AgPxiPc_LockSession ( ViSession Vi, ViBoolean* CallerHasLock );
ViStatus _VI_FUNC AgPxiPc_reset ( ViSession Vi );
ViStatus _VI_FUNC AgPxiPc_ResetWithDefaults ( ViSession Vi );
ViStatus _VI_FUNC AgPxiPc_self_test ( ViSession Vi, ViInt16* TestResult, ViChar TestMessage[] );
ViStatus _VI_FUNC AgPxiPc_UnlockSession ( ViSession Vi, ViBoolean* CallerHasLock );

/*- Attribute Accessors */

ViStatus _VI_FUNC AgPxiPc_GetAttributeViInt32 ( ViSession Vi, ViConstString RepCapIdentifier, ViAttr AttributeID, ViInt32* AttributeValue );
ViStatus _VI_FUNC AgPxiPc_GetAttributeViReal64 ( ViSession Vi, ViConstString RepCapIdentifier, ViAttr AttributeID, ViReal64* AttributeValue );
ViStatus _VI_FUNC AgPxiPc_GetAttributeViBoolean ( ViSession Vi, ViConstString RepCapIdentifier, ViAttr AttributeID, ViBoolean* AttributeValue );
ViStatus _VI_FUNC AgPxiPc_GetAttributeViSession ( ViSession Vi, ViConstString RepCapIdentifier, ViAttr AttributeID, ViSession* AttributeValue );
ViStatus _VI_FUNC AgPxiPc_GetAttributeViString ( ViSession Vi, ViConstString RepCapIdentifier, ViAttr AttributeID, ViInt32 AttributeValueBufferSize, ViChar AttributeValue[] );
ViStatus _VI_FUNC AgPxiPc_SetAttributeViInt32 ( ViSession Vi, ViConstString RepCapIdentifier, ViAttr AttributeID, ViInt32 AttributeValue );
ViStatus _VI_FUNC AgPxiPc_SetAttributeViReal64 ( ViSession Vi, ViConstString RepCapIdentifier, ViAttr AttributeID, ViReal64 AttributeValue );
ViStatus _VI_FUNC AgPxiPc_SetAttributeViBoolean ( ViSession Vi, ViConstString RepCapIdentifier, ViAttr AttributeID, ViBoolean AttributeValue );
ViStatus _VI_FUNC AgPxiPc_SetAttributeViSession ( ViSession Vi, ViConstString RepCapIdentifier, ViAttr AttributeID, ViSession AttributeValue );
ViStatus _VI_FUNC AgPxiPc_SetAttributeViString ( ViSession Vi, ViConstString RepCapIdentifier, ViAttr AttributeID, ViConstString AttributeValue );

/*- TriggerRouting */

ViStatus _VI_FUNC AgPxiPc_TriggerRoutingSetRoute ( ViSession Vi, ViInt32 RouteConfiguration, ViInt32 PxiTrig );
ViStatus _VI_FUNC AgPxiPc_TriggerRoutingResetRoute ( ViSession Vi );
ViStatus _VI_FUNC AgPxiPc_TriggerRoutingGetEnabled ( ViSession Vi, ViBoolean* Enabled );
ViStatus _VI_FUNC AgPxiPc_TriggerRoutingGetRoute ( ViSession Vi, ViInt32* RouteConfiguration, ViInt32* PxiTrig );
ViStatus _VI_FUNC AgPxiPc_TriggerRoutingGetPxiTrig ( ViSession Vi, ViInt32* PxiTrig );
ViStatus _VI_FUNC AgPxiPc_TriggerRoutingGetRouteConfiguration ( ViSession Vi, ViInt32* RouteConfiguration );
ViStatus _VI_FUNC AgPxiPc_TriggerRoutingGetSoftwareRouteTriggerState ( ViSession Vi, ViBoolean* SoftwareRouteTriggerState );
ViStatus _VI_FUNC AgPxiPc_TriggerRoutingSetSoftwareRouteTriggerState ( ViSession Vi, ViBoolean SoftwareRouteTriggerState );

/*- System */

ViStatus _VI_FUNC AgPxiPc_ExecuteError ( ViSession Vi, ViInt32 ErrorNumber );
ViStatus _VI_FUNC AgPxiPc_DiagCommand ( ViSession Vi, ViInt32 OpCode, ViConstString Param );
ViStatus _VI_FUNC AgPxiPc_DiagQuery ( ViSession Vi, ViInt32 OpCode, ViConstString Param, ViInt32 ValBufferSize, ViChar Val[] );


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


#define AGPXIPC_ERROR_CANNOT_RECOVER                        (IVIC_ERROR_BASE + 0x0000)
#define AGPXIPC_ERROR_INSTRUMENT_STATUS                     (IVIC_ERROR_BASE + 0x0001)
#define AGPXIPC_ERROR_CANNOT_OPEN_FILE                      (IVIC_ERROR_BASE + 0x0002)
#define AGPXIPC_ERROR_READING_FILE                          (IVIC_ERROR_BASE + 0x0003)
#define AGPXIPC_ERROR_WRITING_FILE                          (IVIC_ERROR_BASE + 0x0004)
#define AGPXIPC_ERROR_INVALID_PATHNAME                      (IVIC_ERROR_BASE + 0x000B)
#define AGPXIPC_ERROR_INVALID_VALUE                         (IVIC_ERROR_BASE + 0x0010)
#define AGPXIPC_ERROR_FUNCTION_NOT_SUPPORTED                (IVIC_ERROR_BASE + 0x0011)
#define AGPXIPC_ERROR_ATTRIBUTE_NOT_SUPPORTED               (IVIC_ERROR_BASE + 0x0012)
#define AGPXIPC_ERROR_VALUE_NOT_SUPPORTED                   (IVIC_ERROR_BASE + 0x0013)
#define AGPXIPC_ERROR_NOT_INITIALIZED                       (IVIC_ERROR_BASE + 0x001D)
#define AGPXIPC_ERROR_UNKNOWN_CHANNEL_NAME                  (IVIC_ERROR_BASE + 0x0020)
#define AGPXIPC_ERROR_TOO_MANY_OPEN_FILES                   (IVIC_ERROR_BASE + 0x0023)
#define AGPXIPC_ERROR_CHANNEL_NAME_REQUIRED                 (IVIC_ERROR_BASE + 0x0044)
#define AGPXIPC_ERROR_MISSING_OPTION_NAME                   (IVIC_ERROR_BASE + 0x0049)
#define AGPXIPC_ERROR_MISSING_OPTION_VALUE                  (IVIC_ERROR_BASE + 0x004A)
#define AGPXIPC_ERROR_BAD_OPTION_NAME                       (IVIC_ERROR_BASE + 0x004B)
#define AGPXIPC_ERROR_BAD_OPTION_VALUE                      (IVIC_ERROR_BASE + 0x004C)
#define AGPXIPC_ERROR_OUT_OF_MEMORY                         (IVIC_ERROR_BASE + 0x0056)
#define AGPXIPC_ERROR_OPERATION_PENDING                     (IVIC_ERROR_BASE + 0x0057)
#define AGPXIPC_ERROR_NULL_POINTER                          (IVIC_ERROR_BASE + 0x0058)
#define AGPXIPC_ERROR_UNEXPECTED_RESPONSE                   (IVIC_ERROR_BASE + 0x0059)
#define AGPXIPC_ERROR_FILE_NOT_FOUND                        (IVIC_ERROR_BASE + 0x005B)
#define AGPXIPC_ERROR_INVALID_FILE_FORMAT                   (IVIC_ERROR_BASE + 0x005C)
#define AGPXIPC_ERROR_STATUS_NOT_AVAILABLE                  (IVIC_ERROR_BASE + 0x005D)
#define AGPXIPC_ERROR_ID_QUERY_FAILED                       (IVIC_ERROR_BASE + 0x005E)
#define AGPXIPC_ERROR_RESET_FAILED                          (IVIC_ERROR_BASE + 0x005F)
#define AGPXIPC_ERROR_RESOURCE_UNKNOWN                      (IVIC_ERROR_BASE + 0x0060)
#define AGPXIPC_ERROR_ALREADY_INITIALIZED                   (IVIC_ERROR_BASE + 0x0061)
#define AGPXIPC_ERROR_CANNOT_CHANGE_SIMULATION_STATE        (IVIC_ERROR_BASE + 0x0062)
#define AGPXIPC_ERROR_INVALID_NUMBER_OF_LEVELS_IN_SELECTOR  (IVIC_ERROR_BASE + 0x0063)
#define AGPXIPC_ERROR_INVALID_RANGE_IN_SELECTOR             (IVIC_ERROR_BASE + 0x0064)
#define AGPXIPC_ERROR_UNKOWN_NAME_IN_SELECTOR               (IVIC_ERROR_BASE + 0x0065)
#define AGPXIPC_ERROR_BADLY_FORMED_SELECTOR                 (IVIC_ERROR_BASE + 0x0066)
#define AGPXIPC_ERROR_UNKNOWN_PHYSICAL_IDENTIFIER           (IVIC_ERROR_BASE + 0x0067)
#define AGPXIPC_ERROR_INVALID_ATTRIBUTE                     (IVIC_ERROR_BASE + 0x000C)
#define AGPXIPC_ERROR_TYPES_DO_NOT_MATCH                    (IVIC_ERROR_BASE + 0x0015)
#define AGPXIPC_ERROR_IVI_ATTR_NOT_WRITABLE                 (IVIC_ERROR_BASE + 0x000D)
#define AGPXIPC_ERROR_IVI_ATTR_NOT_READABLE                 (IVIC_ERROR_BASE + 0x000E)
#define AGPXIPC_ERROR_INVALID_SESSION_HANDLE                (IVIC_ERROR_BASE + 0x1190)



#define AGPXIPC_SUCCESS                                     0
#define AGPXIPC_WARN_NSUP_ID_QUERY                          (IVIC_WARN_BASE + 0x0065)
#define AGPXIPC_WARN_NSUP_RESET                             (IVIC_WARN_BASE + 0x0066)
#define AGPXIPC_WARN_NSUP_SELF_TEST                         (IVIC_WARN_BASE + 0x0067)
#define AGPXIPC_WARN_NSUP_ERROR_QUERY                       (IVIC_WARN_BASE + 0x0068)
#define AGPXIPC_WARN_NSUP_REV_QUERY                         (IVIC_WARN_BASE + 0x0069)



#define AGPXIPC_ERROR_IO_GENERAL                            (IVIC_SPECIFIC_ERROR_BASE + 0x0214)
#define AGPXIPC_ERROR_IO_TIMEOUT                            (IVIC_SPECIFIC_ERROR_BASE + 0x0215)
#define AGPXIPC_ERROR_MODEL_NOT_SUPPORTED                   (IVIC_SPECIFIC_ERROR_BASE + 0x0216)
#define AGPXIPC_ERROR_PERSONALITY_NOT_ACTIVE                (IVIC_SPECIFIC_ERROR_BASE + 0x0211)
#define AGPXIPC_ERROR_PERSONALITY_NOT_LICENSED              (IVIC_SPECIFIC_ERROR_BASE + 0x0213)
#define AGPXIPC_ERROR_PERSONALITY_NOT_INSTALLED             (IVIC_SPECIFIC_ERROR_BASE + 0x0212)
#define AGPXIPC_ERROR_FUNDAMENTAL_API                       (IVIC_SPECIFIC_ERROR_BASE + 0x0001)




/**************************************************************************** 
 *---------------------------- End Include File ----------------------------* 
 ****************************************************************************/
#if defined(__cplusplus) || defined(__cplusplus__)
}
#endif
#endif // __AGPXIPC_HEADER
