/******************************************************************************
 *                                                                         
 * Copyright 2016, Keysight Technologies
 *
 *****************************************************************************/

#ifndef __KTMTRIG_HEADER
#define __KTMTRIG_HEADER

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

#define KTMTRIG_ATTR_SPECIFIC_DRIVER_DESCRIPTION              (IVI_INHERENT_ATTR_BASE + 514L)  /* ViString, read-only */
#define KTMTRIG_ATTR_SPECIFIC_DRIVER_PREFIX                   (IVI_INHERENT_ATTR_BASE + 302L)  /* ViString, read-only */
#define KTMTRIG_ATTR_SPECIFIC_DRIVER_VENDOR                   (IVI_INHERENT_ATTR_BASE + 513L)  /* ViString, read-only */
#define KTMTRIG_ATTR_SPECIFIC_DRIVER_REVISION                 (IVI_INHERENT_ATTR_BASE + 551L)  /* ViString, read-only */
#define KTMTRIG_ATTR_SPECIFIC_DRIVER_CLASS_SPEC_MAJOR_VERSION (IVI_INHERENT_ATTR_BASE + 515L)  /* ViInt32, read-only */
#define KTMTRIG_ATTR_SPECIFIC_DRIVER_CLASS_SPEC_MINOR_VERSION (IVI_INHERENT_ATTR_BASE + 516L)  /* ViInt32, read-only */

/*- User Options */

#define KTMTRIG_ATTR_RANGE_CHECK                            (IVI_INHERENT_ATTR_BASE + 2L)  /* ViBoolean, read-write */
#define KTMTRIG_ATTR_QUERY_INSTRUMENT_STATUS                (IVI_INHERENT_ATTR_BASE + 3L)  /* ViBoolean, read-write */
#define KTMTRIG_ATTR_CACHE                                  (IVI_INHERENT_ATTR_BASE + 4L)  /* ViBoolean, read-write */
#define KTMTRIG_ATTR_SIMULATE                               (IVI_INHERENT_ATTR_BASE + 5L)  /* ViBoolean, read-write */
#define KTMTRIG_ATTR_RECORD_COERCIONS                       (IVI_INHERENT_ATTR_BASE + 6L)  /* ViBoolean, read-write */
#define KTMTRIG_ATTR_INTERCHANGE_CHECK                      (IVI_INHERENT_ATTR_BASE + 21L)  /* ViBoolean, read-write */

/*- Advanced Session Information */

#define KTMTRIG_ATTR_LOGICAL_NAME                           (IVI_INHERENT_ATTR_BASE + 305L)  /* ViString, read-only */
#define KTMTRIG_ATTR_IO_RESOURCE_DESCRIPTOR                 (IVI_INHERENT_ATTR_BASE + 304L)  /* ViString, read-only */
#define KTMTRIG_ATTR_DRIVER_SETUP                           (IVI_INHERENT_ATTR_BASE + 7L)  /* ViString, read-only */

/*- Driver Capabilities */

#define KTMTRIG_ATTR_GROUP_CAPABILITIES                     (IVI_INHERENT_ATTR_BASE + 401L)  /* ViString, read-only */
#define KTMTRIG_ATTR_SUPPORTED_INSTRUMENT_MODELS            (IVI_INHERENT_ATTR_BASE + 327L)  /* ViString, read-only */

/*- Instrument Identification */

#define KTMTRIG_ATTR_INSTRUMENT_FIRMWARE_REVISION           (IVI_INHERENT_ATTR_BASE + 510L)  /* ViString, read-only */
#define KTMTRIG_ATTR_INSTRUMENT_MANUFACTURER                (IVI_INHERENT_ATTR_BASE + 511L)  /* ViString, read-only */
#define KTMTRIG_ATTR_INSTRUMENT_MODEL                       (IVI_INHERENT_ATTR_BASE + 512L)  /* ViString, read-only */


/*===== Instrument-Specific Attributes =====================================*/

/*- System */

