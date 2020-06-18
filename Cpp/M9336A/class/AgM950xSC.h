/******************************************************************************
 *                                                                         
 * © Keysight Technologies 2011-2017
 *
 *****************************************************************************/

#ifndef __AGM950XSC_HEADER
#define __AGM950XSC_HEADER

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

#define AGM950XSC_ATTR_SPECIFIC_DRIVER_DESCRIPTION              (IVI_INHERENT_ATTR_BASE + 514L)  /* ViString, read-only */
#define AGM950XSC_ATTR_SPECIFIC_DRIVER_PREFIX                   (IVI_INHERENT_ATTR_BASE + 302L)  /* ViString, read-only */
#define AGM950XSC_ATTR_SPECIFIC_DRIVER_VENDOR                   (IVI_INHERENT_ATTR_BASE + 513L)  /* ViString, read-only */
#define AGM950XSC_ATTR_SPECIFIC_DRIVER_REVISION                 (IVI_INHERENT_ATTR_BASE + 551L)  /* ViString, read-only */
#define AGM950XSC_ATTR_SPECIFIC_DRIVER_CLASS_SPEC_MAJOR_VERSION (IVI_INHERENT_ATTR_BASE + 515L)  /* ViInt32, read-only */
#define AGM950XSC_ATTR_SPECIFIC_DRIVER_CLASS_SPEC_MINOR_VERSION (IVI_INHERENT_ATTR_BASE + 516L)  /* ViInt32, read-only */

/*- User Options */

#define AGM950XSC_ATTR_RANGE_CHECK                          (IVI_INHERENT_ATTR_BASE + 2L)  /* ViBoolean, read-write */
#define AGM950XSC_ATTR_QUERY_INSTRUMENT_STATUS              (IVI_INHERENT_ATTR_BASE + 3L)  /* ViBoolean, read-write */
#define AGM950XSC_ATTR_CACHE                                (IVI_INHERENT_ATTR_BASE + 4L)  /* ViBoolean, read-write */
#define AGM950XSC_ATTR_SIMULATE                             (IVI_INHERENT_ATTR_BASE + 5L)  /* ViBoolean, read-write */
#define AGM950XSC_ATTR_RECORD_COERCIONS                     (IVI_INHERENT_ATTR_BASE + 6L)  /* ViBoolean, read-write */
#define AGM950XSC_ATTR_INTERCHANGE_CHECK                    (IVI_INHERENT_ATTR_BASE + 21L)  /* ViBoolean, read-write */

/*- Advanced Session Information */

#define AGM950XSC_ATTR_LOGICAL_NAME                         (IVI_INHERENT_ATTR_BASE + 305L)  /* ViString, read-only */
#define AGM950XSC_ATTR_IO_RESOURCE_DESCRIPTOR               (IVI_INHERENT_ATTR_BASE + 304L)  /* ViString, read-only */
#define AGM950XSC_ATTR_DRIVER_SETUP                         (IVI_INHERENT_ATTR_BASE + 7L)  /* ViString, read-only */

/*- Driver Capabilities */

#define AGM950XSC_ATTR_GROUP_CAPABILITIES                   (IVI_INHERENT_ATTR_BASE + 401L)  /* ViString, read-only */
#define AGM950XSC_ATTR_SUPPORTED_INSTRUMENT_MODELS          (IVI_INHERENT_ATTR_BASE + 327L)  /* ViString, read-only */

/*- Instrument Identification */

#define AGM950XSC_ATTR_INSTRUMENT_FIRMWARE_REVISION         (IVI_INHERENT_ATTR_BASE + 510L)  /* ViString, read-only */
#define AGM950XSC_ATTR_INSTRUMENT_MANUFACTURER              (IVI_INHERENT_ATTR_BASE + 511L)  /* ViString, read-only */
#define AGM950XSC_ATTR_INSTRUMENT_MODEL                     (IVI_INHERENT_ATTR_BASE + 512L)  /* ViString, read-only */


/*===== Instrument-Specific Attributes =====================================*/

/*- System */

#define AGM950XSC_ATTR_SERIAL_NUMBER                        (IVI_SPECIFIC_ATTR_BASE + 1L)  /* ViString, read-only */
#define AGM950XSC_ATTR_TRACE_ENABLED                        (IVI_SPECIFIC_ATTR_BASE + 2L)  /* ViBoolean, read-write */

