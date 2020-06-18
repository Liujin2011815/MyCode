/******************************************************************************
 *                                                                         
 * Copyright Keysight Technologies 2015
 *
 *****************************************************************************/

#ifndef __KTMAWG_HEADER
#define __KTMAWG_HEADER

#include "ivivisatype.h"

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

#define KTMAWG_ATTR_SPECIFIC_DRIVER_DESCRIPTION              (IVI_INHERENT_ATTR_BASE + 514L)  /* ViString, read-only */
#define KTMAWG_ATTR_SPECIFIC_DRIVER_PREFIX                   (IVI_INHERENT_ATTR_BASE + 302L)  /* ViString, read-only */
#define KTMAWG_ATTR_SPECIFIC_DRIVER_VENDOR                   (IVI_INHERENT_ATTR_BASE + 513L)  /* ViString, read-only */
#define KTMAWG_ATTR_SPECIFIC_DRIVER_REVISION                 (IVI_INHERENT_ATTR_BASE + 551L)  /* ViString, read-only */
#define KTMAWG_ATTR_SPECIFIC_DRIVER_CLASS_SPEC_MAJOR_VERSION (IVI_INHERENT_ATTR_BASE + 515L)  /* ViInt32, read-only */
#define KTMAWG_ATTR_SPECIFIC_DRIVER_CLASS_SPEC_MINOR_VERSION (IVI_INHERENT_ATTR_BASE + 516L)  /* ViInt32, read-only */

/*- User Options */

#define KTMAWG_ATTR_RANGE_CHECK                             (IVI_INHERENT_ATTR_BASE + 2L)  /* ViBoolean, read-write */
#define KTMAWG_ATTR_QUERY_INSTRUMENT_STATUS                 (IVI_INHERENT_ATTR_BASE + 3L)  /* ViBoolean, read-write */
#define KTMAWG_ATTR_CACHE                                   (IVI_INHERENT_ATTR_BASE + 4L)  /* ViBoolean, read-write */
#define KTMAWG_ATTR_SIMULATE                                (IVI_INHERENT_ATTR_BASE + 5L)  /* ViBoolean, read-write */
#define KTMAWG_ATTR_RECORD_COERCIONS                        (IVI_INHERENT_ATTR_BASE + 6L)  /* ViBoolean, read-write */
#define KTMAWG_ATTR_INTERCHANGE_CHECK                       (IVI_INHERENT_ATTR_BASE + 21L)  /* ViBoolean, read-write */

/*- Advanced Session Information */

#define KTMAWG_ATTR_LOGICAL_NAME                            (IVI_INHERENT_ATTR_BASE + 305L)  /* ViString, read-only */
#define KTMAWG_ATTR_IO_RESOURCE_DESCRIPTOR                  (IVI_INHERENT_ATTR_BASE + 304L)  /* ViString, read-only */
#define KTMAWG_ATTR_DRIVER_SETUP                            (IVI_INHERENT_ATTR_BASE + 7L)  /* ViString, read-only */

/*- Driver Capabilities */

#define KTMAWG_ATTR_GROUP_CAPABILITIES                      (IVI_INHERENT_ATTR_BASE + 401L)  /* ViString, read-only */
#define KTMAWG_ATTR_SUPPORTED_INSTRUMENT_MODELS             (IVI_INHERENT_ATTR_BASE + 327L)  /* ViString, read-only */

/*- Instrument Identification */

#define KTMAWG_ATTR_INSTRUMENT_FIRMWARE_REVISION            (IVI_INHERENT_ATTR_BASE + 510L)  /* ViString, read-only */
#define KTMAWG_ATTR_INSTRUMENT_MANUFACTURER                 (IVI_INHERENT_ATTR_BASE + 511L)  /* ViString, read-only */
#define KTMAWG_ATTR_INSTRUMENT_MODEL                        (IVI_INHERENT_ATTR_BASE + 512L)  /* ViString, read-only */


/*===== Instrument-Specific Attributes =====================================*/

/*- Instrument Specific */

#define KTMAWG_ATTR_GENERATION_SETTINGS_RESTRICTIONS        (IVI_SPECIFIC_ATTR_BASE + 101L)  /* ViBoolean, read-only */

/*- System */

#define KTMAWG_ATTR_SERIAL_NUMBER                           (IVI_SPECIFIC_ATTR_BASE + 3L)  /* ViString, read-only */
#define KTMAWG_ATTR_SYSTEM_ABOUT                            (IVI_SPECIFIC_ATTR_BASE + 4L)  /* ViString, read-only */
#define KTMAWG_ATTR_SYSTEM_GC_TIMING_OPTIMIZATION_ENABLED   (IVI_SPECIFIC_ATTR_BASE + 5L)  /* ViBoolean, read-write */
#define KTMAWG_ATTR_SYSTEM_IDENTIFY_ENABLED                 (IVI_SPECIFIC_ATTR_BASE + 6L)  /* ViBoolean, read-write */
#define KTMAWG_ATTR_SYSTEM_INSTANCE_ID                      (IVI_SPECIFIC_ATTR_BASE + 7L)  /* ViInt32, read-only */
#define KTMAWG_ATTR_SYSTEM_OPTIONS                          (IVI_SPECIFIC_ATTR_BASE + 8L)  /* ViString, read-only */
#define KTMAWG_ATTR_SYSTEM_TIMEOUT                          (IVI_SPECIFIC_ATTR_BASE + 9L)  /* ViInt32, read-write */

/*- Licensing */

#define KTMAWG_ATTR_LICENSING_HOST_IDENTIFIER               (IVI_SPECIFIC_ATTR_BASE + 11L)  /* ViString, read-only */
#define KTMAWG_ATTR_LICENSING_INSTALLED_LICENSES            (IVI_SPECIFIC_ATTR_BASE + 12L)  /* ViString, read-only */

/*- Calibration */

#define KTMAWG_ATTR_CALIBRATION_ADJUSTMENT_INFORMATION      (IVI_SPECIFIC_ATTR_BASE + 16L)  /* ViString, read-only */
#define KTMAWG_ATTR_CALIBRATION_DUE_DATE                    (IVI_SPECIFIC_ATTR_BASE + 17L)  /* ViString, read-only */
#define KTMAWG_ATTR_CALIBRATION_INSTRUMENT_IDENTIFIER       (IVI_SPECIFIC_ATTR_BASE + 18L)  /* ViString, read-only */
#define KTMAWG_ATTR_CALIBRATION_STATUS                      (IVI_SPECIFIC_ATTR_BASE + 19L)  /* ViInt32, read-only */
#define KTMAWG_ATTR_CALIBRATION_VERIFICATION_INFORMATION    (IVI_SPECIFIC_ATTR_BASE + 20L)  /* ViString, read-only */

/*- Module */

#define KTMAWG_ATTR_MODULE_COUNT                            (IVI_SPECIFIC_ATTR_BASE + 23L)  /* ViInt32, read-only */
#define KTMAWG_ATTR_MODULE_INSTRUMENT_CAPABILITY            (IVI_SPECIFIC_ATTR_BASE + 24L)  /* ViString, read-only */
#define KTMAWG_ATTR_MODULE_MAXIMUM_RECORDED_TEMPERATURE     (IVI_SPECIFIC_ATTR_BASE + 25L)  /* ViInt32, read-only */
#define KTMAWG_ATTR_MODULE_OPTIONS                          (IVI_SPECIFIC_ATTR_BASE + 26L)  /* ViString, read-only */
#define KTMAWG_ATTR_MODULE_SERIAL_NUMBER                    (IVI_SPECIFIC_ATTR_BASE + 27L)  /* ViString, read-only */
#define KTMAWG_ATTR_MODULE_SLOT                             (IVI_SPECIFIC_ATTR_BASE + 28L)  /* ViInt32, read-only */
#define KTMAWG_ATTR_MODULE_TEMPERATURE                      (IVI_SPECIFIC_ATTR_BASE + 29L)  /* ViReal64, read-only */

/*- Calibration */

#define KTMAWG_ATTR_MODULE_CALIBRATION_ADJUSTMENT_INFORMATION   (IVI_SPECIFIC_ATTR_BASE + 30L)  /* ViString, read-only */
#define KTMAWG_ATTR_MODULE_CALIBRATION_DUE_DATE                 (IVI_SPECIFIC_ATTR_BASE + 31L)  /* ViString, read-only */
#define KTMAWG_ATTR_MODULE_CALIBRATION_STATUS                   (IVI_SPECIFIC_ATTR_BASE + 32L)  /* ViInt32, read-only */
#define KTMAWG_ATTR_MODULE_CALIBRATION_VERIFICATION_INFORMATION (IVI_SPECIFIC_ATTR_BASE + 33L)  /* ViString, read-only */

/*- Nonvolatile */

#define KTMAWG_ATTR_NONVOLATILE_ASSET_NUMBER                   (IVI_SPECIFIC_ATTR_BASE + 34L)  /* ViString, read-write */
#define KTMAWG_ATTR_NONVOLATILE_CAL_DUE_REMINDER               (IVI_SPECIFIC_ATTR_BASE + 35L)  /* ViInt32, read-write */
#define KTMAWG_ATTR_NONVOLATILE_ENABLE_INSTRUMENT_CAL_WARNINGS (IVI_SPECIFIC_ATTR_BASE + 36L)  /* ViBoolean, read-write */
#define KTMAWG_ATTR_NONVOLATILE_ENABLE_MODULE_CAL_WARNINGS     (IVI_SPECIFIC_ATTR_BASE + 37L)  /* ViBoolean, read-write */
#define KTMAWG_ATTR_NONVOLATILE_ENABLE_PERIODIC_CAL            (IVI_SPECIFIC_ATTR_BASE + 38L)  /* ViBoolean, read-write */
#define KTMAWG_ATTR_NONVOLATILE_INSTRUMENT_CAL_INTERVAL        (IVI_SPECIFIC_ATTR_BASE + 39L)  /* ViInt32, read-write */
#define KTMAWG_ATTR_NONVOLATILE_MODULE_CAL_INTERVAL            (IVI_SPECIFIC_ATTR_BASE + 40L)  /* ViInt32, read-write */
#define KTMAWG_ATTR_NONVOLATILE_PASSPHRASE                     (IVI_SPECIFIC_ATTR_BASE + 41L)  /* ViString, read-write */
#define KTMAWG_ATTR_NONVOLATILE_SYSTEM_IDENTIFICATION          (IVI_SPECIFIC_ATTR_BASE + 42L)  /* ViString, read-write */

/*- AssetChannel */

#define KTMAWG_ATTR_ASSETCHANNEL_COUNT                      (IVI_SPECIFIC_ATTR_BASE + 60L)  /* ViInt32, read-only */

/*- PeerToPeerPort */

#define KTMAWG_ATTR_PEERTOPEERPORT_COUNT                    (IVI_SPECIFIC_ATTR_BASE + 45L)  /* ViInt32, read-only */
#define KTMAWG_ATTR_ACTIVE_PEERTOPEERPORT                   (IVI_SPECIFIC_ATTR_BASE + 46L)  /* ViString, read-write */