#define KTMTRIG_ATTR_SYSTEM_SERIAL_NUMBER                   (IVI_SPECIFIC_ATTR_BASE + 3L)  /* ViString, read-only */
#define KTMTRIG_ATTR_SYSTEM_CLIENT_LABEL                    (IVI_SPECIFIC_ATTR_BASE + 4L)  /* ViString, read-only */
#define KTMTRIG_ATTR_SYSTEM_SEGMENT_COUNT                   (IVI_SPECIFIC_ATTR_BASE + 5L)  /* ViInt32, read-only */


/**************************************************************************** 
 *------------------------ Attribute Value Defines -------------------------* 
 ****************************************************************************/

/*- Defined values for */

#define KTMTRIG_VAL_STATUS_BYTE_FLAGS_USER0                 1
#define KTMTRIG_VAL_STATUS_BYTE_FLAGS_USER1                 2
#define KTMTRIG_VAL_STATUS_BYTE_FLAGS_USER2                 4
#define KTMTRIG_VAL_STATUS_BYTE_FLAGS_USER3                 8
#define KTMTRIG_VAL_STATUS_BYTE_FLAGS_MESSAGE_AVAILABLE     16
#define KTMTRIG_VAL_STATUS_BYTE_FLAGS_EVENT_STATUS_REGISTER 32
#define KTMTRIG_VAL_STATUS_BYTE_FLAGS_REQUESTING_SERVICE    64
#define KTMTRIG_VAL_STATUS_BYTE_FLAGS_USER7                 128


/**************************************************************************** 
 *---------------- Instrument Driver Function Declarations -----------------* 
 ****************************************************************************/

/*- KtMTrig */

ViStatus _VI_FUNC KtMTrig_init(ViRsrc ResourceName, ViBoolean IdQuery, ViBoolean Reset, ViSession* Vi);
ViStatus _VI_FUNC KtMTrig_close(ViSession Vi);
ViStatus _VI_FUNC KtMTrig_InitWithOptions(ViRsrc ResourceName, ViBoolean IdQuery, ViBoolean Reset, ViConstString OptionsString, ViSession* Vi);

/*- Instrument Specific */

ViStatus _VI_FUNC KtMTrig_SetTriggerPathBetweenSlots(ViSession Vi, ViInt32 SourceSlot, ViInt32 DestinationSlotsBufferSize, ViInt32 DestinationSlots[], ViInt32 PreferredTriggerLine, ViInt32* Val);
ViStatus _VI_FUNC KtMTrig_SetReservation(ViSession Vi, ViInt32 BusSegment, ViInt32 TriggerLine);
ViStatus _VI_FUNC KtMTrig_ClearReservation(ViSession Vi, ViInt32 BusSegment, ViInt32 TriggerLine);
ViStatus _VI_FUNC KtMTrig_ClearTriggerPathBetweenSlots(ViSession Vi, ViInt32 SourceSlot, ViInt32 DestinationSlotsBufferSize, ViInt32 DestinationSlots[], ViInt32 TriggerLine);

/*- System */

ViStatus _VI_FUNC KtMTrig_SystemQueryHighSlotOfBusSegment(ViSession Vi, ViInt32 BusSegment, ViInt32* Val);
ViStatus _VI_FUNC KtMTrig_SystemQueryLowSlotOfBusSegment(ViSession Vi, ViInt32 BusSegment, ViInt32* Val);
ViStatus _VI_FUNC KtMTrig_SystemQueryReservationOwner(ViSession Vi, ViInt32 BusSegment, ViInt32 TriggerLine, ViInt32 ValBufferSize, ViChar Val[]);
ViStatus _VI_FUNC KtMTrig_SystemRedefineClientLabel(ViSession Vi, ViConstString ClientLabel);

/*- Administration */

ViStatus _VI_FUNC KtMTrig_SystemAdministrationClearAllRoutesAndReservationsAllClients(ViSession Vi);
ViStatus _VI_FUNC KtMTrig_SystemAdministrationClearAllRoutesAndReservationsSingleClient(ViSession Vi, ViConstString ClientLabel);

/*- PXI9 */