/*- ExternalSignals */

#define AGM950XSC_ATTR_EXTERNALSIGNALS_TRIGGER_IN_INVERT    (IVI_SPECIFIC_ATTR_BASE + 11L)  /* ViBoolean, read-write */
#define AGM950XSC_ATTR_EXTERNALSIGNALS_TRIGGER_IN_THRESHOLD (IVI_SPECIFIC_ATTR_BASE + 12L)  /* ViReal64, read-write */
#define AGM950XSC_ATTR_EXTERNALSIGNALS_TRIGGER_OUT_ENABLED  (IVI_SPECIFIC_ATTR_BASE + 13L)  /* ViBoolean, read-write */
#define AGM950XSC_ATTR_EXTERNALSIGNALS_TRIGGER_OUT_INVERT   (IVI_SPECIFIC_ATTR_BASE + 14L)  /* ViBoolean, read-write */
#define AGM950XSC_ATTR_EXTERNALSIGNALS_TRIGGER_OUT_PULSED   (IVI_SPECIFIC_ATTR_BASE + 15L)  /* ViBoolean, read-write */
#define AGM950XSC_ATTR_EXTERNALSIGNALS_CLOCK_OUTPUT_ENABLE  (IVI_SPECIFIC_ATTR_BASE + 16L)  /* ViBoolean, read-write */

/*- Timing */

#define AGM950XSC_ATTR_TIMING_RUN                           (IVI_SPECIFIC_ATTR_BASE + 17L)  /* ViBoolean, read-write */

/*- TriggerRouting */

#define AGM950XSC_ATTR_TRIGGERROUTING_SYNC_THROUGH_CROSSPOINT_SWITCH (IVI_SPECIFIC_ATTR_BASE + 5L)  /* ViBoolean, read-write */


/**************************************************************************** 
 *------------------------ Attribute Value Defines -------------------------* 
 ****************************************************************************/

/*- Defined values for 
	parameter CounterIdentification in function AgM950xSC_TimingGetCorrelationCounter
	parameter CounterIdentification in function AgM950xSC_TimingGetCorrelationSeconds */

#define AGM950XSC_VAL_CORRELATORS0                          0
#define AGM950XSC_VAL_CORRELATORS1                          1
#define AGM950XSC_VAL_CORRELATORS2                          2
#define AGM950XSC_VAL_CORRELATORS3                          3
#define AGM950XSC_VAL_CORRELATORS4                          4
#define AGM950XSC_VAL_CORRELATORS5                          5
#define AGM950XSC_VAL_CORRELATORS6                          6
#define AGM950XSC_VAL_CORRELATORS7                          7

/*- Defined values for 
	parameter OutputLine in function AgM950xSC_TriggerRoutingGetCrosspointSwitchOutputSource
	parameter OutputLine in function AgM950xSC_TriggerRoutingSetCrosspointSwitchOutputSource */

#define AGM950XSC_VAL_OUT_SYNC                              0
#define AGM950XSC_VAL_OUT_SMA_TRIGGER                       1
#define AGM950XSC_VAL_OUT_TRIGGER0                          2
#define AGM950XSC_VAL_OUT_TRIGGER1                          3
#define AGM950XSC_VAL_OUT_TRIGGER2                          4
#define AGM950XSC_VAL_OUT_TRIGGER3                          5
#define AGM950XSC_VAL_OUT_TRIGGER4                          6
#define AGM950XSC_VAL_OUT_TRIGGER5                          7
#define AGM950XSC_VAL_OUT_TRIGGER6                          8
#define AGM950XSC_VAL_OUT_TRIGGER7                          9
#define AGM950XSC_VAL_OUT_TRIGGER8                          10
#define AGM950XSC_VAL_OUT_TRIGGER9                          11
#define AGM950XSC_VAL_OUT_TRIGGER10                         12
#define AGM950XSC_VAL_OUT_TRIGGER11                         13
#define AGM950XSC_VAL_OUT_MULTIFRAME_FLAG1                  14
#define AGM950XSC_VAL_OUT_MULTIFRAME_FLAG2                  15
#define AGM950XSC_VAL_OUT_MULTIFRAME_FLAG3                  16
#define AGM950XSC_VAL_OUT_MULTIFRAME_FLAG4                  17
#define AGM950XSC_VAL_OUT_CORRELATOR_TRIGGER0               18
#define AGM950XSC_VAL_OUT_CORRELATOR_TRIGGER1               19
#define AGM950XSC_VAL_OUT_CORRELATOR_TRIGGER2               20
#define AGM950XSC_VAL_OUT_CORRELATOR_TRIGGER3               21
#define AGM950XSC_VAL_OUT_CORRELATOR_TRIGGER4               22
#define AGM950XSC_VAL_OUT_CORRELATOR_TRIGGER5               23
#define AGM950XSC_VAL_OUT_STAR_TRIGGER_SLOT1                24
#define AGM950XSC_VAL_OUT_STAR_TRIGGER_SLOT2                25
#define AGM950XSC_VAL_OUT_STAR_TRIGGER_SLOT3                26
#define AGM950XSC_VAL_OUT_STAR_TRIGGER_SLOT4                27
#define AGM950XSC_VAL_OUT_STAR_TRIGGER_SLOT5                28