/*- DeviceSync */

#define KTMAWG_ATTR_DEVICE_SYNC_CLOCK_RATE                  (IVI_SPECIFIC_ATTR_BASE + 88L)  /* ViInt32, read-write */
#define KTMAWG_ATTR_DEVICE_SYNC_CLOCK_SOURCE                (IVI_SPECIFIC_ATTR_BASE + 89L)  /* ViString, read-write */
#define KTMAWG_ATTR_DEVICE_SYNC_GROUP_MASK                  (IVI_SPECIFIC_ATTR_BASE + 90L)  /* ViInt32, read-write */
#define KTMAWG_ATTR_DEVICE_SYNC_GROUP_SIGNAL                (IVI_SPECIFIC_ATTR_BASE + 91L)  /* ViInt32, read-write */
#define KTMAWG_ATTR_DEVICE_SYNC_ROLE                        (IVI_SPECIFIC_ATTR_BASE + 92L)  /* ViInt32, read-write */
#define KTMAWG_ATTR_DEVICE_SYNC_SLAVE_SIGNAL                (IVI_SPECIFIC_ATTR_BASE + 93L)  /* ViInt32, read-write */
#define KTMAWG_ATTR_DEVICE_SYNC_STATE                       (IVI_SPECIFIC_ATTR_BASE + 94L)  /* ViInt32, read-only */
#define KTMAWG_ATTR_DEVICE_SYNC_IS_ALIGNMENT_VALID          (IVI_SPECIFIC_ATTR_BASE + 97L)  /* ViBoolean, read-only */
#define KTMAWG_ATTR_DEVICE_SYNC_SYNC_CHANNELS               (IVI_SPECIFIC_ATTR_BASE + 100L)  /* ViString, read-write */

/*- Waveform */

#define KTMAWG_ATTR_ARB_NUMBER_WAVEFORMS                    (IVI_SPECIFIC_ATTR_BASE + 98L)  /* ViInt32, read-only */

/*- Sequence */

#define KTMAWG_ATTR_ARB_NUMBER_SEQUENCES                    (IVI_SPECIFIC_ATTR_BASE + 99L)  /* ViInt32, read-only */

/*- SequenceTriggers */

#define KTMAWG_ATTR_SEQUENCETRIGGER_MAX_COUNT               (IVI_SPECIFIC_ATTR_BASE + 73L)  /* ViInt32, read-only */
#define KTMAWG_ATTR_SEQUENCETRIGGER_COUNT                   (IVI_SPECIFIC_ATTR_BASE + 74L)  /* ViInt32, read-only */

/*- Marker */

#define KTMAWG_ATTR_MARKER_COUNT                            (IVI_SPECIFIC_ATTR_BASE + 75L)  /* ViInt32, read-only */
#define KTMAWG_ATTR_MARKER_MAX_COUNT                        (IVI_SPECIFIC_ATTR_BASE + 76L)  /* ViInt32, read-only */

/*- External */

#define KTMAWG_ATTR_EXTERNAL_COUNT                          (IVI_SPECIFIC_ATTR_BASE + 79L)  /* ViInt32, read-only */
#define KTMAWG_ATTR_EXTERNAL_INPUT_SLOPE                    (IVI_SPECIFIC_ATTR_BASE + 83L)  /* ViInt32, read-write */
#define KTMAWG_ATTR_EXTERNAL_OUTPUT_POLARITY                (IVI_SPECIFIC_ATTR_BASE + 84L)  /* ViInt32, read-write */
#define KTMAWG_ATTR_EXTERNAL_THRESHOLD                      (IVI_SPECIFIC_ATTR_BASE + 85L)  /* ViReal64, read-write */

/*- TriggerBusLine */

#define KTMAWG_ATTR_TRIGGER_BUS_LINE_COUNT                  (IVI_SPECIFIC_ATTR_BASE + 80L)  /* ViInt32, read-only */
#define KTMAWG_ATTR_TRIGGER_BUS_LINE_INPUT_SLOPE            (IVI_SPECIFIC_ATTR_BASE + 81L)  /* ViInt32, read-write */
#define KTMAWG_ATTR_TRIGGER_BUS_LINE_OUTPUT_POLARITY        (IVI_SPECIFIC_ATTR_BASE + 82L)  /* ViInt32, read-write */
#define KTMAWG_ATTR_TRIGGER_BUS_LINE_CAPABILITY             (IVI_SPECIFIC_ATTR_BASE + 86L)  /* ViInt32, read-only */

/*- ReferenceClock */

#define KTMAWG_ATTR_REF_CLOCK_IS_PHASE_LOCKED               (IVI_SPECIFIC_ATTR_BASE + 96L)  /* ViBoolean, read-only */

/*- Arbitrary */

#define KTMAWG_ATTR_ARB_GAIN                                (IVI_CLASS_ATTR_BASE + 202L)  /* ViReal64, read-write */
#define KTMAWG_ATTR_ARB_OFFSET                              (IVI_CLASS_ATTR_BASE + 203L)  /* ViReal64, read-write */
#define KTMAWG_ATTR_ARB_SAMPLE_RATE                         (IVI_CLASS_ATTR_BASE + 204L)  /* ViReal64, read-write */

/*- Waveform */

#define KTMAWG_ATTR_ARB_WAVEFORM_HANDLE                     (IVI_CLASS_ATTR_BASE + 201L)  /* ViInt32, read-write */
#define KTMAWG_ATTR_MAX_NUM_WAVEFORMS                       (IVI_CLASS_ATTR_BASE + 205L)  /* ViInt32, read-only */
#define KTMAWG_ATTR_WAVEFORM_QUANTUM                        (IVI_CLASS_ATTR_BASE + 206L)  /* ViInt32, read-only */
#define KTMAWG_ATTR_MAX_WAVEFORM_SIZE                       (IVI_CLASS_ATTR_BASE + 208L)  /* ViInt32, read-only */
#define KTMAWG_ATTR_MAX_WAVEFORM_SIZE64                     (IVI_CLASS_ATTR_BASE + 222L)  /* ViInt64, read-only */
#define KTMAWG_ATTR_MIN_WAVEFORM_SIZE                       (IVI_CLASS_ATTR_BASE + 207L)  /* ViInt32, read-only */
#define KTMAWG_ATTR_MIN_WAVEFORM_SIZE64                     (IVI_CLASS_ATTR_BASE + 221L)  /* ViInt64, read-only */
#define KTMAWG_ATTR_BINARY_ALIGNMENT                        (IVI_CLASS_ATTR_BASE + 241L)  /* ViInt32, read-only */
#define KTMAWG_ATTR_SAMPLE_BIT_RESOLUTION                   (IVI_CLASS_ATTR_BASE + 242L)  /* ViInt32, read-only */
#define KTMAWG_ATTR_OUTPUT_DATA_MASK                        (IVI_CLASS_ATTR_BASE + 261L)  /* ViInt32, read-only */

/*- Sequence */

#define KTMAWG_ATTR_ARB_SEQUENCE_HANDLE                     (IVI_CLASS_ATTR_BASE + 211L)  /* ViInt32, read-write */
#define KTMAWG_ATTR_MAX_SEQUENCE_LENGTH                     (IVI_CLASS_ATTR_BASE + 214L)  /* ViInt32, read-only */
#define KTMAWG_ATTR_MIN_SEQUENCE_LENGTH                     (IVI_CLASS_ATTR_BASE + 213L)  /* ViInt32, read-only */
#define KTMAWG_ATTR_MAX_LOOP_COUNT                          (IVI_CLASS_ATTR_BASE + 215L)  /* ViInt32, read-only */
#define KTMAWG_ATTR_MAX_NUM_SEQUENCES                       (IVI_CLASS_ATTR_BASE + 212L)  /* ViInt32, read-only */
#define KTMAWG_ATTR_MAX_SEQUENCE_DEPTH                      (IVI_CLASS_ATTR_BASE + 281L)  /* ViInt32, read-only */

/*- Output */

#define KTMAWG_ATTR_CHANNEL_COUNT                           (IVI_INHERENT_ATTR_BASE + 203L)  /* ViInt32, read-only */
#define KTMAWG_ATTR_OUTPUT_ENABLED                          (IVI_CLASS_ATTR_BASE + 3L)  /* ViBoolean, read-write */
#define KTMAWG_ATTR_OUTPUT_IMPEDANCE                        (IVI_CLASS_ATTR_BASE + 4L)  /* ViReal64, read-write */
#define KTMAWG_ATTR_OPERATION_MODE                          (IVI_CLASS_ATTR_BASE + 5L)  /* ViInt32, read-write */
#define KTMAWG_ATTR_OUTPUT_MODE                             (IVI_CLASS_ATTR_BASE + 1L)  /* ViInt32, read-write */
#define KTMAWG_ATTR_REF_CLOCK_SOURCE                        (IVI_CLASS_ATTR_BASE + 2L)  /* ViInt32, read-write */
#define KTMAWG_ATTR_TERMINAL_CONFIGURATION                  (IVI_CLASS_ATTR_BASE + 31L)  /* ViInt32, read-write */

/*- Trigger */

#define KTMAWG_ATTR_BURST_COUNT                             (IVI_CLASS_ATTR_BASE + 350L)  /* ViInt32, read-write */
#define KTMAWG_ATTR_TRIGGER_SOURCE                          (IVI_CLASS_ATTR_BASE + 302L)  /* ViInt32, read-write */

/*- Start Trigger */

#define KTMAWG_ATTR_START_TRIGGER_DELAY                     (IVI_CLASS_ATTR_BASE + 320L)  /* ViReal64, read-write */
#define KTMAWG_ATTR_START_TRIGGER_SLOPE                     (IVI_CLASS_ATTR_BASE + 321L)  /* ViInt32, read-write */
#define KTMAWG_ATTR_START_TRIGGER_SOURCE                    (IVI_CLASS_ATTR_BASE + 322L)  /* ViString, read-write */
#define KTMAWG_ATTR_START_TRIGGER_THRESHOLD                 (IVI_CLASS_ATTR_BASE + 323L)  /* ViReal64, read-write */


/**************************************************************************** 
 *------------------------ Attribute Value Defines -------------------------* 
 ****************************************************************************/

/*- Defined values for */

#define KTMAWG_VAL_STATUS_BYTE_FLAGS_USER0                  1
#define KTMAWG_VAL_STATUS_BYTE_FLAGS_USER1                  2
#define KTMAWG_VAL_STATUS_BYTE_FLAGS_USER2                  4
#define KTMAWG_VAL_STATUS_BYTE_FLAGS_USER3                  8
#define KTMAWG_VAL_STATUS_BYTE_FLAGS_MESSAGE_AVAILABLE      16
#define KTMAWG_VAL_STATUS_BYTE_FLAGS_EVENT_STATUS_REGISTER  32
#define KTMAWG_VAL_STATUS_BYTE_FLAGS_REQUESTING_SERVICE     64
#define KTMAWG_VAL_STATUS_BYTE_FLAGS_USER7                  128

/*- Defined values for */