ViStatus _VI_FUNC KtMTrig_PXI9ClearAllRoutesAndReservations(ViSession Vi);
ViStatus _VI_FUNC KtMTrig_PXI9ClearRoute(ViSession Vi, ViInt32 DestinationBusSegment, ViInt32 DestinationTriggerLine);
ViStatus _VI_FUNC KtMTrig_PXI9GetLineInformation(ViSession Vi, ViInt32 BusSegment, ViInt32 TriggerLine, ViInt32* ReservationStatus, ViInt32* SourceBusSegmentOfRoute, ViInt32* SourceTriggerLineOfRoute, ViInt32 OwnerClientLabelBufferSize, ViChar OwnerClientLabel[]);
ViStatus _VI_FUNC KtMTrig_PXI9SetReservation(ViSession Vi, ViInt32 BusSegment, ViInt32 TriggerLine, ViInt32 Reserve);
ViStatus _VI_FUNC KtMTrig_PXI9SetReservationMultiple(ViSession Vi, ViInt32 BusSegmentsBufferSize, ViInt32 BusSegments[], ViInt32 TriggerLinesBufferSize, ViInt32 TriggerLines[], ViInt32* IndexOfFailure);
ViStatus _VI_FUNC KtMTrig_PXI9SetRoute(ViSession Vi, ViInt32 SourceBusSegment, ViInt32 SourceTriggerLine, ViInt32 DestinationBusSegment, ViInt32 DestinationTriggerLine);

/*- Utility */

ViStatus _VI_FUNC KtMTrig_revision_query(ViSession Vi, ViChar DriverRev[], ViChar InstrRev[]);
ViStatus _VI_FUNC KtMTrig_error_message(ViSession Vi, ViStatus ErrorCode, ViChar ErrorMessage[]);
ViStatus _VI_FUNC KtMTrig_GetError(ViSession Vi, ViStatus* ErrorCode, ViInt32 ErrorDescriptionBufferSize, ViChar ErrorDescription[]);
ViStatus _VI_FUNC KtMTrig_ClearError(ViSession Vi);
ViStatus _VI_FUNC KtMTrig_GetNextCoercionRecord(ViSession Vi, ViInt32 CoercionRecordBufferSize, ViChar CoercionRecord[]);
ViStatus _VI_FUNC KtMTrig_InvalidateAllAttributes(ViSession Vi);
ViStatus _VI_FUNC KtMTrig_Disable(ViSession Vi);
ViStatus _VI_FUNC KtMTrig_error_query(ViSession Vi, ViInt32* ErrorCode, ViChar ErrorMessage[]);
ViStatus _VI_FUNC KtMTrig_LockSession(ViSession Vi, ViBoolean* CallerHasLock);
ViStatus _VI_FUNC KtMTrig_reset(ViSession Vi);
ViStatus _VI_FUNC KtMTrig_ResetWithDefaults(ViSession Vi);
ViStatus _VI_FUNC KtMTrig_self_test(ViSession Vi, ViInt16* TestResult, ViChar TestMessage[]);
ViStatus _VI_FUNC KtMTrig_UnlockSession(ViSession Vi, ViBoolean* CallerHasLock);

/*- Attribute Accessors */