/*- Defined values for 
	parameter InputLine in function AgM950xSC_TriggerRoutingGetCrosspointSwitchOutputSource
	parameter InputLine in function AgM950xSC_TriggerRoutingSetCrosspointSwitchOutputSource */

#define AGM950XSC_VAL_IN_STATIC_ZERO                        0
#define AGM950XSC_VAL_IN_TRIGGER0                           1
#define AGM950XSC_VAL_IN_TRIGGER1                           2
#define AGM950XSC_VAL_IN_TRIGGER2                           3
#define AGM950XSC_VAL_IN_TRIGGER3                           4
#define AGM950XSC_VAL_IN_TRIGGER4                           5
#define AGM950XSC_VAL_IN_TRIGGER5                           6
#define AGM950XSC_VAL_IN_TRIGGER6                           7
#define AGM950XSC_VAL_IN_TRIGGER7                           8
#define AGM950XSC_VAL_IN_TRIGGER8                           9
#define AGM950XSC_VAL_IN_TRIGGER9                           10
#define AGM950XSC_VAL_IN_TRIGGER10                          11
#define AGM950XSC_VAL_IN_TRIGGER11                          12
#define AGM950XSC_VAL_IN_STAR_TRIGGER_SLOT1                 13
#define AGM950XSC_VAL_IN_STAR_TRIGGER_SLOT2                 14
#define AGM950XSC_VAL_IN_STAR_TRIGGER_SLOT3                 15
#define AGM950XSC_VAL_IN_STAR_TRIGGER_SLOT4                 16
#define AGM950XSC_VAL_IN_STAR_TRIGGER_SLOT5                 17
#define AGM950XSC_VAL_IN_SMA_TRIGGER                        26
#define AGM950XSC_VAL_IN_MULTIFRAME_FLAG1                   27
#define AGM950XSC_VAL_IN_MULTIFRAME_FLAG2                   28
#define AGM950XSC_VAL_IN_MULTIFRAME_FLAG3                   29
#define AGM950XSC_VAL_IN_MULTIFRAME_FLAG4                   30
#define AGM950XSC_VAL_IN_RUN_FLAG                           31
#define AGM950XSC_VAL_IN_STATIC_ONE                         32
#define AGM950XSC_VAL_IN_UNKNOWN                            255

/*- Defined values for 
	parameter StarTriggerOutputEnableRegister in function AgM950xSC_TriggerRoutingGetStarTriggerOutputEnableRegister
	parameter Bitmask in function AgM950xSC_TriggerRoutingSetStarTriggerOutputEnableRegister */

#define AGM950XSC_VAL_STAR_TRIGGER_OUTPUT_ENABLE_SLOT1      1
#define AGM950XSC_VAL_STAR_TRIGGER_OUTPUT_ENABLE_SLOT2      2
#define AGM950XSC_VAL_STAR_TRIGGER_OUTPUT_ENABLE_SLOT3      4
#define AGM950XSC_VAL_STAR_TRIGGER_OUTPUT_ENABLE_SLOT4      8
#define AGM950XSC_VAL_STAR_TRIGGER_OUTPUT_ENABLE_SLOT5      16

/*- Defined values for 
	parameter TriggerBus in function AgM950xSC_TriggerRoutingGetTriggerBus */