#define KTMAWG_VAL_UPDATE_STATUS_IN_PROGRESS                0
#define KTMAWG_VAL_UPDATE_STATUS_SUCCESS                    1
#define KTMAWG_VAL_UPDATE_STATUS_RESTART_REQUIRED           2
#define KTMAWG_VAL_UPDATE_STATUS_POWER_CYCLE_REQUIRED       3
#define KTMAWG_VAL_UPDATE_STATUS_FAILED                     4

/*- Defined values for 
	attribute KTMAWG_ATTR_CALIBRATION_STATUS
	attribute KTMAWG_ATTR_MODULE_CALIBRATION_STATUS */

#define KTMAWG_VAL_CALIBRATION_STATUS_DUE                        1
#define KTMAWG_VAL_CALIBRATION_STATUS_EXPIRED                    2
#define KTMAWG_VAL_CALIBRATION_STATUS_INSTRUMENT_CALIBRATED      0
#define KTMAWG_VAL_CALIBRATION_STATUS_MODULES_CALIBRATED         5
#define KTMAWG_VAL_CALIBRATION_STATUS_NOT_CALIBRATED             3
#define KTMAWG_VAL_CALIBRATION_STATUS_NOT_SUBJECT_TO_CALIBRATION 4

/*- Defined values for 
	parameter Mask in function KtMAwg_StatusClearEvent
	parameter Mask in function KtMAwg_StatusGetEventState
	parameter Mask in function KtMAwg_StatusSetEvent */

#define KTMAWG_VAL_STATUS_EVENT_ALL                         0
#define KTMAWG_VAL_STATUS_EVENT_ERROR_IN_QUEUE              1
#define KTMAWG_VAL_STATUS_EVENT_THERMAL_SHUTDOWN            14
#define KTMAWG_VAL_STATUS_EVENT_THERMAL_WARNING             15
#define KTMAWG_VAL_STATUS_EVENT_USER_DEFINED                2

/*- Defined values for */

#define KTMAWG_VAL_MODULE_EVENT_ALL                         0
#define KTMAWG_VAL_MODULE_EVENT_TIMER1                      201
#define KTMAWG_VAL_MODULE_EVENT_TIMER2                      202
#define KTMAWG_VAL_MODULE_EVENT_TIMER3                      203
#define KTMAWG_VAL_MODULE_EVENT_TIMER4                      204
#define KTMAWG_VAL_MODULE_EVENT_TRIGGER1                    1
#define KTMAWG_VAL_MODULE_EVENT_TRIGGER10                   10
#define KTMAWG_VAL_MODULE_EVENT_TRIGGER2                    2
#define KTMAWG_VAL_MODULE_EVENT_TRIGGER3                    3
#define KTMAWG_VAL_MODULE_EVENT_TRIGGER4                    4
#define KTMAWG_VAL_MODULE_EVENT_TRIGGER5                    5
#define KTMAWG_VAL_MODULE_EVENT_TRIGGER6                    6
#define KTMAWG_VAL_MODULE_EVENT_TRIGGER7                    7
#define KTMAWG_VAL_MODULE_EVENT_TRIGGER8                    8
#define KTMAWG_VAL_MODULE_EVENT_TRIGGER9                    9
#define KTMAWG_VAL_MODULE_EVENT_USER1                       101
#define KTMAWG_VAL_MODULE_EVENT_USER2                       102
#define KTMAWG_VAL_MODULE_EVENT_USER3                       103
#define KTMAWG_VAL_MODULE_EVENT_USER4                       104

/*- Defined values for */

#define KTMAWG_VAL_SPI_MODE_LSB_FIRST_BYTE                  0
#define KTMAWG_VAL_SPI_MODE_LSB_FIRST_WORD                  1
#define KTMAWG_VAL_SPI_MODE_MSB_FIRST_BYTE                  2
#define KTMAWG_VAL_SPI_MODE_MSB_FIRST_WORD                  3

/*- Defined values for */

#define KTMAWG_VAL_TRIGGER_DIRECTION_INPUT                  0
#define KTMAWG_VAL_TRIGGER_DIRECTION_OUTPUT                 1

/*- Defined values for */

#define KTMAWG_VAL_TRIGGER_MODE_LEVEL                       1
#define KTMAWG_VAL_TRIGGER_MODE_PULSE                       0

/*- Defined values for */

#define KTMAWG_VAL_TRIGGER_POLARITY_NEGATIVE                1
#define KTMAWG_VAL_TRIGGER_POLARITY_POSITIVE                0

/*- Defined values for */

#define KTMAWG_VAL_TRIGGER_PXI_TRIGGER0                     0
#define KTMAWG_VAL_TRIGGER_PXI_TRIGGER1                     1
#define KTMAWG_VAL_TRIGGER_PXI_TRIGGER2                     2
#define KTMAWG_VAL_TRIGGER_PXI_TRIGGER3                     3
#define KTMAWG_VAL_TRIGGER_PXI_TRIGGER4                     4
#define KTMAWG_VAL_TRIGGER_PXI_TRIGGER5                     5
#define KTMAWG_VAL_TRIGGER_PXI_TRIGGER6                     6
#define KTMAWG_VAL_TRIGGER_PXI_TRIGGER7                     7

/*- Defined values for */

#define KTMAWG_VAL_TRIGGER_RESOURCE_NONE                    -1
#define KTMAWG_VAL_TRIGGER_RESOURCE_TRIGGER1                0
#define KTMAWG_VAL_TRIGGER_RESOURCE_TRIGGER2                1
#define KTMAWG_VAL_TRIGGER_RESOURCE_TRIGGER3                2
#define KTMAWG_VAL_TRIGGER_RESOURCE_TRIGGER4                3
#define KTMAWG_VAL_TRIGGER_RESOURCE_TRIGGER5                4
#define KTMAWG_VAL_TRIGGER_RESOURCE_TRIGGER6                5
#define KTMAWG_VAL_TRIGGER_RESOURCE_TRIGGER7                6
#define KTMAWG_VAL_TRIGGER_RESOURCE_TRIGGER8                7
#define KTMAWG_VAL_TRIGGER_RESOURCE_TRIGGER9                8
#define KTMAWG_VAL_TRIGGER_RESOURCE_TRIGGER10               9

/*- Defined values for */

#define KTMAWG_VAL_TRIGGER_TERMINATION_HIGH_IMPEDANCE       0
#define KTMAWG_VAL_TRIGGER_TERMINATION_LOW_IMPEDANCE        1

/*- Defined values for */

#define KTMAWG_VAL_LTC3880_PHASE_BOTH_PHASES                255
#define KTMAWG_VAL_LTC3880_PHASE_PHASE0                     0
#define KTMAWG_VAL_LTC3880_PHASE_PHASE1                     1

/*- Defined values for */

#define KTMAWG_VAL_SELF_TEST_ADC_MEASUREMENT_MODE_COMMON_REFERENCE 1
#define KTMAWG_VAL_SELF_TEST_ADC_MEASUREMENT_MODE_DIFFERENTIAL     0

/*- Defined values for */

#define KTMAWG_VAL_SELF_TEST_ADC_MEASUREMENT_RANGE_VOLTAGE_0P64   5
#define KTMAWG_VAL_SELF_TEST_ADC_MEASUREMENT_RANGE_VOLTAGE1_0P24  1
#define KTMAWG_VAL_SELF_TEST_ADC_MEASUREMENT_RANGE_VOLTAGE_1P28   4
#define KTMAWG_VAL_SELF_TEST_ADC_MEASUREMENT_RANGE_VOLTAGE2_0P48  7
#define KTMAWG_VAL_SELF_TEST_ADC_MEASUREMENT_RANGE_VOLTAGE2_4P576 0
#define KTMAWG_VAL_SELF_TEST_ADC_MEASUREMENT_RANGE_VOLTAGE_2P56   3
#define KTMAWG_VAL_SELF_TEST_ADC_MEASUREMENT_RANGE_VOLTAGE_5P12   2

/*- Defined values for 
	parameter State in function KtMAwg_GetGenerationStateByChannel */

#define KTMAWG_VAL_GENERATION_STATE_CONFIGURATION           0
#define KTMAWG_VAL_GENERATION_STATE_OUTPUT_GENERATION       1

/*- Defined values for */

#define KTMAWG_VAL_MEMORY_QUERY_MODE_TOTAL_SIZE             0
#define KTMAWG_VAL_MEMORY_QUERY_MODE_FREE_SIZE              1
#define KTMAWG_VAL_MEMORY_QUERY_MODE_ALLOCATED_SIZE         2

/*- Defined values for 
	parameter Mode in function KtMAwg_CorrectionsGetFilterMode
	parameter Mode in function KtMAwg_CorrectionsSetFilterMode */

#define KTMAWG_VAL_CORRECTION_FILTER_MODE_UNCALIBRATED      1
#define KTMAWG_VAL_CORRECTION_FILTER_MODE_BYPASS            2
#define KTMAWG_VAL_CORRECTION_FILTER_MODE_CALIBRATED        0

/*- Defined values for */

#define KTMAWG_VAL_ATTRIBUTES_ARBITRARY_SAMPLE_RATE         0
#define KTMAWG_VAL_ATTRIBUTES_OUTPUT_DELAY                  4
#define KTMAWG_VAL_ATTRIBUTES_MARKER_DELAY                  20
#define KTMAWG_VAL_ATTRIBUTES_ARBITRARY_GAIN                10
#define KTMAWG_VAL_ATTRIBUTES_ARBITRARY_ANALOG_GAIN         13
#define KTMAWG_VAL_ATTRIBUTES_ARBITRARY_DIGITAL_GAIN        14
#define KTMAWG_VAL_ATTRIBUTES_ARBITRARY_OFFSET              11
#define KTMAWG_VAL_ATTRIBUTES_ARBITRARY_COMMON_MODE_OFFSET  12
#define KTMAWG_VAL_ATTRIBUTES_ARBITRARY_LOAD_IMPEDANCE      8
#define KTMAWG_VAL_ATTRIBUTES_START_TRIGGER_DELAY           16
#define KTMAWG_VAL_ATTRIBUTES_START_TRIGGER_SOURCE          15
#define KTMAWG_VAL_ATTRIBUTES_MARKER_DESTINATION            19
#define KTMAWG_VAL_ATTRIBUTES_MARKER_BIT_POSITION           21
#define KTMAWG_VAL_ATTRIBUTES_SEQUENCE_TRIGGER_SOURCE       17
#define KTMAWG_VAL_ATTRIBUTES_SEQUENCE_TRIGGER_DELAY        18
#define KTMAWG_VAL_ATTRIBUTES_OUTPUT_OPERATION_MODE         5
#define KTMAWG_VAL_ATTRIBUTES_ARBITRARY_GAIN_CONTROL        9
#define KTMAWG_VAL_ATTRIBUTES_ARBITRARY_CHANNEL_MODE        2
#define KTMAWG_VAL_ATTRIBUTES_ARBITRARY_HANDLE              1
#define KTMAWG_VAL_ATTRIBUTES_OUTPUT_ENABLED                3
#define KTMAWG_VAL_ATTRIBUTES_OUTPUT_TERMINAL_CONFIGURATION 7
#define KTMAWG_VAL_ATTRIBUTES_CORRECTION_FILTER_MODE        22
#define KTMAWG_VAL_ATTRIBUTES_BURST_COUNT                   6