ViStatus _VI_FUNC KtMTrig_GetAttributeViInt32(ViSession Vi, ViConstString RepCapIdentifier, ViAttr AttributeID, ViInt32* AttributeValue);
ViStatus _VI_FUNC KtMTrig_GetAttributeViReal64(ViSession Vi, ViConstString RepCapIdentifier, ViAttr AttributeID, ViReal64* AttributeValue);
ViStatus _VI_FUNC KtMTrig_GetAttributeViBoolean(ViSession Vi, ViConstString RepCapIdentifier, ViAttr AttributeID, ViBoolean* AttributeValue);
ViStatus _VI_FUNC KtMTrig_GetAttributeViSession(ViSession Vi, ViConstString RepCapIdentifier, ViAttr AttributeID, ViSession* AttributeValue);
ViStatus _VI_FUNC KtMTrig_GetAttributeViString(ViSession Vi, ViConstString RepCapIdentifier, ViAttr AttributeID, ViInt32 AttributeValueBufferSize, ViChar AttributeValue[]);
ViStatus _VI_FUNC KtMTrig_SetAttributeViInt32(ViSession Vi, ViConstString RepCapIdentifier, ViAttr AttributeID, ViInt32 AttributeValue);
ViStatus _VI_FUNC KtMTrig_SetAttributeViReal64(ViSession Vi, ViConstString RepCapIdentifier, ViAttr AttributeID, ViReal64 AttributeValue);
ViStatus _VI_FUNC KtMTrig_SetAttributeViBoolean(ViSession Vi, ViConstString RepCapIdentifier, ViAttr AttributeID, ViBoolean AttributeValue);
ViStatus _VI_FUNC KtMTrig_SetAttributeViSession(ViSession Vi, ViConstString RepCapIdentifier, ViAttr AttributeID, ViSession AttributeValue);
ViStatus _VI_FUNC KtMTrig_SetAttributeViString(ViSession Vi, ViConstString RepCapIdentifier, ViAttr AttributeID, ViConstString AttributeValue);


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


#define KTMTRIG_ERROR_CANNOT_RECOVER                        (IVIC_ERROR_BASE + 0x0000)
#define KTMTRIG_ERROR_INSTRUMENT_STATUS                     (IVIC_ERROR_BASE + 0x0001)
#define KTMTRIG_ERROR_CANNOT_OPEN_FILE                      (IVIC_ERROR_BASE + 0x0002)
#define KTMTRIG_ERROR_READING_FILE                          (IVIC_ERROR_BASE + 0x0003)
#define KTMTRIG_ERROR_WRITING_FILE                          (IVIC_ERROR_BASE + 0x0004)
#define KTMTRIG_ERROR_INVALID_PATHNAME                      (IVIC_ERROR_BASE + 0x000B)
#define KTMTRIG_ERROR_INVALID_ATTRIBUTE                     (IVIC_ERROR_BASE + 0x000C)
#define KTMTRIG_ERROR_IVI_ATTR_NOT_WRITABLE                 (IVIC_ERROR_BASE + 0x000D)
#define KTMTRIG_ERROR_IVI_ATTR_NOT_READABLE                 (IVIC_ERROR_BASE + 0x000E)
#define KTMTRIG_ERROR_INVALID_VALUE                         (IVIC_ERROR_BASE + 0x0010)
#define KTMTRIG_ERROR_FUNCTION_NOT_SUPPORTED                (IVIC_ERROR_BASE + 0x0011)
#define KTMTRIG_ERROR_ATTRIBUTE_NOT_SUPPORTED               (IVIC_ERROR_BASE + 0x0012)
#define KTMTRIG_ERROR_VALUE_NOT_SUPPORTED                   (IVIC_ERROR_BASE + 0x0013)
#define KTMTRIG_ERROR_TYPES_DO_NOT_MATCH                    (IVIC_ERROR_BASE + 0x0015)
#define KTMTRIG_ERROR_NOT_INITIALIZED                       (IVIC_ERROR_BASE + 0x001D)
#define KTMTRIG_ERROR_UNKNOWN_CHANNEL_NAME                  (IVIC_ERROR_BASE + 0x0020)
#define KTMTRIG_ERROR_TOO_MANY_OPEN_FILES                   (IVIC_ERROR_BASE + 0x0023)
#define KTMTRIG_ERROR_CHANNEL_NAME_REQUIRED                 (IVIC_ERROR_BASE + 0x0044)
#define KTMTRIG_ERROR_MISSING_OPTION_NAME                   (IVIC_ERROR_BASE + 0x0049)
#define KTMTRIG_ERROR_MISSING_OPTION_VALUE                  (IVIC_ERROR_BASE + 0x004A)
#define KTMTRIG_ERROR_BAD_OPTION_NAME                       (IVIC_ERROR_BASE + 0x004B)
#define KTMTRIG_ERROR_BAD_OPTION_VALUE                      (IVIC_ERROR_BASE + 0x004C)
#define KTMTRIG_ERROR_OUT_OF_MEMORY                         (IVIC_ERROR_BASE + 0x0056)
#define KTMTRIG_ERROR_OPERATION_PENDING                     (IVIC_ERROR_BASE + 0x0057)
#define KTMTRIG_ERROR_NULL_POINTER                          (IVIC_ERROR_BASE + 0x0058)
#define KTMTRIG_ERROR_UNEXPECTED_RESPONSE                   (IVIC_ERROR_BASE + 0x0059)
#define KTMTRIG_ERROR_FILE_NOT_FOUND                        (IVIC_ERROR_BASE + 0x005B)
#define KTMTRIG_ERROR_INVALID_FILE_FORMAT                   (IVIC_ERROR_BASE + 0x005C)
#define KTMTRIG_ERROR_STATUS_NOT_AVAILABLE                  (IVIC_ERROR_BASE + 0x005D)
#define KTMTRIG_ERROR_ID_QUERY_FAILED                       (IVIC_ERROR_BASE + 0x005E)
#define KTMTRIG_ERROR_RESET_FAILED                          (IVIC_ERROR_BASE + 0x005F)
#define KTMTRIG_ERROR_RESOURCE_UNKNOWN                      (IVIC_ERROR_BASE + 0x0060)
#define KTMTRIG_ERROR_ALREADY_INITIALIZED                   (IVIC_ERROR_BASE + 0x0061)
#define KTMTRIG_ERROR_CANNOT_CHANGE_SIMULATION_STATE        (IVIC_ERROR_BASE + 0x0062)
#define KTMTRIG_ERROR_INVALID_NUMBER_OF_LEVELS_IN_SELECTOR  (IVIC_ERROR_BASE + 0x0063)
#define KTMTRIG_ERROR_INVALID_RANGE_IN_SELECTOR             (IVIC_ERROR_BASE + 0x0064)
#define KTMTRIG_ERROR_UNKOWN_NAME_IN_SELECTOR               (IVIC_ERROR_BASE + 0x0065)
#define KTMTRIG_ERROR_BADLY_FORMED_SELECTOR                 (IVIC_ERROR_BASE + 0x0066)
#define KTMTRIG_ERROR_UNKNOWN_PHYSICAL_IDENTIFIER           (IVIC_ERROR_BASE + 0x0067)
#define KTMTRIG_ERROR_INVALID_SESSION_HANDLE                (IVIC_ERROR_BASE + 0x1190)