#define AGM950XSC_VAL_TRIGGER_BUS_BITMAP_TRIGGER0           1
#define AGM950XSC_VAL_TRIGGER_BUS_BITMAP_TRIGGER1           2
#define AGM950XSC_VAL_TRIGGER_BUS_BITMAP_TRIGGER2           4
#define AGM950XSC_VAL_TRIGGER_BUS_BITMAP_TRIGGER3           8
#define AGM950XSC_VAL_TRIGGER_BUS_BITMAP_TRIGGER4           16
#define AGM950XSC_VAL_TRIGGER_BUS_BITMAP_TRIGGER5           32
#define AGM950XSC_VAL_TRIGGER_BUS_BITMAP_TRIGGER6           64
#define AGM950XSC_VAL_TRIGGER_BUS_BITMAP_TRIGGER7           128
#define AGM950XSC_VAL_TRIGGER_BUS_BITMAP_TRIGGER8           256
#define AGM950XSC_VAL_TRIGGER_BUS_BITMAP_TRIGGER9           512
#define AGM950XSC_VAL_TRIGGER_BUS_BITMAP_TRIGGER10          1024
#define AGM950XSC_VAL_TRIGGER_BUS_BITMAP_TRIGGER11          2048
#define AGM950XSC_VAL_TRIGGER_BUS_BITMAP_STAR_TRIGGER_SLOT1 4096
#define AGM950XSC_VAL_TRIGGER_BUS_BITMAP_STAR_TRIGGER_SLOT2 8192
#define AGM950XSC_VAL_TRIGGER_BUS_BITMAP_STAR_TRIGGER_SLOT3 16384
#define AGM950XSC_VAL_TRIGGER_BUS_BITMAP_STAR_TRIGGER_SLOT4 32768
#define AGM950XSC_VAL_TRIGGER_BUS_BITMAP_STAR_TRIGGER_SLOT5 65536
#define AGM950XSC_VAL_TRIGGER_BUS_BITMAP_SMA_INPUT_TRIGGER  33554432
#define AGM950XSC_VAL_TRIGGER_BUS_BITMAP_MULTIFRAME_FLAG1   67108864
#define AGM950XSC_VAL_TRIGGER_BUS_BITMAP_MULTIFRAME_FLAG2   134217728
#define AGM950XSC_VAL_TRIGGER_BUS_BITMAP_MULTIFRAME_FLAG3   268435456
#define AGM950XSC_VAL_TRIGGER_BUS_BITMAP_MULTIFRAME_FLAG4   536870912
#define AGM950XSC_VAL_TRIGGER_BUS_BITMAP_RUN_FLAG           1073741824

/*- Defined values for 
	parameter TriggerOutputEnableRegister in function AgM950xSC_TriggerRoutingGetTriggerOutputEnableRegister
	parameter Bitmask in function AgM950xSC_TriggerRoutingSetTriggerOutputEnableRegister */

#define AGM950XSC_VAL_TRIGGER_OUTPUT_ENABLE0                1
#define AGM950XSC_VAL_TRIGGER_OUTPUT_ENABLE1                2
#define AGM950XSC_VAL_TRIGGER_OUTPUT_ENABLE2                4
#define AGM950XSC_VAL_TRIGGER_OUTPUT_ENABLE3                8
#define AGM950XSC_VAL_TRIGGER_OUTPUT_ENABLE4                16
#define AGM950XSC_VAL_TRIGGER_OUTPUT_ENABLE5                32
#define AGM950XSC_VAL_TRIGGER_OUTPUT_ENABLE6                64
#define AGM950XSC_VAL_TRIGGER_OUTPUT_ENABLE7                128
#define AGM950XSC_VAL_TRIGGER_OUTPUT_ENABLE8                256
#define AGM950XSC_VAL_TRIGGER_OUTPUT_ENABLE9                512
#define AGM950XSC_VAL_TRIGGER_OUTPUT_ENABLE10               1024
#define AGM950XSC_VAL_TRIGGER_OUTPUT_ENABLE11               2048


/**************************************************************************** 
 *---------------- Instrument Driver Function Declarations -----------------* 
 ****************************************************************************/

/*- AgM950xSC */

ViStatus _VI_FUNC AgM950xSC_init ( ViRsrc ResourceName, ViBoolean IdQuery, ViBoolean Reset, ViSession* Vi );
ViStatus _VI_FUNC AgM950xSC_close ( ViSession Vi );
ViStatus _VI_FUNC AgM950xSC_InitWithOptions ( ViRsrc ResourceName, ViBoolean IdQuery, ViBoolean Reset, ViConstString OptionsString, ViSession* Vi );