/*- Defined values for 
	parameter Control in function KtMAwg_ArbitrarySetGainControl
	parameter Control in function KtMAwg_ArbitraryGetGainControl */

#define KTMAWG_VAL_GAIN_CONTROL_COMPONENT                   1
#define KTMAWG_VAL_GAIN_CONTROL_COMPOSITE                   0

/*- Defined values for 
	parameter Events in function KtMAwg_QueryGenerationEvents */

#define KTMAWG_VAL_GENERATION_EVENTS_NONE                        0
#define KTMAWG_VAL_GENERATION_EVENTS_DIGITAL_GAIN_BLOCK_OVERFLOW 1
#define KTMAWG_VAL_GENERATION_EVENTS_FIFO_UNDERRUN               2
#define KTMAWG_VAL_GENERATION_EVENTS_RESAMPLER_OVERFLOW          4
#define KTMAWG_VAL_GENERATION_EVENTS_CORRECTIONS_OVERFLOW        8
#define KTMAWG_VAL_GENERATION_EVENTS_MARKER_QUEUE_OVERRUN        16
#define KTMAWG_VAL_GENERATION_EVENTS_MARKER_IGNORED              32

/*- Defined values for 
	attribute KTMAWG_ATTR_OUTPUT_MODE
	parameter OutputMode in function KtMAwg_ConfigureOutputMode */

#define KTMAWG_VAL_OUTPUT_FUNC                              0
#define KTMAWG_VAL_OUTPUT_ARB                               1
#define KTMAWG_VAL_OUTPUT_SEQ                               2

/*- Defined values for 
	attribute KTMAWG_ATTR_OPERATION_MODE
	parameter OperationMode in function KtMAwg_ConfigureOperationMode */

#define KTMAWG_VAL_OPERATE_CONTINUOUS                       0
#define KTMAWG_VAL_OPERATE_BURST                            1

/*- Defined values for 
	attribute KTMAWG_ATTR_REF_CLOCK_SOURCE
	parameter Source in function KtMAwg_ConfigureRefClockSource */

#define KTMAWG_VAL_REF_CLOCK_INTERNAL                       0
#define KTMAWG_VAL_REF_CLOCK_EXTERNAL                       1
#define KTMAWG_VAL_REF_CLOCK_RTSI_CLOCK                     101

/*- Defined values for 
	attribute KTMAWG_ATTR_TRIGGER_SOURCE
	parameter Source in function KtMAwg_ConfigureTriggerSource */

#define KTMAWG_VAL_EXTERNAL                                 1
#define KTMAWG_VAL_SOFTWARE_TRIG                            2
#define KTMAWG_VAL_INTERNAL_TRIGGER                         3
#define KTMAWG_VAL_TTL0                                     111
#define KTMAWG_VAL_TTL1                                     112
#define KTMAWG_VAL_TTL2                                     113
#define KTMAWG_VAL_TTL3                                     114
#define KTMAWG_VAL_TTL4                                     115
#define KTMAWG_VAL_TTL5                                     116
#define KTMAWG_VAL_TTL6                                     117
#define KTMAWG_VAL_TTL7                                     118
#define KTMAWG_VAL_ECL0                                     119
#define KTMAWG_VAL_ECL1                                     120
#define KTMAWG_VAL_PXI_STAR                                 131
#define KTMAWG_VAL_RTSI_0                                   141
#define KTMAWG_VAL_RTSI_1                                   142
#define KTMAWG_VAL_RTSI_2                                   143
#define KTMAWG_VAL_RTSI_3                                   144
#define KTMAWG_VAL_RTSI_4                                   145
#define KTMAWG_VAL_RTSI_5                                   146
#define KTMAWG_VAL_RTSI_6                                   147
#define KTMAWG_VAL_SOFTWARE0                                1001
#define KTMAWG_VAL_SOFTWARE1                                1002
#define KTMAWG_VAL_SOFTWARE2                                1003
#define KTMAWG_VAL_SOFTWARE3                                1004
#define KTMAWG_VAL_SOFTWARE4                                1005
#define KTMAWG_VAL_SOFTWARE5                                1006
#define KTMAWG_VAL_SOFTWARE6                                1007
#define KTMAWG_VAL_SOFTWARE7                                1008
#define KTMAWG_VAL_SOFTWARE9                                1010
#define KTMAWG_VAL_SOFTWARE10                               1011
#define KTMAWG_VAL_SOFTWARE11                               1012
#define KTMAWG_VAL_SOFTWARE12                               1013
#define KTMAWG_VAL_SOFTWARE13                               1014
#define KTMAWG_VAL_SOFTWARE14                               1015
#define KTMAWG_VAL_SOFTWARE15                               1016
#define KTMAWG_VAL_SOFTWARE8                                1009
#define KTMAWG_VAL_PXI_TRIG0                                1017
#define KTMAWG_VAL_PXI_TRIG1                                1018
#define KTMAWG_VAL_PXI_TRIG2                                1019
#define KTMAWG_VAL_PXI_TRIG3                                1020
#define KTMAWG_VAL_PXI_TRIG4                                1021
#define KTMAWG_VAL_PXI_TRIG5                                1022
#define KTMAWG_VAL_PXI_TRIG6                                1023
#define KTMAWG_VAL_PXI_TRIG7                                1024
#define KTMAWG_VAL_EXTERNAL1                                1025
#define KTMAWG_VAL_EXTERNAL2                                1026
#define KTMAWG_VAL_PXIE_DSTARB                              1027
#define KTMAWG_VAL_DIO_0                                    1028
#define KTMAWG_VAL_DIO_1                                    1029
#define KTMAWG_VAL_DIO_2                                    1030
#define KTMAWG_VAL_DIO_3                                    1031
#define KTMAWG_VAL_DIO_4                                    1032
#define KTMAWG_VAL_DIO_5                                    1033
#define KTMAWG_VAL_DIO_7                                    1035
#define KTMAWG_VAL_DIO_6                                    1034
#define KTMAWG_VAL_TRIG_IMMEDIATE                           1036
#define KTMAWG_VAL_DISABLED                                 1037

/*- Defined values for */

#define KTMAWG_VAL_WFM_SINE                                 1
#define KTMAWG_VAL_WFM_SQUARE                               2
#define KTMAWG_VAL_WFM_TRIANGLE                             3
#define KTMAWG_VAL_WFM_RAMP_UP                              4
#define KTMAWG_VAL_WFM_RAMP_DOWN                            5
#define KTMAWG_VAL_WFM_DC                                   6

/*- Defined values for */

#define KTMAWG_VAL_AM_INTERNAL_SINE                         1
#define KTMAWG_VAL_AM_INTERNAL_SQUARE                       2
#define KTMAWG_VAL_AM_INTERNAL_TRIANGLE                     3
#define KTMAWG_VAL_AM_INTERNAL_RAMP_UP                      4
#define KTMAWG_VAL_AM_INTERNAL_RAMP_DOWN                    5

/*- Defined values for */

#define KTMAWG_VAL_AM_INTERNAL                              0
#define KTMAWG_VAL_AM_EXTERNAL                              1

/*- Defined values for */

#define KTMAWG_VAL_FM_INTERNAL_SINE                         1
#define KTMAWG_VAL_FM_INTERNAL_SQUARE                       2
#define KTMAWG_VAL_FM_INTERNAL_TRIANGLE                     3
#define KTMAWG_VAL_FM_INTERNAL_RAMP_UP                      4
#define KTMAWG_VAL_FM_INTERNAL_RAMP_DOWN                    5

/*- Defined values for */

#define KTMAWG_VAL_FM_INTERNAL                              0
#define KTMAWG_VAL_FM_EXTERNAL                              1

/*- Defined values for 
	attribute KTMAWG_ATTR_START_TRIGGER_SLOPE
	parameter Slope in function KtMAwg_ConfigureStartTrigger */

#define KTMAWG_VAL_TRIGGER_POSITIVE                         0
#define KTMAWG_VAL_TRIGGER_NEGATIVE                         1
#define KTMAWG_VAL_TRIGGER_EITHER                           2

/*- Defined values for 
	attribute KTMAWG_ATTR_TERMINAL_CONFIGURATION
	parameter Configuration in function KtMAwg_OutputSetTerminalConfiguration */

#define KTMAWG_VAL_TERMINAL_CONFIGURATION_SINGLE_ENDED      0
#define KTMAWG_VAL_TERMINAL_CONFIGURATION_DIFFERENTIAL      1

/*- Defined values for */

#define KTMAWG_VAL_SAMPLE_CLOCK_SOURCE_INTERNAL             0
#define KTMAWG_VAL_SAMPLE_CLOCK_SOURCE_EXTERNAL             1

/*- Defined values for */

#define KTMAWG_VAL_MARKER_POLARITY_ACTIVE_HIGH              0
#define KTMAWG_VAL_MARKER_POLARITY_ACTIVE_LOW               1

/*- Defined values for 
	attribute KTMAWG_ATTR_BINARY_ALIGNMENT */

#define KTMAWG_VAL_BINARY_ALIGNMENT_LEFT                    0
#define KTMAWG_VAL_BINARY_ALIGNMENT_RIGHT                   1

/*- Defined values for 
	parameter Mode in function KtMAwg_GetChannelMode
	parameter Mode in function KtMAwg_SetChannelMode */

#define KTMAWG_VAL_CHANNEL_MODE_WAVEFORM                    0
#define KTMAWG_VAL_CHANNEL_MODE_MARKER                      1

/*- Defined values for */

#define KTMAWG_VAL_EXTERNAL_IMPEDANCE_OHM_1K                0
#define KTMAWG_VAL_EXTERNAL_IMPEDANCE_OHM50                 1

/*- Defined values for */

#define KTMAWG_VAL_EXTERNAL_ATTRIBUTES_THRESHOLD            0

/*- Defined values for 
	attribute KTMAWG_ATTR_EXTERNAL_INPUT_SLOPE
	attribute KTMAWG_ATTR_TRIGGER_BUS_LINE_INPUT_SLOPE */

#define KTMAWG_VAL_INPUT_SLOPE_POSITIVE                     0
#define KTMAWG_VAL_INPUT_SLOPE_NEGATIVE                     1

/*- Defined values for 
	attribute KTMAWG_ATTR_EXTERNAL_OUTPUT_POLARITY
	attribute KTMAWG_ATTR_TRIGGER_BUS_LINE_OUTPUT_POLARITY
	parameter Val in function KtMAwg_GetChannelMarkerPolarity
	parameter Polarity in function KtMAwg_SetChannelMarkerPolarity */

#define KTMAWG_VAL_OUTPUT_POLARITY_POSITIVE                 0
#define KTMAWG_VAL_OUTPUT_POLARITY_NEGATIVE                 1

/*- Defined values for 
	parameter Option in function KtMAwg_MemoryTest */

#define KTMAWG_VAL_MEMORY_TEST_STANDARD                     1
#define KTMAWG_VAL_MEMORY_TEST_COMPREHENSIVE                0