#define KTMTRIG_SUCCESS                                     0
#define KTMTRIG_WARN_NSUP_ID_QUERY                          (IVIC_WARN_BASE + 0x0065)
#define KTMTRIG_WARN_NSUP_RESET                             (IVIC_WARN_BASE + 0x0066)
#define KTMTRIG_WARN_NSUP_SELF_TEST                         (IVIC_WARN_BASE + 0x0067)
#define KTMTRIG_WARN_NSUP_ERROR_QUERY                       (IVIC_WARN_BASE + 0x0068)
#define KTMTRIG_WARN_NSUP_REV_QUERY                         (IVIC_WARN_BASE + 0x0069)



#define KTMTRIG_ERROR_IO_GENERAL                            (IVIC_SPECIFIC_ERROR_BASE + 0x0214)
#define KTMTRIG_ERROR_IO_TIMEOUT                            (IVIC_SPECIFIC_ERROR_BASE + 0x0215)
#define KTMTRIG_ERROR_CHASSIS_API                           (IVIC_SPECIFIC_ERROR_BASE + 0x0216)
#define KTMTRIG_ERROR_VISA_API                              (IVIC_SPECIFIC_ERROR_BASE + 0x0217)




/**************************************************************************** 
 *---------------------------- End Include File ----------------------------* 
 ****************************************************************************/
#if defined(__cplusplus) || defined(__cplusplus__)
}
#endif
#endif // __KTMTRIG_HEADER