/*- Utility */

ViStatus _VI_FUNC AgM950xSC_revision_query ( ViSession Vi, ViChar DriverRev[], ViChar InstrRev[] );
ViStatus _VI_FUNC AgM950xSC_error_message ( ViSession Vi, ViStatus ErrorCode, ViChar ErrorMessage[] );
ViStatus _VI_FUNC AgM950xSC_GetError ( ViSession Vi, ViStatus* ErrorCode, ViInt32 ErrorDescriptionBufferSize, ViChar ErrorDescription[] );
ViStatus _VI_FUNC AgM950xSC_ClearError ( ViSession Vi );
ViStatus _VI_FUNC AgM950xSC_ClearInterchangeWarnings ( ViSession Vi );
ViStatus _VI_FUNC AgM950xSC_GetNextCoercionRecord ( ViSession Vi, ViInt32 CoercionRecordBufferSize, ViChar CoercionRecord[] );
ViStatus _VI_FUNC AgM950xSC_GetNextInterchangeWarning ( ViSession Vi, ViInt32 InterchangeWarningBufferSize, ViChar InterchangeWarning[] );
ViStatus _VI_FUNC AgM950xSC_InvalidateAllAttributes ( ViSession Vi );
ViStatus _VI_FUNC AgM950xSC_ResetInterchangeCheck ( ViSession Vi );
ViStatus _VI_FUNC AgM950xSC_Disable ( ViSession Vi );
ViStatus _VI_FUNC AgM950xSC_error_query ( ViSession Vi, ViInt32* ErrorCode, ViChar ErrorMessage[] );
ViStatus _VI_FUNC AgM950xSC_LockSession ( ViSession Vi, ViBoolean* CallerHasLock );
ViStatus _VI_FUNC AgM950xSC_reset ( ViSession Vi );
ViStatus _VI_FUNC AgM950xSC_ResetWithDefaults ( ViSession Vi );
ViStatus _VI_FUNC AgM950xSC_self_test ( ViSession Vi, ViInt16* TestResult, ViChar TestMessage[] );
ViStatus _VI_FUNC AgM950xSC_UnlockSession ( ViSession Vi, ViBoolean* CallerHasLock );

/*- Attribute Accessors */

ViStatus _VI_FUNC AgM950xSC_GetAttributeViInt32 ( ViSession Vi, ViConstString RepCapIdentifier, ViAttr AttributeID, ViInt32* AttributeValue );
ViStatus _VI_FUNC AgM950xSC_GetAttributeViReal64 ( ViSession Vi, ViConstString RepCapIdentifier, ViAttr AttributeID, ViReal64* AttributeValue );
ViStatus _VI_FUNC AgM950xSC_GetAttributeViBoolean ( ViSession Vi, ViConstString RepCapIdentifier, ViAttr AttributeID, ViBoolean* AttributeValue );
ViStatus _VI_FUNC AgM950xSC_GetAttributeViSession ( ViSession Vi, ViConstString RepCapIdentifier, ViAttr AttributeID, ViSession* AttributeValue );
ViStatus _VI_FUNC AgM950xSC_GetAttributeViString ( ViSession Vi, ViConstString RepCapIdentifier, ViAttr AttributeID, ViInt32 AttributeValueBufferSize, ViChar AttributeValue[] );
ViStatus _VI_FUNC AgM950xSC_SetAttributeViInt32 ( ViSession Vi, ViConstString RepCapIdentifier, ViAttr AttributeID, ViInt32 AttributeValue );
ViStatus _VI_FUNC AgM950xSC_SetAttributeViReal64 ( ViSession Vi, ViConstString RepCapIdentifier, ViAttr AttributeID, ViReal64 AttributeValue );
ViStatus _VI_FUNC AgM950xSC_SetAttributeViBoolean ( ViSession Vi, ViConstString RepCapIdentifier, ViAttr AttributeID, ViBoolean AttributeValue );
ViStatus _VI_FUNC AgM950xSC_SetAttributeViSession ( ViSession Vi, ViConstString RepCapIdentifier, ViAttr AttributeID, ViSession AttributeValue );
ViStatus _VI_FUNC AgM950xSC_SetAttributeViString ( ViSession Vi, ViConstString RepCapIdentifier, ViAttr AttributeID, ViConstString AttributeValue );