/*- Defined values for 
	attribute KTMAWG_ATTR_TRIGGER_BUS_LINE_CAPABILITY */

#define KTMAWG_VAL_TRIGGER_BUS_LINE_CAPABILITY_INPUT        1
#define KTMAWG_VAL_TRIGGER_BUS_LINE_CAPABILITY_OUTPUT       2
#define KTMAWG_VAL_TRIGGER_BUS_LINE_CAPABILITY_BOTH         3

/*- Defined values for 
	attribute KTMAWG_ATTR_DEVICE_SYNC_GROUP_SIGNAL
	attribute KTMAWG_ATTR_DEVICE_SYNC_SLAVE_SIGNAL
	parameter GroupSignal in function KtMAwg_DeviceSyncConfigureMaster
	parameter SlaveSignals in function KtMAwg_DeviceSyncConfigureMaster
	parameter GroupSignal in function KtMAwg_DeviceSyncConfigureSlave
	parameter SlaveSignal in function KtMAwg_DeviceSyncConfigureSlave
	parameter Val in function KtMAwg_DeviceSyncGetGroupMask
	parameter SlaveSignals in function KtMAwg_DeviceSyncSetGroupMask */

#define KTMAWG_VAL_DEVICE_SYNC_RESOURCESFP_SYNC             32768
#define KTMAWG_VAL_DEVICE_SYNC_RESOURCES_NONE               0
#define KTMAWG_VAL_DEVICE_SYNC_RESOURCESPXI_LBL6            2048
#define KTMAWG_VAL_DEVICE_SYNC_RESOURCESPXI_LBR6            1024
#define KTMAWG_VAL_DEVICE_SYNC_RESOURCESPXI_STAR            512
#define KTMAWG_VAL_DEVICE_SYNC_RESOURCESPXI_TRIG0           1
#define KTMAWG_VAL_DEVICE_SYNC_RESOURCESPXI_TRIG1           2
#define KTMAWG_VAL_DEVICE_SYNC_RESOURCESPXI_TRIG2           4
#define KTMAWG_VAL_DEVICE_SYNC_RESOURCESPXI_TRIG3           8
#define KTMAWG_VAL_DEVICE_SYNC_RESOURCESPXI_TRIG4           16
#define KTMAWG_VAL_DEVICE_SYNC_RESOURCESPXI_TRIG5           32
#define KTMAWG_VAL_DEVICE_SYNC_RESOURCESPXI_TRIG6           64
#define KTMAWG_VAL_DEVICE_SYNC_RESOURCESPXI_TRIG7           128
#define KTMAWG_VAL_DEVICE_SYNC_RESOURCESPXIE_DSTARA         4096
#define KTMAWG_VAL_DEVICE_SYNC_RESOURCESPXIE_DSTARB         8192
#define KTMAWG_VAL_DEVICE_SYNC_RESOURCESPXIE_DSTARC         16384

/*- Defined values for 
	attribute KTMAWG_ATTR_DEVICE_SYNC_ROLE
	parameter Role in function KtMAwg_DeviceSyncConfigureMaster */

#define KTMAWG_VAL_DEVICE_SYNC_ROLE_GROUP_MASTER            3
#define KTMAWG_VAL_DEVICE_SYNC_ROLE_LOCAL_MASTER            5
#define KTMAWG_VAL_DEVICE_SYNC_ROLE_OFF                     0
#define KTMAWG_VAL_DEVICE_SYNC_ROLE_SLAVE                   2
#define KTMAWG_VAL_DEVICE_SYNC_ROLE_SANDBOX                 1
#define KTMAWG_VAL_DEVICE_SYNC_ROLE_SYSTEM_MASTER           4

/*- Defined values for 
	attribute KTMAWG_ATTR_DEVICE_SYNC_STATE */

#define KTMAWG_VAL_DEVICE_SYNC_STATE_ARM                    1
#define KTMAWG_VAL_DEVICE_SYNC_STATE_IDLE                   0
#define KTMAWG_VAL_DEVICE_SYNC_STATE_RUN                    3
#define KTMAWG_VAL_DEVICE_SYNC_STATE_TRIGGER                2
#define KTMAWG_VAL_DEVICE_SYNC_STATE_UNKNOWN                4


/**************************************************************************** 
 *---------------- Instrument Driver Function Declarations -----------------* 
 ****************************************************************************/

/*- KtMAwg */

ViStatus _VI_FUNC KtMAwg_init(ViRsrc ResourceName, ViBoolean IdQuery, ViBoolean Reset, ViSession* Vi);
ViStatus _VI_FUNC KtMAwg_close(ViSession Vi);
ViStatus _VI_FUNC KtMAwg_InitWithOptions(ViRsrc ResourceName, ViBoolean IdQuery, ViBoolean Reset, ViConstString OptionsString, ViSession* Vi);

/*- Instrument Specific */

ViStatus _VI_FUNC KtMAwg_Apply(ViSession Vi);
ViStatus _VI_FUNC KtMAwg_InitiateGenerationByChannel(ViSession Vi, ViConstString Channel);
ViStatus _VI_FUNC KtMAwg_Discard(ViSession Vi);
ViStatus _VI_FUNC KtMAwg_Resolve(ViSession Vi);
ViStatus _VI_FUNC KtMAwg_Validate(ViSession Vi);
ViStatus _VI_FUNC KtMAwg_AbortGenerationByChannel(ViSession Vi, ViConstString ChannelName);
ViStatus _VI_FUNC KtMAwg_QueryGenerationEvents(ViSession Vi, ViConstString ChannelName, ViBoolean Reset, ViInt32* Events);
ViStatus _VI_FUNC KtMAwg_GetGenerationStateByChannel(ViSession Vi, ViConstString ChannelName, ViInt32* State);
ViStatus _VI_FUNC KtMAwg_EnableGenerationSettingsRestrictions(ViSession Vi);
ViStatus _VI_FUNC KtMAwg_DisableGenerationSettingsRestrictions(ViSession Vi);

/*- System */

ViStatus _VI_FUNC KtMAwg_SystemGetModuleSlotAssignments(ViSession Vi, ViInt32 SlotsBufferSize, ViInt32 Slots[], ViInt32* SlotsActualSize);
ViStatus _VI_FUNC KtMAwg_SystemGetModuleInformation(ViSession Vi, ViInt32 SlotIndex, ViInt32 IdentityBufferSize, ViChar Identity[]);
ViStatus _VI_FUNC KtMAwg_MemoryTest(ViSession Vi, ViInt32 Option, ViInt16* TestResult, ViChar Message[]);

/*- Status */

ViStatus _VI_FUNC KtMAwg_StatusClearEvent(ViSession Vi, ViInt32 Mask);
ViStatus _VI_FUNC KtMAwg_StatusGetEventState(ViSession Vi, ViInt32 Mask, ViBoolean* State);
ViStatus _VI_FUNC KtMAwg_StatusSetEvent(ViSession Vi, ViInt32 Mask);

/*- Module */

ViStatus _VI_FUNC KtMAwg_GetModuleName(ViSession Vi, ViInt32 Index, ViInt32 NameBufferSize, ViChar Name[]);
ViStatus _VI_FUNC KtMAwg_ModuleGetValue(ViSession Vi, ViConstString Module, ViConstString Name, ViInt32 ValBufferSize, ViChar Val[]);
ViStatus _VI_FUNC KtMAwg_ModuleSetValue(ViSession Vi, ViConstString Module, ViConstString Name, ViConstString Value);

/*- Nonvolatile */

ViStatus _VI_FUNC KtMAwg_NonvolatileClear(ViSession Vi, ViConstString Module);
ViStatus _VI_FUNC KtMAwg_NonvolatileWrite(ViSession Vi, ViConstString Module, ViConstString Passphrase);

/*- AssetChannel */

ViStatus _VI_FUNC KtMAwg_GetAssetChannelName(ViSession Vi, ViConstString Resource, ViInt32 Index, ViInt32 NameBufferSize, ViChar Name[]);

/*- Output */

ViStatus _VI_FUNC KtMAwg_GetCalibrationCoefficient(ViSession Vi, ViConstString AssetChannel, ViConstString CalibrationCoefficient, ViReal64* Val);

/*- PeerToPeerPort */

ViStatus _VI_FUNC KtMAwg_GetPeerToPeerPortName(ViSession Vi, ViInt32 Index, ViInt32 NameBufferSize, ViChar Name[]);
ViStatus _VI_FUNC KtMAwg_SetActivePeerToPeerPort(ViSession Vi, ViConstString Name);

/*- DeviceSync */

ViStatus _VI_FUNC KtMAwg_DeviceSyncAbort(ViSession Vi);
ViStatus _VI_FUNC KtMAwg_DeviceSyncConfigureMaster(ViSession Vi, ViInt32 Role, ViInt32 GroupSignal, ViInt32 SlaveSignalsBufferSize, ViInt32 SlaveSignals[]);
ViStatus _VI_FUNC KtMAwg_DeviceSyncConfigureSlave(ViSession Vi, ViInt32 GroupSignal, ViInt32 SlaveSignal);
ViStatus _VI_FUNC KtMAwg_DeviceSyncGetGroupMask(ViSession Vi, ViInt32 ValBufferSize, ViInt32 Val[], ViInt32* ValActualSize);
ViStatus _VI_FUNC KtMAwg_DeviceSyncInitializeClocks(ViSession Vi);
ViStatus _VI_FUNC KtMAwg_DeviceSyncInitiate(ViSession Vi);
ViStatus _VI_FUNC KtMAwg_DeviceSyncSetGroupMask(ViSession Vi, ViInt32 SlaveSignalsBufferSize, ViInt32 SlaveSignals[]);

/*- Output */

ViStatus _VI_FUNC KtMAwg_OutputSetDelay(ViSession Vi, ViConstString ChannelName, ViReal64 Delay);
ViStatus _VI_FUNC KtMAwg_GetChannelMode(ViSession Vi, ViConstString ChannelName, ViInt32* Mode);
ViStatus _VI_FUNC KtMAwg_SetChannelMode(ViSession Vi, ViConstString ChannelName, ViInt32 Mode);
ViStatus _VI_FUNC KtMAwg_OutputSetTerminalConfiguration(ViSession Vi, ViConstString ChannelName, ViInt32 Configuration);
ViStatus _VI_FUNC KtMAwg_OutputGetDelay(ViSession Vi, ViConstString ChannelName, ViReal64* Delay);
ViStatus _VI_FUNC KtMAwg_GetChannelMarkerPolarity(ViSession Vi, ViConstString ChannelName, ViInt32* Val);
ViStatus _VI_FUNC KtMAwg_SetChannelMarkerPolarity(ViSession Vi, ViConstString ChannelName, ViInt32 Polarity);

/*- Arbitrary */