/*- Instrument Specific */

ViStatus _VI_FUNC AgM950xSC_ResetTriggerBus ( ViSession Vi );

/*- System */

ViStatus _VI_FUNC AgM950xSC_SaveState ( ViSession Vi, ViInt32 StateBlobBufferSize, ViChar StateBlob[] );
ViStatus _VI_FUNC AgM950xSC_RecallState ( ViSession Vi, ViConstString StateBlob );
ViStatus _VI_FUNC AgM950xSC_SaveAsDefaultState ( ViSession Vi );
ViStatus _VI_FUNC AgM950xSC_RecallDefaultState ( ViSession Vi );
ViStatus _VI_FUNC AgM950xSC_GetSerialNumber ( ViSession Vi, ViInt32 SerialNumberBufferSize, ViChar SerialNumber[] );

/*- ExternalSignals */

ViStatus _VI_FUNC AgM950xSC_ExternalSignalsGetClockOutputEnable ( ViSession Vi, ViBoolean* ClockOutputEnable );
ViStatus _VI_FUNC AgM950xSC_ExternalSignalsSetClockOutputEnable ( ViSession Vi, ViBoolean ClockOutputEnable );
ViStatus _VI_FUNC AgM950xSC_ExternalSignalsGetTriggerInInvert ( ViSession Vi, ViBoolean* TriggerInInvert );
ViStatus _VI_FUNC AgM950xSC_ExternalSignalsSetTriggerInInvert ( ViSession Vi, ViBoolean TriggerInInvert );
ViStatus _VI_FUNC AgM950xSC_ExternalSignalsGetTriggerInThreshold ( ViSession Vi, ViReal64* TriggerInThreshold );
ViStatus _VI_FUNC AgM950xSC_ExternalSignalsSetTriggerInThreshold ( ViSession Vi, ViReal64 TriggerInThreshold );
ViStatus _VI_FUNC AgM950xSC_ExternalSignalsGetTriggerOutEnabled ( ViSession Vi, ViBoolean* TriggerOutEnabled );
ViStatus _VI_FUNC AgM950xSC_ExternalSignalsSetTriggerOutEnabled ( ViSession Vi, ViBoolean TriggerOutEnabled );
ViStatus _VI_FUNC AgM950xSC_ExternalSignalsGetTriggerOutInvert ( ViSession Vi, ViBoolean* TriggerOutInvert );
ViStatus _VI_FUNC AgM950xSC_ExternalSignalsSetTriggerOutInvert ( ViSession Vi, ViBoolean TriggerOutInvert );
ViStatus _VI_FUNC AgM950xSC_ExternalSignalsGetTriggerOutPulsed ( ViSession Vi, ViBoolean* TriggerOutPulsed );
ViStatus _VI_FUNC AgM950xSC_ExternalSignalsSetTriggerOutPulsed ( ViSession Vi, ViBoolean TriggerOutPulsed );

/*- Timing */

ViStatus _VI_FUNC AgM950xSC_TimingClearCorrelationCounters ( ViSession Vi );
ViStatus _VI_FUNC AgM950xSC_TimingGetCorrelationCounter ( ViSession Vi, ViInt32 CounterIdentification, ViInt64* CorrelationCounter );
ViStatus _VI_FUNC AgM950xSC_TimingGetCorrelationSeconds ( ViSession Vi, ViInt32 CounterIdentification, ViReal64* CorrelationSeconds );
ViStatus _VI_FUNC AgM950xSC_TimingGetRun ( ViSession Vi, ViBoolean* Run );
ViStatus _VI_FUNC AgM950xSC_TimingSetRun ( ViSession Vi, ViBoolean Run );

/*- TriggerRouting */

ViStatus _VI_FUNC AgM950xSC_TriggerRoutingGetStarTriggerOutputEnableRegister ( ViSession Vi, ViInt32* StarTriggerOutputEnableRegister );
ViStatus _VI_FUNC AgM950xSC_TriggerRoutingGetCrosspointSwitchOutputSource ( ViSession Vi, ViInt32 OutputLine, ViInt32* InputLine );
ViStatus _VI_FUNC AgM950xSC_TriggerRoutingGetTriggerBus ( ViSession Vi, ViInt32* TriggerBus );
ViStatus _VI_FUNC AgM950xSC_TriggerRoutingGetTriggerOutputEnableRegister ( ViSession Vi, ViInt32* TriggerOutputEnableRegister );
ViStatus _VI_FUNC AgM950xSC_TriggerRoutingSetCrosspointSwitchOutputSource ( ViSession Vi, ViInt32 OutputLine, ViInt32 InputLine );
ViStatus _VI_FUNC AgM950xSC_TriggerRoutingSetStarTriggerOutputEnableRegister ( ViSession Vi, ViInt32 Bitmask );
ViStatus _VI_FUNC AgM950xSC_TriggerRoutingGetSyncThroughCrosspointSwitch ( ViSession Vi, ViBoolean* SyncThroughCrosspointSwitch );
ViStatus _VI_FUNC AgM950xSC_TriggerRoutingSetSyncThroughCrosspointSwitch ( ViSession Vi, ViBoolean SyncThroughCrosspointSwitch );
ViStatus _VI_FUNC AgM950xSC_TriggerRoutingSetTriggerOutputEnableRegister ( ViSession Vi, ViInt32 Bitmask );


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


#define AGM950XSC_ERROR_CANNOT_RECOVER                       (IVIC_ERROR_BASE + 0x0000)
#define AGM950XSC_ERROR_INSTRUMENT_STATUS                    (IVIC_ERROR_BASE + 0x0001)
#define AGM950XSC_ERROR_CANNOT_OPEN_FILE                     (IVIC_ERROR_BASE + 0x0002)
#define AGM950XSC_ERROR_READING_FILE                         (IVIC_ERROR_BASE + 0x0003)
#define AGM950XSC_ERROR_WRITING_FILE                         (IVIC_ERROR_BASE + 0x0004)
#define AGM950XSC_ERROR_INVALID_PATHNAME                     (IVIC_ERROR_BASE + 0x000B)
#define AGM950XSC_ERROR_INVALID_VALUE                        (IVIC_ERROR_BASE + 0x0010)
#define AGM950XSC_ERROR_FUNCTION_NOT_SUPPORTED               (IVIC_ERROR_BASE + 0x0011)
#define AGM950XSC_ERROR_ATTRIBUTE_NOT_SUPPORTED              (IVIC_ERROR_BASE + 0x0012)
#define AGM950XSC_ERROR_VALUE_NOT_SUPPORTED                  (IVIC_ERROR_BASE + 0x0013)
#define AGM950XSC_ERROR_NOT_INITIALIZED                      (IVIC_ERROR_BASE + 0x001D)
#define AGM950XSC_ERROR_UNKNOWN_CHANNEL_NAME                 (IVIC_ERROR_BASE + 0x0020)
#define AGM950XSC_ERROR_TOO_MANY_OPEN_FILES                  (IVIC_ERROR_BASE + 0x0023)
#define AGM950XSC_ERROR_CHANNEL_NAME_REQUIRED                (IVIC_ERROR_BASE + 0x0044)
#define AGM950XSC_ERROR_MISSING_OPTION_NAME                  (IVIC_ERROR_BASE + 0x0049)
#define AGM950XSC_ERROR_MISSING_OPTION_VALUE                 (IVIC_ERROR_BASE + 0x004A)
#define AGM950XSC_ERROR_BAD_OPTION_NAME                      (IVIC_ERROR_BASE + 0x004B)
#define AGM950XSC_ERROR_BAD_OPTION_VALUE                     (IVIC_ERROR_BASE + 0x004C)
#define AGM950XSC_ERROR_OUT_OF_MEMORY                        (IVIC_ERROR_BASE + 0x0056)
#define AGM950XSC_ERROR_OPERATION_PENDING                    (IVIC_ERROR_BASE + 0x0057)
#define AGM950XSC_ERROR_NULL_POINTER                         (IVIC_ERROR_BASE + 0x0058)
#define AGM950XSC_ERROR_UNEXPECTED_RESPONSE                  (IVIC_ERROR_BASE + 0x0059)
#define AGM950XSC_ERROR_FILE_NOT_FOUND                       (IVIC_ERROR_BASE + 0x005B)
#define AGM950XSC_ERROR_INVALID_FILE_FORMAT                  (IVIC_ERROR_BASE + 0x005C)
#define AGM950XSC_ERROR_STATUS_NOT_AVAILABLE                 (IVIC_ERROR_BASE + 0x005D)
#define AGM950XSC_ERROR_ID_QUERY_FAILED                      (IVIC_ERROR_BASE + 0x005E)
#define AGM950XSC_ERROR_RESET_FAILED                         (IVIC_ERROR_BASE + 0x005F)
#define AGM950XSC_ERROR_RESOURCE_UNKNOWN                     (IVIC_ERROR_BASE + 0x0060)
#define AGM950XSC_ERROR_ALREADY_INITIALIZED                  (IVIC_ERROR_BASE + 0x0061)
#define AGM950XSC_ERROR_CANNOT_CHANGE_SIMULATION_STATE       (IVIC_ERROR_BASE + 0x0062)
#define AGM950XSC_ERROR_INVALID_NUMBER_OF_LEVELS_IN_SELECTOR (IVIC_ERROR_BASE + 0x0063)
#define AGM950XSC_ERROR_INVALID_RANGE_IN_SELECTOR            (IVIC_ERROR_BASE + 0x0064)
#define AGM950XSC_ERROR_UNKOWN_NAME_IN_SELECTOR              (IVIC_ERROR_BASE + 0x0065)
#define AGM950XSC_ERROR_BADLY_FORMED_SELECTOR                (IVIC_ERROR_BASE + 0x0066)
#define AGM950XSC_ERROR_UNKNOWN_PHYSICAL_IDENTIFIER          (IVIC_ERROR_BASE + 0x0067)
#define AGM950XSC_ERROR_INVALID_ATTRIBUTE                    (IVIC_ERROR_BASE + 0x000C)
#define AGM950XSC_ERROR_TYPES_DO_NOT_MATCH                   (IVIC_ERROR_BASE + 0x0015)
#define AGM950XSC_ERROR_IVI_ATTR_NOT_WRITABLE                (IVIC_ERROR_BASE + 0x000D)
#define AGM950XSC_ERROR_IVI_ATTR_NOT_READABLE                (IVIC_ERROR_BASE + 0x000E)
#define AGM950XSC_ERROR_INVALID_SESSION_HANDLE               (IVIC_ERROR_BASE + 0x1190)