ViStatus _VI_FUNC KtMAwg_ArbitrarySetGain(ViSession Vi, ViConstString ChannelName, ViReal64 Gain);
ViStatus _VI_FUNC KtMAwg_ArbitrarySetOffset(ViSession Vi, ViConstString ChannelName, ViReal64 Offset);
ViStatus _VI_FUNC KtMAwg_ArbitrarySetGainControl(ViSession Vi, ViConstString ChannelName, ViInt32 Control);
ViStatus _VI_FUNC KtMAwg_ArbitrarySetHandle(ViSession Vi, ViConstString ChannelName, ViInt32 Handle);
ViStatus _VI_FUNC KtMAwg_ArbitraryGetHandle(ViSession Vi, ViConstString ChannelName, ViInt32* Handle);
ViStatus _VI_FUNC KtMAwg_ArbitrarySetCommonModeOffset(ViSession Vi, ViConstString ChannelName, ViReal64 Offset);
ViStatus _VI_FUNC KtMAwg_ArbitrarySetDigitalGain(ViSession Vi, ViConstString ChannelName, ViReal64 Gain);
ViStatus _VI_FUNC KtMAwg_ArbitrarySetAnalogGain(ViSession Vi, ViConstString ChannelName, ViReal64 Gain);
ViStatus _VI_FUNC KtMAwg_ArbitraryGetAnalogGain(ViSession Vi, ViConstString ChannelName, ViReal64* Gain);
ViStatus _VI_FUNC KtMAwg_ArbitraryGetCommonModeOffset(ViSession Vi, ViConstString ChannelName, ViReal64* Offset);
ViStatus _VI_FUNC KtMAwg_ArbitraryGetDigitalGain(ViSession Vi, ViConstString ChannelName, ViReal64* Gain);
ViStatus _VI_FUNC KtMAwg_ArbitraryGetGainControl(ViSession Vi, ViConstString ChannelName, ViInt32* Control);
ViStatus _VI_FUNC KtMAwg_ArbitrarySetSampleRateByChannel(ViSession Vi, ViConstString ChannelName, ViReal64 Rate);
ViStatus _VI_FUNC KtMAwg_ArbitraryGetSampleRateByChannel(ViSession Vi, ViConstString ChannelName, ViReal64* Rate);

/*- Waveform */

ViStatus _VI_FUNC KtMAwg_WaveformCreateChannelWaveform(ViSession Vi, ViConstString Channel, ViConstString Name, ViInt32 SamplesBufferSize, ViReal64 Samples[], ViInt32 MarkersBufferSize, ViByte Markers[], ViInt32* Handle);
ViStatus _VI_FUNC KtMAwg_WaveformCreateChannelWaveformInt16(ViSession Vi, ViConstString Channel, ViConstString Name, ViInt32 SamplesBufferSize, ViInt16 Samples[], ViInt32 MarkersBufferSize, ViByte Markers[], ViInt32* Handle);
ViStatus _VI_FUNC KtMAwg_WaveformCreateChannelWaveformInt32(ViSession Vi, ViConstString Channel, ViConstString Name, ViInt32 SamplesBufferSize, ViInt32 Samples[], ViInt32* Handle);
ViStatus _VI_FUNC KtMAwg_ArbitraryWaveformConfigure(ViSession Vi, ViConstString ChannelName, ViInt32 Handle, ViReal64 Gain, ViReal64 Offset, ViReal64 CommonModeOffset);
ViStatus _VI_FUNC KtMAwg_WaveformCreateChannelWaveformFromFile(ViSession Vi, ViConstString ChannelName, ViConstString Name, ViInt64 MaximumSize, ViConstString Filename, ViInt32* Handle);

/*- Corrections */

ViStatus _VI_FUNC KtMAwg_CorrectionsGetFilterMode(ViSession Vi, ViConstString ChannelName, ViInt32* Mode);
ViStatus _VI_FUNC KtMAwg_CorrectionsSetFilterMode(ViSession Vi, ViConstString ChannelName, ViInt32 Mode);

/*- Sequence */

ViStatus _VI_FUNC KtMAwg_SequenceSetHandle(ViSession Vi, ViConstString ChannelName, ViInt32 Handle);
ViStatus _VI_FUNC KtMAwg_SequenceGetHandle(ViSession Vi, ViConstString ChannelName, ViInt32* Handle);
ViStatus _VI_FUNC KtMAwg_SequenceCreateFromFile(ViSession Vi, ViConstString Name, ViConstString Filename, ViInt32* Handle);
ViStatus _VI_FUNC KtMAwg_SequenceValidateFile(ViSession Vi, ViConstString Filename, ViBoolean IncludeReferences, ViInt32 MessagesBufferSize, ViChar Messages[]);
ViStatus _VI_FUNC KtMAwg_SequenceCreate(ViSession Vi, ViConstString Name, ViInt32 Length, ViInt32 ReferenceHandles[], ViInt32 LoopCounts[], ViInt32* Handle);

/*- Noise */

ViStatus _VI_FUNC KtMAwg_NoiseSetGain(ViSession Vi, ViConstString ChannelName, ViReal64 Gain);
ViStatus _VI_FUNC KtMAwg_NoiseGetGain(ViSession Vi, ViConstString ChannelName, ViReal64* Gain);
ViStatus _VI_FUNC KtMAwg_NoiseSetBandwidth(ViSession Vi, ViConstString ChannelName, ViReal64 Bandwidth);
ViStatus _VI_FUNC KtMAwg_NoiseGetBandwidth(ViSession Vi, ViConstString ChannelName, ViReal64* Bandwidth);
ViStatus _VI_FUNC KtMAwg_NoiseGetEnabled(ViSession Vi, ViConstString ChannelName, ViBoolean* Enabled);
ViStatus _VI_FUNC KtMAwg_NoiseSetEnabled(ViSession Vi, ViConstString ChannelName, ViBoolean Enabled);

/*- Trigger */

ViStatus _VI_FUNC KtMAwg_TriggerGenerateSoftwareEvents(ViSession Vi, ViInt32 EventBits);

/*- Start */

ViStatus _VI_FUNC KtMAwg_TriggerStartSetDelay(ViSession Vi, ViConstString ChannelName, ViReal64 DelayValue);
ViStatus _VI_FUNC KtMAwg_TriggerStartGetDelay(ViSession Vi, ViConstString ChannelName, ViReal64* Delay);
ViStatus _VI_FUNC KtMAwg_SendSoftwareTriggerByChannel(ViSession Vi, ViConstString ChannelName);

/*- SequenceTriggers */

ViStatus _VI_FUNC KtMAwg_SequenceTriggerAdd(ViSession Vi, ViConstString Name);
ViStatus _VI_FUNC KtMAwg_SequenceTriggerRemove(ViSession Vi, ViConstString Name);
ViStatus _VI_FUNC KtMAwg_SequenceTriggerClear(ViSession Vi);
ViStatus _VI_FUNC KtMAwg_SequenceTriggerConfigure(ViSession Vi, ViConstString GeneralTrigger, ViConstString ChannelName, ViConstString SourceName, ViReal64 Delay);
ViStatus _VI_FUNC KtMAwg_SequenceTriggerGetDelay(ViSession Vi, ViConstString GeneralTrigger, ViConstString ChannelName, ViReal64* Delay);
ViStatus _VI_FUNC KtMAwg_SequenceTriggerSetDelay(ViSession Vi, ViConstString GeneralTrigger, ViConstString ChannelName, ViReal64 Delay);
ViStatus _VI_FUNC KtMAwg_SequenceTriggerGetSource(ViSession Vi, ViConstString GeneralTrigger, ViConstString ChannelName, ViInt32 SourceBufferSize, ViChar Source[]);
ViStatus _VI_FUNC KtMAwg_SequenceTriggerSetSource(ViSession Vi, ViConstString GeneralTrigger, ViConstString ChannelName, ViConstString SourceName);
ViStatus _VI_FUNC KtMAwg_GetSequenceTriggerName(ViSession Vi, ViInt32 Index, ViInt32 NameBufferSize, ViChar Name[]);

/*- Marker */

ViStatus _VI_FUNC KtMAwg_GetMarkerName(ViSession Vi, ViInt32 Index, ViInt32 NameBufferSize, ViChar Name[]);
ViStatus _VI_FUNC KtMAwg_MarkerAdd(ViSession Vi, ViConstString Name);
ViStatus _VI_FUNC KtMAwg_MarkerClear(ViSession Vi);
ViStatus _VI_FUNC KtMAwg_MarkerRemove(ViSession Vi, ViConstString Name);
ViStatus _VI_FUNC KtMAwg_MarkerSetDestination(ViSession Vi, ViConstString Marker, ViConstString ChannelName, ViConstString Destination);
ViStatus _VI_FUNC KtMAwg_MarkerGetDestination(ViSession Vi, ViConstString Marker, ViConstString ChannelName, ViInt32 DestinationBufferSize, ViChar Destination[]);
ViStatus _VI_FUNC KtMAwg_MarkerGetBitPosition(ViSession Vi, ViConstString Marker, ViConstString ChannelName, ViInt32* Position);
ViStatus _VI_FUNC KtMAwg_MarkerSetBitPosition(ViSession Vi, ViConstString Marker, ViConstString ChannelName, ViInt32 Position);
ViStatus _VI_FUNC KtMAwg_MarkerConfigure(ViSession Vi, ViConstString Marker, ViConstString ChannelName, ViInt32 BitPosition, ViConstString Destination);
ViStatus _VI_FUNC KtMAwg_MarkerGetDelay(ViSession Vi, ViConstString Marker, ViConstString ChannelName, ViReal64* Delay);
ViStatus _VI_FUNC KtMAwg_MarkerSetDelay(ViSession Vi, ViConstString Marker, ViConstString ChannelName, ViReal64 Delay);

/*- External */

ViStatus _VI_FUNC KtMAwg_GetExternalName(ViSession Vi, ViInt32 Index, ViInt32 NameBufferSize, ViChar Name[]);
ViStatus _VI_FUNC KtMAwg_ExternalGetThreshold(ViSession Vi, ViConstString External, ViReal64* Voltage);
ViStatus _VI_FUNC KtMAwg_ExternalSetThreshold(ViSession Vi, ViConstString External, ViReal64 Voltage);

/*- TriggerBusLine */

ViStatus _VI_FUNC KtMAwg_GetTriggerBusLineName(ViSession Vi, ViInt32 Index, ViInt32 NameBufferSize, ViChar Name[]);

/*- ReferenceClock */

ViStatus _VI_FUNC KtMAwg_ReferenceClockAcquirePhaseLock(ViSession Vi);

/*- Utility */