#define AGM950XSC_SUCCESS                                   0
#define AGM950XSC_WARN_NSUP_ID_QUERY                        (IVIC_WARN_BASE + 0x0065)
#define AGM950XSC_WARN_NSUP_RESET                           (IVIC_WARN_BASE + 0x0066)
#define AGM950XSC_WARN_NSUP_SELF_TEST                       (IVIC_WARN_BASE + 0x0067)
#define AGM950XSC_WARN_NSUP_ERROR_QUERY                     (IVIC_WARN_BASE + 0x0068)
#define AGM950XSC_WARN_NSUP_REV_QUERY                       (IVIC_WARN_BASE + 0x0069)



#define AGM950XSC_ERROR_IO_GENERAL                          (IVIC_SPECIFIC_ERROR_BASE + 0x0214)
#define AGM950XSC_ERROR_IO_TIMEOUT                          (IVIC_SPECIFIC_ERROR_BASE + 0x0215)
#define AGM950XSC_ERROR_MODEL_NOT_SUPPORTED                 (IVIC_SPECIFIC_ERROR_BASE + 0x0216)
#define AGM950XSC_ERROR_PERSONALITY_NOT_ACTIVE              (IVIC_SPECIFIC_ERROR_BASE + 0x0211)
#define AGM950XSC_ERROR_PERSONALITY_NOT_LICENSED            (IVIC_SPECIFIC_ERROR_BASE + 0x0213)
#define AGM950XSC_ERROR_PERSONALITY_NOT_INSTALLED           (IVIC_SPECIFIC_ERROR_BASE + 0x0212)
#define AGM950XSC_ERROR_CHASSIS_API                         (IVIC_SPECIFIC_ERROR_BASE + 0x0002)
#define AGM950XSC_ERROR_INTERNAL_SW                         (IVIC_SPECIFIC_ERROR_BASE + 0x0004)
#define AGM950XSC_ERROR_UNEXPECTED                          (IVIC_SPECIFIC_ERROR_BASE + 0x0003)
#define AGM950XSC_ERROR_VISA_API                            (IVIC_SPECIFIC_ERROR_BASE + 0x0001)




/**************************************************************************** 
 *---------------------------- End Include File ----------------------------* 
 ****************************************************************************/
#if defined(__cplusplus) || defined(__cplusplus__)
}
#endif
#endif // __AGM950XSC_HEADER