ViStatus _VI_FUNC KtMAwg_revision_query(ViSession Vi, ViChar DriverRev[], ViChar InstrRev[]);
ViStatus _VI_FUNC KtMAwg_error_message(ViSession Vi, ViStatus ErrorCode, ViChar ErrorMessage[]);
ViStatus _VI_FUNC KtMAwg_GetError(ViSession Vi, ViStatus* ErrorCode, ViInt32 ErrorDescriptionBufferSize, ViChar ErrorDescription[]);
ViStatus _VI_FUNC KtMAwg_ClearError(ViSession Vi);
ViStatus _VI_FUNC KtMAwg_GetNextCoercionRecord(ViSession Vi, ViInt32 CoercionRecordBufferSize, ViChar CoercionRecord[]);
ViStatus _VI_FUNC KtMAwg_InvalidateAllAttributes(ViSession Vi);
ViStatus _VI_FUNC KtMAwg_Disable(ViSession Vi);
ViStatus _VI_FUNC KtMAwg_error_query(ViSession Vi, ViInt32* ErrorCode, ViChar ErrorMessage[]);
ViStatus _VI_FUNC KtMAwg_LockSession(ViSession Vi, ViBoolean* CallerHasLock);
ViStatus _VI_FUNC KtMAwg_reset(ViSession Vi);
ViStatus _VI_FUNC KtMAwg_ResetWithDefaults(ViSession Vi);
ViStatus _VI_FUNC KtMAwg_self_test(ViSession Vi, ViInt16* TestResult, ViChar TestMessage[]);
ViStatus _VI_FUNC KtMAwg_UnlockSession(ViSession Vi, ViBoolean* CallerHasLock);
ViStatus _VI_FUNC KtMAwg_GetChannelName(ViSession Vi, ViInt32 Index, ViInt32 NameBufferSize, ViChar Name[]);

/*- Attribute Accessors */

ViStatus _VI_FUNC KtMAwg_GetAttributeViInt32(ViSession Vi, ViConstString RepCapIdentifier, ViAttr AttributeID, ViInt32* AttributeValue);
ViStatus _VI_FUNC KtMAwg_GetAttributeViReal64(ViSession Vi, ViConstString RepCapIdentifier, ViAttr AttributeID, ViReal64* AttributeValue);
ViStatus _VI_FUNC KtMAwg_GetAttributeViBoolean(ViSession Vi, ViConstString RepCapIdentifier, ViAttr AttributeID, ViBoolean* AttributeValue);
ViStatus _VI_FUNC KtMAwg_GetAttributeViSession(ViSession Vi, ViConstString RepCapIdentifier, ViAttr AttributeID, ViSession* AttributeValue);
ViStatus _VI_FUNC KtMAwg_GetAttributeViString(ViSession Vi, ViConstString RepCapIdentifier, ViAttr AttributeID, ViInt32 AttributeValueBufferSize, ViChar AttributeValue[]);
ViStatus _VI_FUNC KtMAwg_SetAttributeViInt32(ViSession Vi, ViConstString RepCapIdentifier, ViAttr AttributeID, ViInt32 AttributeValue);
ViStatus _VI_FUNC KtMAwg_SetAttributeViReal64(ViSession Vi, ViConstString RepCapIdentifier, ViAttr AttributeID, ViReal64 AttributeValue);
ViStatus _VI_FUNC KtMAwg_SetAttributeViBoolean(ViSession Vi, ViConstString RepCapIdentifier, ViAttr AttributeID, ViBoolean AttributeValue);
ViStatus _VI_FUNC KtMAwg_SetAttributeViSession(ViSession Vi, ViConstString RepCapIdentifier, ViAttr AttributeID, ViSession AttributeValue);
ViStatus _VI_FUNC KtMAwg_SetAttributeViString(ViSession Vi, ViConstString RepCapIdentifier, ViAttr AttributeID, ViConstString AttributeValue);
ViStatus _VI_FUNC KtMAwg_GetAttributeViInt64(ViSession Vi, ViConstString RepCapIdentifier, ViAttr AttributeID, ViInt64* AttributeValue);
ViStatus _VI_FUNC KtMAwg_SetAttributeViInt64(ViSession Vi, ViConstString RepCapIdentifier, ViAttr AttributeID, ViInt64 AttributeValue);

/*- General */

ViStatus _VI_FUNC KtMAwg_ConfigureOperationMode(ViSession Vi, ViConstString ChannelName, ViInt32 OperationMode);
ViStatus _VI_FUNC KtMAwg_ConfigureOutputEnabled(ViSession Vi, ViConstString ChannelName, ViBoolean Enabled);
ViStatus _VI_FUNC KtMAwg_ConfigureOutputImpedance(ViSession Vi, ViConstString ChannelName, ViReal64 Impedance);
ViStatus _VI_FUNC KtMAwg_ConfigureOutputMode(ViSession Vi, ViInt32 OutputMode);
ViStatus _VI_FUNC KtMAwg_ConfigureRefClockSource(ViSession Vi, ViInt32 Source);

/*- Arbitrary Waveform */

ViStatus _VI_FUNC KtMAwg_ConfigureSampleRate(ViSession Vi, ViReal64 SampleRate);
ViStatus _VI_FUNC KtMAwg_QueryArbWfmCapabilities(ViSession Vi, ViInt32* MaxNumWfms, ViInt32* WfmQuantum, ViInt32* MinWfmSize, ViInt32* MaxWfmSize);
ViStatus _VI_FUNC KtMAwg_QueryArbWfmCapabilities64(ViSession Vi, ViInt64* MaxNumWfms, ViInt64* WfmQuantum, ViInt64* MinWfmSize, ViInt64* MaxWfmSize);
ViStatus _VI_FUNC KtMAwg_ClearArbWaveform(ViSession Vi, ViInt32 Handle);
ViStatus _VI_FUNC KtMAwg_ConfigureArbWaveform(ViSession Vi, ViConstString ChannelName, ViInt32 Handle, ViReal64 Gain, ViReal64 Offset);
ViStatus _VI_FUNC KtMAwg_CreateArbWaveform(ViSession Vi, ViInt32 Size, ViReal64 Data[], ViInt32* Handle);
ViStatus _VI_FUNC KtMAwg_CreateChannelArbWaveform(ViSession Vi, ViConstString ChannelName, ViInt64 Size, ViReal64 Data[], ViInt32* Handle);
ViStatus _VI_FUNC KtMAwg_CreateChannelArbWaveform16(ViSession Vi, ViConstString ChannelName, ViInt64 Size, ViInt16 Data[], ViInt32* Handle);
ViStatus _VI_FUNC KtMAwg_CreateChannelArbWaveform32(ViSession Vi, ViConstString ChannelName, ViInt64 Size, ViInt32 Data[], ViInt32* Handle);

/*- Arbitrary Sequence */

ViStatus _VI_FUNC KtMAwg_QueryArbSeqCapabilities(ViSession Vi, ViInt32* MaxNumSeqs, ViInt32* MinSeqLength, ViInt32* MaxSeqLength, ViInt32* MaxLoopCount);
ViStatus _VI_FUNC KtMAwg_ClearArbMemory(ViSession Vi);
ViStatus _VI_FUNC KtMAwg_ClearArbSequence(ViSession Vi, ViInt32 Handle);
ViStatus _VI_FUNC KtMAwg_ConfigureArbSequence(ViSession Vi, ViConstString ChannelName, ViInt32 Handle, ViReal64 Gain, ViReal64 Offset);
ViStatus _VI_FUNC KtMAwg_CreateArbSequence(ViSession Vi, ViInt32 Length, ViInt32 WfmHandle[], ViInt32 LoopCount[], ViInt32* Handle);

/*- Trigger */

ViStatus _VI_FUNC KtMAwg_ConfigureTriggerSource(ViSession Vi, ViConstString ChannelName, ViInt32 Source);
ViStatus _VI_FUNC KtMAwg_ConfigureStartTrigger(ViSession Vi, ViConstString ChannelName, ViConstString Source, ViInt32 Slope);

/*- Burst */

ViStatus _VI_FUNC KtMAwg_ConfigureBurstCount(ViSession Vi, ViConstString ChannelName, ViInt32 Count);

/*- Action */

ViStatus _VI_FUNC KtMAwg_AbortGeneration(ViSession Vi);
ViStatus _VI_FUNC KtMAwg_InitiateGeneration(ViSession Vi);
ViStatus _VI_FUNC KtMAwg_SendSoftwareTrigger(ViSession Vi);


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


#define KTMAWG_ERROR_CANNOT_RECOVER                         (IVIC_ERROR_BASE + 0x0000)
#define KTMAWG_ERROR_INSTRUMENT_STATUS                      (IVIC_ERROR_BASE + 0x0001)
#define KTMAWG_ERROR_CANNOT_OPEN_FILE                       (IVIC_ERROR_BASE + 0x0002)
#define KTMAWG_ERROR_READING_FILE                           (IVIC_ERROR_BASE + 0x0003)
#define KTMAWG_ERROR_WRITING_FILE                           (IVIC_ERROR_BASE + 0x0004)
#define KTMAWG_ERROR_INVALID_PATHNAME                       (IVIC_ERROR_BASE + 0x000B)
#define KTMAWG_ERROR_INVALID_ATTRIBUTE                      (IVIC_ERROR_BASE + 0x000C)
#define KTMAWG_ERROR_IVI_ATTR_NOT_WRITABLE                  (IVIC_ERROR_BASE + 0x000D)
#define KTMAWG_ERROR_IVI_ATTR_NOT_READABLE                  (IVIC_ERROR_BASE + 0x000E)
#define KTMAWG_ERROR_INVALID_VALUE                          (IVIC_ERROR_BASE + 0x0010)
#define KTMAWG_ERROR_FUNCTION_NOT_SUPPORTED                 (IVIC_ERROR_BASE + 0x0011)
#define KTMAWG_ERROR_ATTRIBUTE_NOT_SUPPORTED                (IVIC_ERROR_BASE + 0x0012)
#define KTMAWG_ERROR_VALUE_NOT_SUPPORTED                    (IVIC_ERROR_BASE + 0x0013)
#define KTMAWG_ERROR_TYPES_DO_NOT_MATCH                     (IVIC_ERROR_BASE + 0x0015)
#define KTMAWG_ERROR_NOT_INITIALIZED                        (IVIC_ERROR_BASE + 0x001D)
#define KTMAWG_ERROR_UNKNOWN_CHANNEL_NAME                   (IVIC_ERROR_BASE + 0x0020)
#define KTMAWG_ERROR_TOO_MANY_OPEN_FILES                    (IVIC_ERROR_BASE + 0x0023)
#define KTMAWG_ERROR_CHANNEL_NAME_REQUIRED                  (IVIC_ERROR_BASE + 0x0044)
#define KTMAWG_ERROR_MISSING_OPTION_NAME                    (IVIC_ERROR_BASE + 0x0049)
#define KTMAWG_ERROR_MISSING_OPTION_VALUE                   (IVIC_ERROR_BASE + 0x004A)
#define KTMAWG_ERROR_BAD_OPTION_NAME                        (IVIC_ERROR_BASE + 0x004B)
#define KTMAWG_ERROR_BAD_OPTION_VALUE                       (IVIC_ERROR_BASE + 0x004C)
#define KTMAWG_ERROR_OUT_OF_MEMORY                          (IVIC_ERROR_BASE + 0x0056)
#define KTMAWG_ERROR_OPERATION_PENDING                      (IVIC_ERROR_BASE + 0x0057)
#define KTMAWG_ERROR_NULL_POINTER                           (IVIC_ERROR_BASE + 0x0058)
#define KTMAWG_ERROR_UNEXPECTED_RESPONSE                    (IVIC_ERROR_BASE + 0x0059)
#define KTMAWG_ERROR_FILE_NOT_FOUND                         (IVIC_ERROR_BASE + 0x005B)
#define KTMAWG_ERROR_INVALID_FILE_FORMAT                    (IVIC_ERROR_BASE + 0x005C)
#define KTMAWG_ERROR_STATUS_NOT_AVAILABLE                   (IVIC_ERROR_BASE + 0x005D)
#define KTMAWG_ERROR_ID_QUERY_FAILED                        (IVIC_ERROR_BASE + 0x005E)
#define KTMAWG_ERROR_RESET_FAILED                           (IVIC_ERROR_BASE + 0x005F)
#define KTMAWG_ERROR_RESOURCE_UNKNOWN                       (IVIC_ERROR_BASE + 0x0060)
#define KTMAWG_ERROR_ALREADY_INITIALIZED                    (IVIC_ERROR_BASE + 0x0061)
#define KTMAWG_ERROR_CANNOT_CHANGE_SIMULATION_STATE         (IVIC_ERROR_BASE + 0x0062)
#define KTMAWG_ERROR_INVALID_NUMBER_OF_LEVELS_IN_SELECTOR   (IVIC_ERROR_BASE + 0x0063)
#define KTMAWG_ERROR_INVALID_RANGE_IN_SELECTOR              (IVIC_ERROR_BASE + 0x0064)
#define KTMAWG_ERROR_UNKOWN_NAME_IN_SELECTOR                (IVIC_ERROR_BASE + 0x0065)
#define KTMAWG_ERROR_BADLY_FORMED_SELECTOR                  (IVIC_ERROR_BASE + 0x0066)
#define KTMAWG_ERROR_UNKNOWN_PHYSICAL_IDENTIFIER            (IVIC_ERROR_BASE + 0x0067)
#define KTMAWG_ERROR_INVALID_SESSION_HANDLE                 (IVIC_ERROR_BASE + 0x1190)



#define KTMAWG_SUCCESS                                      0
#define KTMAWG_WARN_NSUP_ID_QUERY                           (IVIC_WARN_BASE + 0x0065)
#define KTMAWG_WARN_NSUP_RESET                              (IVIC_WARN_BASE + 0x0066)
#define KTMAWG_WARN_NSUP_SELF_TEST                          (IVIC_WARN_BASE + 0x0067)
#define KTMAWG_WARN_NSUP_ERROR_QUERY                        (IVIC_WARN_BASE + 0x0068)
#define KTMAWG_WARN_NSUP_REV_QUERY                          (IVIC_WARN_BASE + 0x0069)



#define KTMAWG_ERROR_IO_GENERAL                             (IVIC_SPECIFIC_ERROR_BASE + 0x0214)
#define KTMAWG_ERROR_IO_TIMEOUT                             (IVIC_SPECIFIC_ERROR_BASE + 0x0215)
#define KTMAWG_ERROR_CALIBRATION_VERSION                    (IVIC_SPECIFIC_ERROR_BASE + 0x0217)
#define KTMAWG_ERROR_CHECK_ERROR_QUEUE                      (IVIC_SPECIFIC_ERROR_BASE + 0x0218)
#define KTMAWG_ERROR_FILE_TYPE_NOT_RECOGNIZED               (IVIC_SPECIFIC_ERROR_BASE + 0x0219)
#define KTMAWG_ERROR_FIRMWARE_UPDATE_ERROR                  (IVIC_SPECIFIC_ERROR_BASE + 0x021A)
#define KTMAWG_ERROR_FIRMWARE_UPDATE_REQUIRED               (IVIC_SPECIFIC_ERROR_BASE + 0x021B)
#define KTMAWG_ERROR_FPGA_PROGRAMMING_ERROR                 (IVIC_SPECIFIC_ERROR_BASE + 0x021C)
#define KTMAWG_ERROR_HARDWARE_TIMEOUT                       (IVIC_SPECIFIC_ERROR_BASE + 0x021D)
#define KTMAWG_ERROR_HW_RESOURCE_NOT_AVAILABLE              (IVIC_SPECIFIC_ERROR_BASE + 0x021E)
#define KTMAWG_ERROR_INCOMPATIBLE_SOFTWARE_VERSION_ERROR    (IVIC_SPECIFIC_ERROR_BASE + 0x021F)
#define KTMAWG_ERROR_INSTRUMENT_CALIBRATION_DUE             (IVIC_SPECIFIC_ERROR_BASE + 0x0220)
#define KTMAWG_ERROR_INSTRUMENT_CALIBRATION_EXPIRED         (IVIC_SPECIFIC_ERROR_BASE + 0x0221)
#define KTMAWG_ERROR_INSTRUMENT_NOT_CALIBRATED              (IVIC_SPECIFIC_ERROR_BASE + 0x0222)
#define KTMAWG_ERROR_INTERNAL_APPLICATION_ERROR             (IVIC_SPECIFIC_ERROR_BASE + 0x0223)
#define KTMAWG_ERROR_LICENSE_SYSTEM_ERROR                   (IVIC_SPECIFIC_ERROR_BASE + 0x0224)
#define KTMAWG_ERROR_LICENSE_VALIDATION_ERROR               (IVIC_SPECIFIC_ERROR_BASE + 0x0225)
#define KTMAWG_ERROR_MAX_TIME_EXCEEDED                      (IVIC_SPECIFIC_ERROR_BASE + 0x0226)
#define KTMAWG_ERROR_MISSING_CLOCK_ERROR                    (IVIC_SPECIFIC_ERROR_BASE + 0x0227)
#define KTMAWG_ERROR_MODEL_NOT_SUPPORTED                    (IVIC_SPECIFIC_ERROR_BASE + 0x0228)
#define KTMAWG_ERROR_MODULE_CALIBRATION_DUE                 (IVIC_SPECIFIC_ERROR_BASE + 0x0229)
#define KTMAWG_ERROR_MODULE_CALIBRATION_EXPIRED             (IVIC_SPECIFIC_ERROR_BASE + 0x022A)
#define KTMAWG_ERROR_MODULE_NOT_CALIBRATED                  (IVIC_SPECIFIC_ERROR_BASE + 0x022B)
#define KTMAWG_ERROR_MODULE_VALIDATE_FAILED                 (IVIC_SPECIFIC_ERROR_BASE + 0x022C)
#define KTMAWG_ERROR_OPERATION_ABORTED                      (IVIC_SPECIFIC_ERROR_BASE + 0x022D)
#define KTMAWG_ERROR_OPERATION_ERROR                        (IVIC_SPECIFIC_ERROR_BASE + 0x022E)
#define KTMAWG_ERROR_OUT_OF_MEMORY_ERROR                    (IVIC_SPECIFIC_ERROR_BASE + 0x022F)
#define KTMAWG_ERROR_PARAMETER_VALIDATION_ERROR             (IVIC_SPECIFIC_ERROR_BASE + 0x0230)
#define KTMAWG_ERROR_PERSONALITY_NOT_ACTIVE                 (IVIC_SPECIFIC_ERROR_BASE + 0x0231)
#define KTMAWG_ERROR_PERSONALITY_NOT_INSTALLED              (IVIC_SPECIFIC_ERROR_BASE + 0x0232)
#define KTMAWG_ERROR_PERSONALITY_NOT_LICENSED               (IVIC_SPECIFIC_ERROR_BASE + 0x0233)
#define KTMAWG_ERROR_SELFTEST_FAILED                        (IVIC_SPECIFIC_ERROR_BASE + 0x0234)
#define KTMAWG_ERROR_SOFTWARE_TIMEOUT                       (IVIC_SPECIFIC_ERROR_BASE + 0x0235)
#define KTMAWG_ERROR_TEST_FAILED_INCORRECT_VERSION          (IVIC_SPECIFIC_ERROR_BASE + 0x0236)
#define KTMAWG_ERROR_THERMAL_SHUTDOWN                       (IVIC_SPECIFIC_ERROR_BASE + 0x0237)
#define KTMAWG_ERROR_THERMAL_WARNING                        (IVIC_SPECIFIC_ERROR_BASE + 0x0238)
#define KTMAWG_ERROR_UNABLE_TO_INITIALIZE_HARDWARE          (IVIC_SPECIFIC_ERROR_BASE + 0x0239)
#define KTMAWG_ERROR_UNRECOGNIZED_ERROR                     (IVIC_SPECIFIC_ERROR_BASE + 0x023A)
#define KTMAWG_ERROR_UNSUPPORTED_FEATURE                    (IVIC_SPECIFIC_ERROR_BASE + 0x023B)
#define KTMAWG_ERROR_UNSUPPORTED_PROPERTY                   (IVIC_SPECIFIC_ERROR_BASE + 0x023C)
#define KTMAWG_ERROR_VALIDATION_ERROR                       (IVIC_SPECIFIC_ERROR_BASE + 0x023D)
#define KTMAWG_ERROR_VERIFY_OPERATION_ERROR                 (IVIC_SPECIFIC_ERROR_BASE + 0x023E)
#define KTMAWG_ERROR_WAIT_ABORTED                           (IVIC_SPECIFIC_ERROR_BASE + 0x023F)
#define KTMAWG_ERROR_TRIGGER_NOT_SOFTWARE                   (IVIC_CLASS_ERROR_BASE + 0x0001)
#define KTMAWG_ERROR_NO_WFMS_AVAILABLE                      (IVIC_CLASS_ERROR_BASE + 0x0004)
#define KTMAWG_ERROR_WFM_IN_USE                             (IVIC_CLASS_ERROR_BASE + 0x0008)
#define KTMAWG_ERROR_NO_SEQS_AVAILABLE                      (IVIC_CLASS_ERROR_BASE + 0x0009)
#define KTMAWG_ERROR_SEQ_IN_USE                             (IVIC_CLASS_ERROR_BASE + 0x000D)
#define KTMAWG_ERROR_INVALID_WFM_CHANNEL                    (IVIC_CLASS_ERROR_BASE + 0x000E)
#define KTMAWG_ERROR_COMPILATION_ERROR                      (IVIC_SPECIFIC_ERROR_BASE + 0x0240)
#define KTMAWG_ERROR_HARDWARE_STATE_ERROR                   (IVIC_SPECIFIC_ERROR_BASE + 0x0241)
#define KTMAWG_ERROR_INCONSISTENT_MULTI_CHANNEL_PROPERTY    (IVIC_SPECIFIC_ERROR_BASE + 0x0242)
#define KTMAWG_ERROR_INVALID_PARAMETER                      (IVIC_SPECIFIC_ERROR_BASE + 0x0243)
#define KTMAWG_ERROR_MODULE_OUT_OF_MEMORY                   (IVIC_SPECIFIC_ERROR_BASE + 0x0245)
#define KTMAWG_ERROR_SETTINGS_CONFLICT                      (IVIC_SPECIFIC_ERROR_BASE + 0x0246)



#define KTMAWG_WARN_VALIDATION_FAILED                       (IVIC_SPECIFIC_WARN_BASE + 0x012D)


/**************************************************************************** 
 *---------------------------- End Include File ----------------------------* 
 ****************************************************************************/
#if defined(__cplusplus) || defined(__cplusplus__)
}
#endif
#endif // __KTMAWG_HEADER
