/******************************************************************************
 *
 * Copyright Keysight Technologies 2012-2017
 *
 *****************************************************************************/

#ifndef __AGMD2_HEADER
#define __AGMD2_HEADER

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

#define AGMD2_ATTR_SPECIFIC_DRIVER_DESCRIPTION              (IVI_INHERENT_ATTR_BASE + 514L)  /* ViString, read-only */
#define AGMD2_ATTR_SPECIFIC_DRIVER_PREFIX                   (IVI_INHERENT_ATTR_BASE + 302L)  /* ViString, read-only */
#define AGMD2_ATTR_SPECIFIC_DRIVER_VENDOR                   (IVI_INHERENT_ATTR_BASE + 513L)  /* ViString, read-only */
#define AGMD2_ATTR_SPECIFIC_DRIVER_REVISION                 (IVI_INHERENT_ATTR_BASE + 551L)  /* ViString, read-only */
#define AGMD2_ATTR_SPECIFIC_DRIVER_CLASS_SPEC_MAJOR_VERSION (IVI_INHERENT_ATTR_BASE + 515L)  /* ViInt32, read-only */
#define AGMD2_ATTR_SPECIFIC_DRIVER_CLASS_SPEC_MINOR_VERSION (IVI_INHERENT_ATTR_BASE + 516L)  /* ViInt32, read-only */

/*- User Options */

#define AGMD2_ATTR_RANGE_CHECK                              (IVI_INHERENT_ATTR_BASE + 2L)  /* ViBoolean, read-write */
#define AGMD2_ATTR_QUERY_INSTRUMENT_STATUS                  (IVI_INHERENT_ATTR_BASE + 3L)  /* ViBoolean, read-write */
#define AGMD2_ATTR_CACHE                                    (IVI_INHERENT_ATTR_BASE + 4L)  /* ViBoolean, read-write */
#define AGMD2_ATTR_SIMULATE                                 (IVI_INHERENT_ATTR_BASE + 5L)  /* ViBoolean, read-write */
#define AGMD2_ATTR_RECORD_COERCIONS                         (IVI_INHERENT_ATTR_BASE + 6L)  /* ViBoolean, read-write */
#define AGMD2_ATTR_INTERCHANGE_CHECK                        (IVI_INHERENT_ATTR_BASE + 21L)  /* ViBoolean, read-write */

/*- Advanced Session Information */

#define AGMD2_ATTR_LOGICAL_NAME                             (IVI_INHERENT_ATTR_BASE + 305L)  /* ViString, read-only */
#define AGMD2_ATTR_IO_RESOURCE_DESCRIPTOR                   (IVI_INHERENT_ATTR_BASE + 304L)  /* ViString, read-only */
#define AGMD2_ATTR_DRIVER_SETUP                             (IVI_INHERENT_ATTR_BASE + 7L)  /* ViString, read-only */

/*- Driver Capabilities */

#define AGMD2_ATTR_GROUP_CAPABILITIES                       (IVI_INHERENT_ATTR_BASE + 401L)  /* ViString, read-only */
#define AGMD2_ATTR_SUPPORTED_INSTRUMENT_MODELS              (IVI_INHERENT_ATTR_BASE + 327L)  /* ViString, read-only */

/*- Instrument Identification */

#define AGMD2_ATTR_INSTRUMENT_FIRMWARE_REVISION             (IVI_INHERENT_ATTR_BASE + 510L)  /* ViString, read-only */
#define AGMD2_ATTR_INSTRUMENT_MANUFACTURER                  (IVI_INHERENT_ATTR_BASE + 511L)  /* ViString, read-only */
#define AGMD2_ATTR_INSTRUMENT_MODEL                         (IVI_INHERENT_ATTR_BASE + 512L)  /* ViString, read-only */


/*===== Instrument-Specific Attributes =====================================*/

/*- Temperature */

#define AGMD2_ATTR_CHANNEL_TEMPERATURE                      (IVI_CLASS_ATTR_BASE + 300L)  /* ViReal64, read-only */
#define AGMD2_ATTR_TEMPERATURE_UNITS                        (IVI_CLASS_ATTR_BASE + 101L)  /* ViInt32, read-write */
#define AGMD2_ATTR_BOARD_TEMPERATURE                        (IVI_CLASS_ATTR_BASE + 100L)  /* ViReal64, read-only */

/*- Waveform Acquisition */

#define AGMD2_ATTR_TIME_INTERLEAVED_CHANNEL_LIST_AUTO       (IVI_CLASS_ATTR_BASE + 401L)  /* ViBoolean, read-write */
#define AGMD2_ATTR_MAX_SAMPLES_PER_CHANNEL                  (IVI_CLASS_ATTR_BASE + 10L)  /* ViInt64, read-only */
#define AGMD2_ATTR_NUM_ACQUIRED_RECORDS                     (IVI_CLASS_ATTR_BASE + 12L)  /* ViInt64, read-only */
#define AGMD2_ATTR_SAMPLE_RATE                              (IVI_CLASS_ATTR_BASE + 15L)  /* ViReal64, read-write */
#define AGMD2_ATTR_MIN_RECORD_SIZE                          (IVI_CLASS_ATTR_BASE + 11L)  /* ViInt64, read-only */
#define AGMD2_ATTR_RECORD_SIZE                              (IVI_CLASS_ATTR_BASE + 14L)  /* ViInt64, read-write */
#define AGMD2_ATTR_NUM_RECORDS_TO_ACQUIRE                   (IVI_CLASS_ATTR_BASE + 13L)  /* ViInt64, read-write */
#define AGMD2_ATTR_IS_IDLE                                  (IVI_CLASS_ATTR_BASE + 5L)  /* ViInt32, read-only */
#define AGMD2_ATTR_IS_MEASURING                             (IVI_CLASS_ATTR_BASE + 6L)  /* ViInt32, read-only */
#define AGMD2_ATTR_IS_WAITING_FOR_ARM                       (IVI_CLASS_ATTR_BASE + 7L)  /* ViInt32, read-only */
#define AGMD2_ATTR_IS_WAITING_FOR_TRIGGER                   (IVI_CLASS_ATTR_BASE + 8L)  /* ViInt32, read-only */
#define AGMD2_ATTR_MAX_FIRST_VALID_POINT_VAL                (IVI_CLASS_ATTR_BASE + 9L)  /* ViInt64, read-write */

/*- Channel */

#define AGMD2_ATTR_CHANNEL_COUNT                            (IVI_INHERENT_ATTR_BASE + 203L)  /* ViInt32, read-only */
#define AGMD2_ATTR_VERTICAL_COUPLING                        (IVI_CLASS_ATTR_BASE + 24L)  /* ViInt32, read-write */
#define AGMD2_ATTR_INPUT_IMPEDANCE                          (IVI_CLASS_ATTR_BASE + 4L)  /* ViReal64, read-write */
#define AGMD2_ATTR_VERTICAL_RANGE                           (IVI_CLASS_ATTR_BASE + 26L)  /* ViReal64, read-write */
#define AGMD2_ATTR_VERTICAL_OFFSET                          (IVI_CLASS_ATTR_BASE + 25L)  /* ViReal64, read-write */
#define AGMD2_ATTR_CHANNEL_ENABLED                          (IVI_CLASS_ATTR_BASE + 2L)  /* ViBoolean, read-write */
#define AGMD2_ATTR_INPUT_CONNECTOR_SELECTION                (IVI_CLASS_ATTR_BASE + 3L)  /* ViInt32, read-write */
#define AGMD2_ATTR_TIME_INTERLEAVED_CHANNEL_LIST            (IVI_CLASS_ATTR_BASE + 400L)  /* ViString, read-write */

/*- Filter */

#define AGMD2_ATTR_INPUT_FILTER_MAX_FREQUENCY               (IVI_CLASS_ATTR_BASE + 201L)  /* ViReal64, read-write */
#define AGMD2_ATTR_INPUT_FILTER_MIN_FREQUENCY               (IVI_CLASS_ATTR_BASE + 202L)  /* ViReal64, read-write */
#define AGMD2_ATTR_INPUT_FILTER_BYPASS                      (IVI_CLASS_ATTR_BASE + 200L)  /* ViBoolean, read-write */

/*- Reference Oscillator */

#define AGMD2_ATTR_REFERENCE_OSCILLATOR_SOURCE              (IVI_CLASS_ATTR_BASE + 602L)  /* ViInt32, read-write */
#define AGMD2_ATTR_REFERENCE_OSCILLATOR_EXTERNAL_FREQUENCY  (IVI_CLASS_ATTR_BASE + 600L)  /* ViReal64, read-write */
#define AGMD2_ATTR_REFERENCE_OSCILLATOR_OUTPUT_ENABLED      (IVI_CLASS_ATTR_BASE + 601L)  /* ViBoolean, read-write */

/*- Sample Clock */

#define AGMD2_ATTR_SAMPLE_CLOCK_SOURCE                      (IVI_CLASS_ATTR_BASE + 703L)  /* ViInt32, read-write */
#define AGMD2_ATTR_SAMPLE_CLOCK_EXTERNAL_FREQUENCY          (IVI_CLASS_ATTR_BASE + 701L)  /* ViReal64, read-write */
#define AGMD2_ATTR_SAMPLE_CLOCK_OUTPUT_ENABLED              (IVI_CLASS_ATTR_BASE + 702L)  /* ViBoolean, read-write */
#define AGMD2_ATTR_SAMPLE_CLOCK_EXTERNAL_DIVIDER            (IVI_CLASS_ATTR_BASE + 700L)  /* ViReal64, read-write */

/*- Trigger */

#define AGMD2_ATTR_TRIGGER_COUPLING                         (IVI_CLASS_ATTR_BASE + 16L)  /* ViInt32, read-write */
#define AGMD2_ATTR_TRIGGER_HYSTERESIS                       (IVI_CLASS_ATTR_BASE + 18L)  /* ViReal64, read-write */
#define AGMD2_ATTR_TRIGGER_LEVEL                            (IVI_CLASS_ATTR_BASE + 19L)  /* ViReal64, read-write */
#define AGMD2_ATTR_TRIGGER_TYPE                             (IVI_CLASS_ATTR_BASE + 23L)  /* ViInt32, read-write */
#define AGMD2_ATTR_ACTIVE_TRIGGER_SOURCE                    (IVI_CLASS_ATTR_BASE + 1L)  /* ViString, read-write */
#define AGMD2_ATTR_PRETRIGGER_SAMPLES                       (IVI_CLASS_ATTR_BASE + 1900L)  /* ViInt64, read-write */
#define AGMD2_ATTR_TRIGGER_HOLDOFF                          (IVI_CLASS_ATTR_BASE + 2000L)  /* ViReal64, read-write */
#define AGMD2_ATTR_TRIGGER_DELAY                            (IVI_CLASS_ATTR_BASE + 17L)  /* ViReal64, read-write */
#define AGMD2_ATTR_TRIGGER_OUTPUT_ENABLED                   (IVI_CLASS_ATTR_BASE + 20L)  /* ViBoolean, read-write */
#define AGMD2_ATTR_TRIGGER_SOURCE_COUNT                     (IVI_CLASS_ATTR_BASE + 22L)  /* ViInt32, read-only */

/*- Edge Triggering */

#define AGMD2_ATTR_TRIGGER_SLOPE                            (IVI_CLASS_ATTR_BASE + 21L)  /* ViInt32, read-write */

/*- Glitch Triggering */

#define AGMD2_ATTR_GLITCH_TRIGGER_WIDTH                     (IVI_CLASS_ATTR_BASE + 2102L)  /* ViReal64, read-write */
#define AGMD2_ATTR_GLITCH_TRIGGER_CONDITION                 (IVI_CLASS_ATTR_BASE + 2100L)  /* ViInt32, read-write */
#define AGMD2_ATTR_GLITCH_TRIGGER_POLARITY                  (IVI_CLASS_ATTR_BASE + 2101L)  /* ViInt32, read-write */

/*- Runt Triggering */

#define AGMD2_ATTR_RUNT_TRIGGER_POLARITY                    (IVI_CLASS_ATTR_BASE + 2202L)  /* ViInt32, read-write */
#define AGMD2_ATTR_RUNT_TRIGGER_HIGH_THRESHOLD              (IVI_CLASS_ATTR_BASE + 2200L)  /* ViReal64, read-write */
#define AGMD2_ATTR_RUNT_TRIGGER_LOW_THRESHOLD               (IVI_CLASS_ATTR_BASE + 2201L)  /* ViReal64, read-write */

/*- TV Triggering */

#define AGMD2_ATTR_TV_TRIGGER_POLARITY                      (IVI_CLASS_ATTR_BASE + 2302L)  /* ViInt32, read-write */
#define AGMD2_ATTR_TV_TRIGGER_EVENT                         (IVI_CLASS_ATTR_BASE + 2300L)  /* ViInt32, read-write */
#define AGMD2_ATTR_TV_TRIGGER_LINE_NUMBER                   (IVI_CLASS_ATTR_BASE + 2301L)  /* ViInt32, read-write */
#define AGMD2_ATTR_TV_TRIGGER_SIGNAL_FORMAT                 (IVI_CLASS_ATTR_BASE + 2303L)  /* ViInt32, read-write */

/*- Width Triggering */

#define AGMD2_ATTR_WIDTH_TRIGGER_POLARITY                   (IVI_CLASS_ATTR_BASE + 2403L)  /* ViInt32, read-write */
#define AGMD2_ATTR_WIDTH_TRIGGER_CONDITION                  (IVI_CLASS_ATTR_BASE + 2400L)  /* ViInt32, read-write */
#define AGMD2_ATTR_WIDTH_TRIGGER_HIGH_THRESHOLD             (IVI_CLASS_ATTR_BASE + 2401L)  /* ViReal64, read-write */
#define AGMD2_ATTR_WIDTH_TRIGGER_LOW_THRESHOLD              (IVI_CLASS_ATTR_BASE + 2402L)  /* ViReal64, read-write */

/*- Window Triggering */

#define AGMD2_ATTR_WINDOW_TRIGGER_CONDITION                 (IVI_CLASS_ATTR_BASE + 2500L)  /* ViInt32, read-write */
#define AGMD2_ATTR_WINDOW_TRIGGER_HIGH_THRESHOLD            (IVI_CLASS_ATTR_BASE + 2501L)  /* ViReal64, read-write */
#define AGMD2_ATTR_WINDOW_TRIGGER_LOW_THRESHOLD             (IVI_CLASS_ATTR_BASE + 2502L)  /* ViReal64, read-write */

/*- Multi Trigger */

#define AGMD2_ATTR_TRIGGER_SOURCE_LIST                      (IVI_CLASS_ATTR_BASE + 1800L)  /* ViString, read-write */
#define AGMD2_ATTR_TRIGGER_SOURCE_OPERATOR                  (IVI_CLASS_ATTR_BASE + 1801L)  /* ViInt32, read-write */

/*- Private */

#define AGMD2_ATTR_PRIVATE_ACCESS_PASSWORD                  (IVI_SPECIFIC_ATTR_BASE + 66L)  /* ViString, write-only */

/*- PrivateFirmware */

#define AGMD2_ATTR_PRIVATE_FIRMWARE_COUNT                   (IVI_SPECIFIC_ATTR_BASE + 2L)  /* ViInt32, read-only */

/*- PrivateStore */

#define AGMD2_ATTR_PRIVATE_STORE_COUNT                      (IVI_SPECIFIC_ATTR_BASE + 5L)  /* ViInt32, read-only */
#define AGMD2_ATTR_PRIVATE_STORE_BAR_CODE                   (IVI_SPECIFIC_ATTR_BASE + 60L)  /* ViString, read-write */
#define AGMD2_ATTR_PRIVATE_STORE_PART_NUMBER                (IVI_SPECIFIC_ATTR_BASE + 61L)  /* ViString, read-write */
#define AGMD2_ATTR_PRIVATE_STORE_PART_NUMBER_REVISION       (IVI_SPECIFIC_ATTR_BASE + 62L)  /* ViString, read-write */
#define AGMD2_ATTR_PRIVATE_STORE_SERIAL_NUMBER              (IVI_SPECIFIC_ATTR_BASE + 63L)  /* ViString, read-write */
#define AGMD2_ATTR_PRIVATE_STORE_PRODUCTION_DATE            (IVI_SPECIFIC_ATTR_BASE + 64L)  /* ViString, read-write */
#define AGMD2_ATTR_PRIVATE_STORE_TEST_DATE                  (IVI_SPECIFIC_ATTR_BASE + 65L)  /* ViString, read-write */

/*- EepromModuleGeneration */

#define AGMD2_ATTR_EEPROM_MODULE_GENERATION_SERIAL_NUMBER   (IVI_SPECIFIC_ATTR_BASE + 58L)  /* ViString, read-write */
#define AGMD2_ATTR_EEPROM_MODULE_GENERATION_OPTIONS         (IVI_SPECIFIC_ATTR_BASE + 59L)  /* ViString, read-write */

/*- PrivateCalibration */

#define AGMD2_ATTR_PRIVATE_CALIBRATION_USER_SIGNAL          (IVI_SPECIFIC_ATTR_BASE + 7L)  /* ViString, read-write */

/*- PrivateDataLock */

#define AGMD2_ATTR_PRIVATE_DATA_LOCK                        (IVI_SPECIFIC_ATTR_BASE + 114L)  /* ViInt32, read-only */

/*- LogicDevice */

#define AGMD2_ATTR_LOGIC_DEVICE_COUNT                               (IVI_SPECIFIC_ATTR_BASE + 1L)  /* ViInt32, read-only */
#define AGMD2_ATTR_LOGIC_DEVICE_FIRMWARE_STORE_COUNT                (IVI_SPECIFIC_ATTR_BASE + 29L)  /* ViInt32, read-only */
#define AGMD2_ATTR_LOGIC_DEVICE_SAMPLES_UNSIGNED                    (IVI_SPECIFIC_ATTR_BASE + 30L)  /* ViBoolean, read-write */
#define AGMD2_ATTR_LOGIC_DEVICE_STREAM_MODE                         (IVI_SPECIFIC_ATTR_BASE + 31L)  /* ViInt32, read-write */
#define AGMD2_ATTR_LOGIC_DEVICE_STREAMS_COUNT                       (IVI_SPECIFIC_ATTR_BASE + 32L)  /* ViInt32, read-only */
#define AGMD2_ATTR_LOGIC_DEVICE_LOAD_FROM_STORE_ECC_WARNING_OCCURED (IVI_SPECIFIC_ATTR_BASE + 117L)  /* ViBoolean, read-only */

/*- LogicDeviceIFDL */

#define AGMD2_ATTR_LOGIC_DEVICE_IFDL_ENABLED                (IVI_SPECIFIC_ATTR_BASE + 33L)  /* ViBoolean, read-write */
#define AGMD2_ATTR_LOGIC_DEVICE_IFDL_IS_ACTIVE              (IVI_SPECIFIC_ATTR_BASE + 34L)  /* ViBoolean, read-only */
#define AGMD2_ATTR_LOGIC_DEVICE_IFDL_COUNT                  (IVI_SPECIFIC_ATTR_BASE + 40L)  /* ViInt32, read-only */

/*- LogicDeviceMemoryBank */

#define AGMD2_ATTR_LOGIC_DEVICE_MEMORY_BANK_ACCESS_CONTROL    (IVI_SPECIFIC_ATTR_BASE + 36L)  /* ViInt32, read-write */
#define AGMD2_ATTR_LOGIC_DEVICE_MEMORY_BANK_ACCESS_MODE       (IVI_SPECIFIC_ATTR_BASE + 37L)  /* ViInt32, read-write */
#define AGMD2_ATTR_LOGIC_DEVICE_MEMORY_BANK_FIFO_MODE_ENABLED (IVI_SPECIFIC_ATTR_BASE + 38L)  /* ViBoolean, read-write */
#define AGMD2_ATTR_LOGIC_DEVICE_MEMORY_BANK_COUNT             (IVI_SPECIFIC_ATTR_BASE + 41L)  /* ViInt32, read-only */

/*- Output */

#define AGMD2_ATTR_TRIGGER_OUTPUT_OFFSET                    (IVI_SPECIFIC_ATTR_BASE + 4L)  /* ViReal64, read-write */
#define AGMD2_ATTR_TRIGGER_OUTPUT_SOURCE                    (IVI_SPECIFIC_ATTR_BASE + 26L)  /* ViString, read-write */

/*- Magnitude */

#define AGMD2_ATTR_TRIGGER_MAGNITUDE_DWELL_TIME_SAMPLES     (IVI_SPECIFIC_ATTR_BASE + 27L)  /* ViInt32, read-write */
#define AGMD2_ATTR_TRIGGER_MAGNITUDE_SLOPE                  (IVI_SPECIFIC_ATTR_BASE + 28L)  /* ViInt32, read-write */

/*- SelfTrigger */

#define AGMD2_ATTR_SELF_TRIGGER_MODE                        (IVI_SPECIFIC_ATTR_BASE + 84L)  /* ViInt32, read-write */

/*- SquareWave */

#define AGMD2_ATTR_SELF_TRIGGER_SQUARE_WAVE_DUTY_CYCLE      (IVI_SPECIFIC_ATTR_BASE + 81L)  /* ViReal64, read-write */
#define AGMD2_ATTR_SELF_TRIGGER_SQUARE_WAVE_FREQUENCY       (IVI_SPECIFIC_ATTR_BASE + 82L)  /* ViReal64, read-write */
#define AGMD2_ATTR_SELF_TRIGGER_SQUARE_WAVE_SLOPE           (IVI_SPECIFIC_ATTR_BASE + 83L)  /* ViInt32, read-write */

/*- ControlIO */

#define AGMD2_ATTR_CONTROL_IO_SIGNAL                        (IVI_SPECIFIC_ATTR_BASE + 6L)  /* ViString, read-write */
#define AGMD2_ATTR_CONTROL_IO_COUNT                         (IVI_SPECIFIC_ATTR_BASE + 9L)  /* ViInt32, read-only */
#define AGMD2_ATTR_CONTROL_IO_AVAILABLE_SIGNALS             (IVI_SPECIFIC_ATTR_BASE + 68L)  /* ViString, read-only */

/*- Acquisition */

#define AGMD2_ATTR_ACQUISITION_DOWNCONVERSION_DATA_SCALING_ENABLED (IVI_SPECIFIC_ATTR_BASE + 10L)  /* ViBoolean, read-write */
#define AGMD2_ATTR_ACQUISITION_MODE                                (IVI_SPECIFIC_ATTR_BASE + 11L)  /* ViInt32, read-write */
#define AGMD2_ATTR_ACQUISITION_NUMBER_OF_AVERAGES                  (IVI_SPECIFIC_ATTR_BASE + 69L)  /* ViInt32, read-write */
#define AGMD2_ATTR_ERROR_ON_OVERRANGE_ENABLED                      (IVI_SPECIFIC_ATTR_BASE + 115L)  /* ViBoolean, read-write */

/*- UserControl */

#define AGMD2_ATTR_USER_CONTROL_COUNTERS_MODE                  (IVI_SPECIFIC_ATTR_BASE + 49L)  /* ViInt32, read-write */
#define AGMD2_ATTR_USER_CONTROL_INTER_SEGMENT_DELAY_MODE       (IVI_SPECIFIC_ATTR_BASE + 50L)  /* ViInt32, read-write */
#define AGMD2_ATTR_USER_CONTROL_INTER_SEGMENT_DELAY_VALUE      (IVI_SPECIFIC_ATTR_BASE + 51L)  /* ViInt32, read-write */
#define AGMD2_ATTR_USER_CONTROL_POST_TRIGGER                   (IVI_SPECIFIC_ATTR_BASE + 52L)  /* ViInt32, read-write */
#define AGMD2_ATTR_USER_CONTROL_PRE_TRIGGER                    (IVI_SPECIFIC_ATTR_BASE + 53L)  /* ViInt32, read-write */
#define AGMD2_ATTR_USER_CONTROL_TRIGGER_ENABLE_SOURCE          (IVI_SPECIFIC_ATTR_BASE + 54L)  /* ViInt32, read-write */
#define AGMD2_ATTR_USER_CONTROL_TRIGGER_FACTOR                 (IVI_SPECIFIC_ATTR_BASE + 55L)  /* ViInt32, read-write */
#define AGMD2_ATTR_USER_CONTROL_TRIGGER_SELECTION              (IVI_SPECIFIC_ATTR_BASE + 56L)  /* ViInt32, read-write */
#define AGMD2_ATTR_USER_CONTROL_START_ON_TRIGGER_ENABLED       (IVI_SPECIFIC_ATTR_BASE + 57L)  /* ViBoolean, read-write */
#define AGMD2_ATTR_IO_FIXED_LATENCY_ENABLED                    (IVI_SPECIFIC_ATTR_BASE + 88L)  /* ViBoolean, read-write */
#define AGMD2_ATTR_USER_CONTROL_CONNECTOR_TO_USER_CORE_LATENCY (IVI_SPECIFIC_ATTR_BASE + 119L)  /* ViReal64, read-only */

/*- TSR */

#define AGMD2_ATTR_TSR_ENABLED                              (IVI_SPECIFIC_ATTR_BASE + 85L)  /* ViBoolean, read-write */
#define AGMD2_ATTR_TSR_IS_ACQUISITION_COMPLETE              (IVI_SPECIFIC_ATTR_BASE + 86L)  /* ViBoolean, read-only */
#define AGMD2_ATTR_TSR_MEMORY_OVERFLOW_OCCURRED             (IVI_SPECIFIC_ATTR_BASE + 87L)  /* ViBoolean, read-only */

/*- CSR */

#define AGMD2_ATTR_CSR_ENABLED                              (IVI_SPECIFIC_ATTR_BASE + 90L)  /* ViBoolean, read-write */
#define AGMD2_ATTR_CSR_STOP_MODE                            (IVI_SPECIFIC_ATTR_BASE + 91L)  /* ViInt32, read-write */

/*- Streaming */

#define AGMD2_ATTR_STREAMING_MODE                           (IVI_SPECIFIC_ATTR_BASE + 120L)  /* ViInt32, read-write */

/*- InstrumentInfo */

#define AGMD2_ATTR_INSTRUMENT_INFO_SERIAL_NUMBER_STRING     (IVI_SPECIFIC_ATTR_BASE + 8L)  /* ViString, read-only */
#define AGMD2_ATTR_INSTRUMENT_INFO_IO_VERSION               (IVI_SPECIFIC_ATTR_BASE + 19L)  /* ViString, read-only */
#define AGMD2_ATTR_INSTRUMENT_INFO_CHASSIS_NUMBER           (IVI_SPECIFIC_ATTR_BASE + 20L)  /* ViInt32, read-only */
#define AGMD2_ATTR_INSTRUMENT_INFO_NBR_ADC_BITS             (IVI_SPECIFIC_ATTR_BASE + 22L)  /* ViInt32, read-only */
#define AGMD2_ATTR_INSTRUMENT_INFO_OPTIONS                  (IVI_SPECIFIC_ATTR_BASE + 23L)  /* ViString, read-only */
#define AGMD2_ATTR_INSTRUMENT_INFO_SLOT_NUMBER              (IVI_SPECIFIC_ATTR_BASE + 106L)  /* ViInt32, read-only */

/*- MonitoringValue */

#define AGMD2_ATTR_MONITORING_VALUE_CURRENT_VALUE           (IVI_SPECIFIC_ATTR_BASE + 44L)  /* ViReal64, read-only */
#define AGMD2_ATTR_MONITORING_VALUE_UNIT                    (IVI_SPECIFIC_ATTR_BASE + 45L)  /* ViString, read-only */
#define AGMD2_ATTR_MONITORING_VALUE_LIMIT_HIGH              (IVI_SPECIFIC_ATTR_BASE + 46L)  /* ViReal64, read-only */
#define AGMD2_ATTR_MONITORING_VALUE_LIMIT_LOW               (IVI_SPECIFIC_ATTR_BASE + 47L)  /* ViReal64, read-only */
#define AGMD2_ATTR_MONITORING_VALUE_COUNT                   (IVI_SPECIFIC_ATTR_BASE + 48L)  /* ViInt32, read-only */

/*- Calibration */

#define AGMD2_ATTR_CALIBRATION_IS_REQUIRED                  (IVI_SPECIFIC_ATTR_BASE + 67L)  /* ViBoolean, read-only */
#define AGMD2_ATTR_CALIBRATION_EQUALIZATION                 (IVI_SPECIFIC_ATTR_BASE + 116L)  /* ViInt32, read-write */
#define AGMD2_ATTR_CALIBRATION_FAILURE_LIST                 (IVI_SPECIFIC_ATTR_BASE + 118L)  /* ViString, read-only */
#define AGMD2_ATTR_CALIBRATION_TARGET_VOLTAGE_ENABLED       (IVI_SPECIFIC_ATTR_BASE + 122L)  /* ViBoolean, read-write */

/*- DelayControl */

#define AGMD2_ATTR_DELAY_CONTROL_MAX                        (IVI_SPECIFIC_ATTR_BASE + 12L)  /* ViInt32, read-only */
#define AGMD2_ATTR_DELAY_CONTROL_MIN                        (IVI_SPECIFIC_ATTR_BASE + 13L)  /* ViInt32, read-only */
#define AGMD2_ATTR_DELAY_CONTROL_VALUE                      (IVI_SPECIFIC_ATTR_BASE + 14L)  /* ViInt32, read-write */
#define AGMD2_ATTR_DELAY_CONTROL_RANGE                      (IVI_SPECIFIC_ATTR_BASE + 15L)  /* ViInt32, read-write */
#define AGMD2_ATTR_DELAY_CONTROL_ENABLED                    (IVI_SPECIFIC_ATTR_BASE + 17L)  /* ViBoolean, read-write */
#define AGMD2_ATTR_DELAY_CONTROL_COUNT                      (IVI_SPECIFIC_ATTR_BASE + 42L)  /* ViInt32, read-only */

/*- Channel */

#define AGMD2_ATTR_CHANNEL_CONNECTOR_NAME                   (IVI_SPECIFIC_ATTR_BASE + 18L)  /* ViString, read-only */
#define AGMD2_ATTR_CHANNEL_DATA_INVERSION_ENABLED           (IVI_SPECIFIC_ATTR_BASE + 70L)  /* ViBoolean, read-write */
#define AGMD2_ATTR_CHANNEL_CALIBRATION_TARGET_VOLTAGE       (IVI_SPECIFIC_ATTR_BASE + 121L)  /* ViReal64, read-write */

/*- NSA */

#define AGMD2_ATTR_NSA_ENABLED                              (IVI_SPECIFIC_ATTR_BASE + 71L)  /* ViBoolean, read-write */
#define AGMD2_ATTR_NSA_NOISE_BASE                           (IVI_SPECIFIC_ATTR_BASE + 72L)  /* ViInt32, read-write */
#define AGMD2_ATTR_NSA_THRESHOLD                            (IVI_SPECIFIC_ATTR_BASE + 73L)  /* ViInt32, read-write */

/*- BaselineCorrection */

#define AGMD2_ATTR_BASELINE_CORRECTION_MODE                 (IVI_SPECIFIC_ATTR_BASE + 77L)  /* ViInt32, read-write */
#define AGMD2_ATTR_BASELINE_CORRECTION_THRESHOLD_HIGH       (IVI_SPECIFIC_ATTR_BASE + 78L)  /* ViInt32, read-write */
#define AGMD2_ATTR_BASELINE_CORRECTION_THRESHOLD_LOW        (IVI_SPECIFIC_ATTR_BASE + 79L)  /* ViInt32, read-write */
#define AGMD2_ATTR_BASELINE_CORRECTION_DIGITAL_OFFSET       (IVI_SPECIFIC_ATTR_BASE + 80L)  /* ViInt32, read-write */

/*- PeakDetection */

#define AGMD2_ATTR_PEAK_DETECTION_RISING_DELTA                   (IVI_SPECIFIC_ATTR_BASE + 74L)  /* ViInt32, read-write */
#define AGMD2_ATTR_PEAK_DETECTION_FALLING_DELTA                  (IVI_SPECIFIC_ATTR_BASE + 75L)  /* ViInt32, read-write */
#define AGMD2_ATTR_PEAK_DETECTION_AMPLITUDE_ACCUMULATION_ENABLED (IVI_SPECIFIC_ATTR_BASE + 76L)  /* ViBoolean, read-write */

/*- ModuleSynchronization */

#define AGMD2_ATTR_MODULE_SYNCHRONIZATION_HANDLE               (IVI_SPECIFIC_ATTR_BASE + 24L)  /* ViInt32, read-only */
#define AGMD2_ATTR_MODULE_SYNCHRONIZATION_MASTER_MODULE_HANDLE (IVI_SPECIFIC_ATTR_BASE + 25L)  /* ViInt32, read-only */

/*- Stream */

#define AGMD2_ATTR_STREAM_COUNT                             (IVI_SPECIFIC_ATTR_BASE + 89L)  /* ViInt32, read-only */
#define AGMD2_ATTR_STREAM_TYPE                              (IVI_SPECIFIC_ATTR_BASE + 92L)  /* ViInt32, read-only */
#define AGMD2_ATTR_STREAM_ENABLED                           (IVI_SPECIFIC_ATTR_BASE + 93L)  /* ViBoolean, read-write */
#define AGMD2_ATTR_STREAM_GRANULARITY_IN_BYTES              (IVI_SPECIFIC_ATTR_BASE + 94L)  /* ViInt64, read-only */
#define AGMD2_ATTR_STREAM_MAX_SIZE_IN_BYTES                 (IVI_SPECIFIC_ATTR_BASE + 95L)  /* ViInt64, read-only */

/*- Markers */

#define AGMD2_ATTR_STREAM_MARKERS_BITS_PER_MARKER           (IVI_SPECIFIC_ATTR_BASE + 97L)  /* ViInt32, read-only */
#define AGMD2_ATTR_STREAM_MARKERS_FRACTIONAL_BITS           (IVI_SPECIFIC_ATTR_BASE + 98L)  /* ViInt32, read-only */

/*- MinMax */

#define AGMD2_ATTR_STREAM_MINMAX_FRAME_SIZE                 (IVI_SPECIFIC_ATTR_BASE + 104L)  /* ViInt64, read-write */

/*- Samples */

#define AGMD2_ATTR_STREAM_SAMPLES_DATA_EMULATION_ENABLED    (IVI_SPECIFIC_ATTR_BASE + 99L)  /* ViBoolean, read-write */
#define AGMD2_ATTR_STREAM_SAMPLES_DATA_EMULATION_RATE       (IVI_SPECIFIC_ATTR_BASE + 100L)  /* ViReal64, read-write */
#define AGMD2_ATTR_STREAM_SAMPLES_DATA_TRUNCATION_ENABLED   (IVI_SPECIFIC_ATTR_BASE + 101L)  /* ViBoolean, read-write */
#define AGMD2_ATTR_STREAM_SAMPLES_DATA_TRUNCATION_BIT_COUNT (IVI_SPECIFIC_ATTR_BASE + 102L)  /* ViInt32, read-write */
#define AGMD2_ATTR_STREAM_SAMPLES_DATA_TRUNCATION_KEEP_MSB  (IVI_SPECIFIC_ATTR_BASE + 103L)  /* ViBoolean, read-write */
#define AGMD2_ATTR_STREAM_SAMPLES_BITS_PER_SAMPLE           (IVI_SPECIFIC_ATTR_BASE + 105L)  /* ViInt32, read-only */

/*- DDCCore */

#define AGMD2_ATTR_DDCCORE_COUNT                            (IVI_SPECIFIC_ATTR_BASE + 107L)  /* ViInt32, read-only */
#define AGMD2_ATTR_DDCCORE_DECIMATION_NUMERATOR             (IVI_SPECIFIC_ATTR_BASE + 108L)  /* ViInt64, read-write */
#define AGMD2_ATTR_DDCCORE_DECIMATION_DENOMINATOR           (IVI_SPECIFIC_ATTR_BASE + 109L)  /* ViInt64, read-write */
#define AGMD2_ATTR_DDCCORE_DATA_SOURCE                      (IVI_SPECIFIC_ATTR_BASE + 110L)  /* ViString, read-write */
#define AGMD2_ATTR_DDCCORE_CENTER_FREQUENCY                 (IVI_SPECIFIC_ATTR_BASE + 111L)  /* ViReal64, read-write */
#define AGMD2_ATTR_DDCCORE_LO_INITIAL_PHASE                 (IVI_SPECIFIC_ATTR_BASE + 112L)  /* ViReal64, read-write */


/****************************************************************************
 *------------------------ Attribute Value Defines -------------------------*
 ****************************************************************************/

/*- Defined values for
	attribute AGMD2_ATTR_VERTICAL_COUPLING
	parameter Coupling in function AgMD2_ConfigureChannel */

#define AGMD2_VAL_VERTICAL_COUPLING_AC                      0
#define AGMD2_VAL_VERTICAL_COUPLING_DC                      1
#define AGMD2_VAL_VERTICAL_COUPLING_GND                     2

/*- Defined values for
	attribute AGMD2_ATTR_TRIGGER_TYPE */

#define AGMD2_VAL_EDGE_TRIGGER                              1
#define AGMD2_VAL_WIDTH_TRIGGER                             2
#define AGMD2_VAL_RUNT_TRIGGER                              3
#define AGMD2_VAL_GLITCH_TRIGGER                            4
#define AGMD2_VAL_TV_TRIGGER                                5
#define AGMD2_VAL_WINDOW_TRIGGER                            6

/*- Defined values for
	attribute AGMD2_ATTR_TEMPERATURE_UNITS
	parameter Units in function AgMD2_ConfigureTemperatureUnits */

#define AGMD2_VAL_CELSIUS                                   0
#define AGMD2_VAL_FAHRENHEIT                                1
#define AGMD2_VAL_KELVIN                                    2

/*- Defined values for
	attribute AGMD2_ATTR_REFERENCE_OSCILLATOR_SOURCE
	parameter Source in function AgMD2_ConfigureReferenceOscillator */

#define AGMD2_VAL_REFERENCE_OSCILLATOR_SOURCE_INTERNAL      0
#define AGMD2_VAL_REFERENCE_OSCILLATOR_SOURCE_EXTERNAL      1
#define AGMD2_VAL_REFERENCE_OSCILLATOR_SOURCE_PXIE_CLK100   3
#define AGMD2_VAL_REFERENCE_OSCILLATOR_SOURCE_AXIE_CLK100   4

/*- Defined values for
	attribute AGMD2_ATTR_SAMPLE_CLOCK_SOURCE
	parameter Source in function AgMD2_ConfigureSampleClock */

#define AGMD2_VAL_SAMPLE_CLOCK_SOURCE_INTERNAL              0
#define AGMD2_VAL_SAMPLE_CLOCK_SOURCE_EXTERNAL              1

/*- Defined values for
	attribute AGMD2_ATTR_TRIGGER_SLOPE
	attribute AGMD2_ATTR_TRIGGER_MAGNITUDE_SLOPE
	parameter Slope in function AgMD2_ConfigureEdgeTriggerSource
	parameter Slope in function AgMD2_TriggerMagnitudeConfigure */

#define AGMD2_VAL_NEGATIVE                                  0
#define AGMD2_VAL_POSITIVE                                  1

/*- Defined values for
	attribute AGMD2_ATTR_GLITCH_TRIGGER_POLARITY
	parameter Polarity in function AgMD2_ConfigureGlitchTriggerSource */

#define AGMD2_VAL_GLITCH_POSITIVE                           1
#define AGMD2_VAL_GLITCH_NEGATIVE                           2
#define AGMD2_VAL_GLITCH_EITHER                             3

/*- Defined values for
	attribute AGMD2_ATTR_GLITCH_TRIGGER_CONDITION
	parameter Condition in function AgMD2_ConfigureGlitchTriggerSource */

#define AGMD2_VAL_GLITCH_LESS_THAN                          1
#define AGMD2_VAL_GLITCH_GREATER_THAN                       2

/*- Defined values for
	attribute AGMD2_ATTR_RUNT_TRIGGER_POLARITY
	parameter Polarity in function AgMD2_ConfigureRuntTriggerSource */

#define AGMD2_VAL_RUNT_POSITIVE                             1
#define AGMD2_VAL_RUNT_NEGATIVE                             2
#define AGMD2_VAL_RUNT_EITHER                               3

/*- Defined values for
	attribute AGMD2_ATTR_TV_TRIGGER_POLARITY
	parameter Polarity in function AgMD2_ConfigureTVTriggerSource */

#define AGMD2_VAL_TV_POSITIVE                               1
#define AGMD2_VAL_TV_NEGATIVE                               2

/*- Defined values for
	attribute AGMD2_ATTR_TV_TRIGGER_EVENT
	parameter Event in function AgMD2_ConfigureTVTriggerSource */

#define AGMD2_VAL_TV_EVENT_FIELD1                           1
#define AGMD2_VAL_TV_EVENT_FIELD2                           2
#define AGMD2_VAL_TV_EVENT_ANY_FIELD                        3
#define AGMD2_VAL_TV_EVENT_ANY_LINE                         4
#define AGMD2_VAL_TV_EVENT_LINE_NUMBER                      5

/*- Defined values for
	attribute AGMD2_ATTR_TV_TRIGGER_SIGNAL_FORMAT
	parameter SignalFormat in function AgMD2_ConfigureTVTriggerSource */

#define AGMD2_VAL_NTSC                                      1
#define AGMD2_VAL_PAL                                       2
#define AGMD2_VAL_SECAM                                     3

/*- Defined values for
	attribute AGMD2_ATTR_WIDTH_TRIGGER_CONDITION
	parameter Condition in function AgMD2_ConfigureWidthTriggerSource */

#define AGMD2_VAL_WIDTH_WITHIN                              1
#define AGMD2_VAL_WIDTH_OUTSIDE                             2

/*- Defined values for
	attribute AGMD2_ATTR_WIDTH_TRIGGER_POLARITY
	parameter Polarity in function AgMD2_ConfigureWidthTriggerSource */

#define AGMD2_VAL_WIDTH_POSITIVE                            1
#define AGMD2_VAL_WIDTH_NEGATIVE                            2
#define AGMD2_VAL_WIDTH_EITHER                              3

/*- Defined values for
	attribute AGMD2_ATTR_WINDOW_TRIGGER_CONDITION
	parameter Condition in function AgMD2_ConfigureWindowTriggerSource */

#define AGMD2_VAL_WINDOW_CONDITION_ENTERING                 1
#define AGMD2_VAL_WINDOW_CONDITION_LEAVING                  2

/*- Defined values for
	attribute AGMD2_ATTR_TRIGGER_COUPLING */

#define AGMD2_VAL_TRIGGER_COUPLING_AC                       0
#define AGMD2_VAL_TRIGGER_COUPLING_DC                       1
#define AGMD2_VAL_TRIGGER_COUPLING_NOISE_REJECT             4
#define AGMD2_VAL_TRIGGER_COUPLING_HF_REJECT                2
#define AGMD2_VAL_TRIGGER_COUPLING_LF_REJECT                3

/*- Defined values for */

#define AGMD2_VAL_EDGE_ARM                                  1
#define AGMD2_VAL_WIDTH_ARM                                 2
#define AGMD2_VAL_RUNT_ARM                                  3
#define AGMD2_VAL_GLITCH_ARM                                4
#define AGMD2_VAL_TV_ARM                                    5
#define AGMD2_VAL_WINDOW_ARM                                6

/*- Defined values for */

#define AGMD2_VAL_MAX_TIME_IMMEDIATE                        0
#define AGMD2_VAL_MAX_TIME_INFINITE                         -1

/*- Defined values for */

#define AGMD2_VAL_ARM_SOURCE_OPERATOR_AND                   0
#define AGMD2_VAL_ARM_SOURCE_OPERATOR_OR                    1
#define AGMD2_VAL_ARM_SOURCE_OPERATOR_NONE                  2

/*- Defined values for
	attribute AGMD2_ATTR_TRIGGER_SOURCE_OPERATOR
	parameter Operator in function AgMD2_ConfigureMultiTrigger */

#define AGMD2_VAL_TRIGGER_SOURCE_OPERATOR_AND               0
#define AGMD2_VAL_TRIGGER_SOURCE_OPERATOR_OR                1
#define AGMD2_VAL_TRIGGER_SOURCE_OPERATOR_NONE              2

/*- Defined values for */

#define AGMD2_VAL_SAMPLE_MODE_REAL_TIME                     0
#define AGMD2_VAL_SAMPLE_MODE_EQUIVALENT_TIME               1

/*- Defined values for */

#define AGMD2_VAL_TRIGGER_MODIFIER_NONE                     1
#define AGMD2_VAL_TRIGGER_MODIFIER_AUTO                     2
#define AGMD2_VAL_TRIGGER_MODIFIER_AUTO_LEVEL               3

/*- Defined values for
	attribute AGMD2_ATTR_IS_IDLE
	attribute AGMD2_ATTR_IS_MEASURING
	attribute AGMD2_ATTR_IS_WAITING_FOR_ARM
	attribute AGMD2_ATTR_IS_WAITING_FOR_TRIGGER
	parameter Status in function AgMD2_IsIdle
	parameter Status in function AgMD2_IsMeasuring
	parameter Status in function AgMD2_IsWaitingForArm
	parameter Status in function AgMD2_IsWaitingForTrigger */

#define AGMD2_VAL_ACQUISITION_STATUS_RESULT_TRUE            1
#define AGMD2_VAL_ACQUISITION_STATUS_RESULT_FALSE           2
#define AGMD2_VAL_ACQUISITION_STATUS_RESULT_UNKNOWN         3

/*- Defined values for
	attribute AGMD2_ATTR_ACQUISITION_MODE */

#define AGMD2_VAL_ACQUISITION_MODE_NORMAL                   0
#define AGMD2_VAL_ACQUISITION_MODE_USER_FDK                 15
#define AGMD2_VAL_ACQUISITION_MODE_AVERAGER                 1
#define AGMD2_VAL_ACQUISITION_MODE_PEAK_DETECTION           2
#define AGMD2_VAL_ACQUISITION_MODE_BASE_BAND0               3
#define AGMD2_VAL_ACQUISITION_MODE_DIGITAL_DOWN_CONVERSION  4

/*- Defined values for
	attribute AGMD2_ATTR_DELAY_CONTROL_RANGE */

#define AGMD2_VAL_DELAY_CONTROL_RANGE_DEFAULT               0
#define AGMD2_VAL_DELAY_CONTROL_RANGE_EXTENDED              1

/*- Defined values for
	parameter CoreId in function AgMD2_LogicDeviceGetCoreVersion */

#define AGMD2_VAL_LOGIC_DEVICE_CORE_PCIE                    0
#define AGMD2_VAL_LOGIC_DEVICE_CORE_DDR3A                   1
#define AGMD2_VAL_LOGIC_DEVICE_CORE_DDR3B                   2
#define AGMD2_VAL_LOGIC_DEVICE_CORE_CALIBRATION_DIGITIZER   3
#define AGMD2_VAL_LOGIC_DEVICE_CORE_IFDL_UP                 4
#define AGMD2_VAL_LOGIC_DEVICE_CORE_IFDL_DOWN               5
#define AGMD2_VAL_LOGIC_DEVICE_CORE_IFDL_CONTROL            6
#define AGMD2_VAL_LOGIC_DEVICE_CORE_QDR2                    7
#define AGMD2_VAL_LOGIC_DEVICE_CORE_ADC_INTERFACE           8
#define AGMD2_VAL_LOGIC_DEVICE_CORE_STREAM_PREPARE          9
#define AGMD2_VAL_LOGIC_DEVICE_CORE_TRIGGER_MANAGER         10

/*- Defined values for
	attribute AGMD2_ATTR_LOGIC_DEVICE_MEMORY_BANK_ACCESS_CONTROL */

#define AGMD2_VAL_LOGIC_DEVICE_MEMORY_BANK_ACCESS_CONTROL_SOFTWARE      0
#define AGMD2_VAL_LOGIC_DEVICE_MEMORY_BANK_ACCESS_CONTROL_USER_FIRMWARE 1

/*- Defined values for
	attribute AGMD2_ATTR_LOGIC_DEVICE_MEMORY_BANK_ACCESS_MODE */

#define AGMD2_VAL_LOGIC_DEVICE_MEMORY_BANK_ACCESS_MODE_WRITE 0
#define AGMD2_VAL_LOGIC_DEVICE_MEMORY_BANK_ACCESS_MODE_READ  1

/*- Defined values for
	attribute AGMD2_ATTR_LOGIC_DEVICE_STREAM_MODE */

#define AGMD2_VAL_LOGIC_DEVICE_STREAM_MODE_ACQUISITION      0
#define AGMD2_VAL_LOGIC_DEVICE_STREAM_MODE_EMULATION        1
#define AGMD2_VAL_LOGIC_DEVICE_STREAM_MODE_SEQUENTIAL       2

/*- Defined values for
	attribute AGMD2_ATTR_USER_CONTROL_COUNTERS_MODE */

#define AGMD2_VAL_USER_CONTROL_COUNTERS_MODE_NORMAL         0
#define AGMD2_VAL_USER_CONTROL_COUNTERS_MODE_STREAMING      1

/*- Defined values for
	attribute AGMD2_ATTR_USER_CONTROL_INTER_SEGMENT_DELAY_MODE */

#define AGMD2_VAL_USER_CONTROL_INTER_SEGMENT_DELAY_MODE_SOFTWARE      0
#define AGMD2_VAL_USER_CONTROL_INTER_SEGMENT_DELAY_MODE_USER_FIRMWARE 1

/*- Defined values for
	attribute AGMD2_ATTR_USER_CONTROL_TRIGGER_ENABLE_SOURCE */

#define AGMD2_VAL_USER_CONTROL_TRIGGER_ENABLE_SOURCE_SEGMENTATION  0
#define AGMD2_VAL_USER_CONTROL_TRIGGER_ENABLE_SOURCE_USER_FIRMWARE 1

/*- Defined values for
	attribute AGMD2_ATTR_USER_CONTROL_TRIGGER_SELECTION */

#define AGMD2_VAL_USER_CONTROL_TRIGGER_SELECTION_ANALOG     0
#define AGMD2_VAL_USER_CONTROL_TRIGGER_SELECTION_DIGITAL    1

/*- Defined values for
	parameter ProcessingType in function AgMD2_UserControlStartProcessing
	parameter ProcessingType in function AgMD2_UserControlStopProcessing */

#define AGMD2_VAL_USER_CONTROL_PROCESSING_TYPE1             1
#define AGMD2_VAL_USER_CONTROL_PROCESSING_TYPE2             2

/*- Defined values for
	attribute AGMD2_ATTR_BASELINE_CORRECTION_MODE
	parameter Mode in function AgMD2_BaselineCorrectionConfigure */

#define AGMD2_VAL_BASELINE_CORRECTION_MODE_DISABLED             0
#define AGMD2_VAL_BASELINE_CORRECTION_MODE_CONTINUOUS           1
#define AGMD2_VAL_BASELINE_CORRECTION_MODE_BETWEEN_ACQUISITIONS 2

/*- Defined values for
	attribute AGMD2_ATTR_SELF_TRIGGER_SQUARE_WAVE_SLOPE
	parameter Slope in function AgMD2_SelfTriggerSquareWaveConfigure */

#define AGMD2_VAL_TRIGGER_SLOPE_NEGATIVE                    0
#define AGMD2_VAL_TRIGGER_SLOPE_POSITIVE                    1

/*- Defined values for
	attribute AGMD2_ATTR_SELF_TRIGGER_MODE */

#define AGMD2_VAL_SELF_TRIGGER_MODE_CUSTOM_WAVE             0
#define AGMD2_VAL_SELF_TRIGGER_MODE_SQUARE_WAVE             1

/*- Defined values for
	attribute AGMD2_ATTR_STREAM_TYPE */

#define AGMD2_VAL_STREAM_TYPE_MARKERS                       0
#define AGMD2_VAL_STREAM_TYPE_MIN_MAX                       1
#define AGMD2_VAL_STREAM_TYPE_SAMPLES                       2

/*- Defined values for
	attribute AGMD2_ATTR_CSR_STOP_MODE */

#define AGMD2_VAL_CSR_STOP_MODE_CONTINUOUS                  0

/*- Defined values for
	attribute AGMD2_ATTR_PRIVATE_DATA_LOCK */

#define AGMD2_VAL_DATA_LOCK_UNLOCKED                        0
#define AGMD2_VAL_DATA_LOCK_ARMED                           1
#define AGMD2_VAL_DATA_LOCK_LOCKED                          2

/*- Defined values for
	attribute AGMD2_ATTR_CALIBRATION_EQUALIZATION */

#define AGMD2_VAL_CALIBRATION_EQUALIZATION_OFF              0
#define AGMD2_VAL_CALIBRATION_EQUALIZATION_CUSTOM           1
#define AGMD2_VAL_CALIBRATION_EQUALIZATION_SMOOTH_ROLL_OFF  2
#define AGMD2_VAL_CALIBRATION_EQUALIZATION_SHARP_ROLL_OFF   3

/*- Defined values for
	attribute AGMD2_ATTR_STREAMING_MODE */

#define AGMD2_VAL_STREAMING_MODE_DISABLED                   0
#define AGMD2_VAL_STREAMING_MODE_CONTINUOUS                 1
#define AGMD2_VAL_STREAMING_MODE_TRIGGERED                  2


/****************************************************************************
 *---------------- Instrument Driver Function Declarations -----------------*
 ****************************************************************************/

/*- AgMD2 */

ViStatus _VI_FUNC AgMD2_init(ViRsrc ResourceName, ViBoolean IdQuery, ViBoolean Reset, ViSession* Vi);
ViStatus _VI_FUNC AgMD2_close(ViSession Vi);
ViStatus _VI_FUNC AgMD2_InitWithOptions(ViRsrc ResourceName, ViBoolean IdQuery, ViBoolean Reset, ViConstString OptionsString, ViSession* Vi);

/*- Utility */

ViStatus _VI_FUNC AgMD2_revision_query(ViSession Vi, ViChar DriverRev[], ViChar InstrRev[]);
ViStatus _VI_FUNC AgMD2_error_message(ViSession Vi, ViStatus ErrorCode, ViChar ErrorMessage[]);
ViStatus _VI_FUNC AgMD2_GetError(ViSession Vi, ViStatus* ErrorCode, ViInt32 ErrorDescriptionBufferSize, ViChar ErrorDescription[]);
ViStatus _VI_FUNC AgMD2_ClearError(ViSession Vi);
ViStatus _VI_FUNC AgMD2_ClearInterchangeWarnings(ViSession Vi);
ViStatus _VI_FUNC AgMD2_GetNextCoercionRecord(ViSession Vi, ViInt32 CoercionRecordBufferSize, ViChar CoercionRecord[]);
ViStatus _VI_FUNC AgMD2_GetNextInterchangeWarning(ViSession Vi, ViInt32 InterchangeWarningBufferSize, ViChar InterchangeWarning[]);
ViStatus _VI_FUNC AgMD2_InvalidateAllAttributes(ViSession Vi);
ViStatus _VI_FUNC AgMD2_ResetInterchangeCheck(ViSession Vi);
ViStatus _VI_FUNC AgMD2_Disable(ViSession Vi);
ViStatus _VI_FUNC AgMD2_error_query(ViSession Vi, ViInt32* ErrorCode, ViChar ErrorMessage[]);
ViStatus _VI_FUNC AgMD2_LockSession(ViSession Vi, ViBoolean* CallerHasLock);
ViStatus _VI_FUNC AgMD2_reset(ViSession Vi);
ViStatus _VI_FUNC AgMD2_ResetWithDefaults(ViSession Vi);
ViStatus _VI_FUNC AgMD2_self_test(ViSession Vi, ViInt16* TestResult, ViChar TestMessage[]);
ViStatus _VI_FUNC AgMD2_UnlockSession(ViSession Vi, ViBoolean* CallerHasLock);

/*- Temperature */

ViStatus _VI_FUNC AgMD2_ConfigureTemperatureUnits(ViSession Vi, ViInt32 Units);
ViStatus _VI_FUNC AgMD2_QueryBoardTemperature(ViSession Vi, ViReal64* Temperature);
ViStatus _VI_FUNC AgMD2_QueryChannelTemperature(ViSession Vi, ViConstString Channel, ViReal64* Temperature);

/*- Attribute Accessors */

ViStatus _VI_FUNC AgMD2_GetAttributeViInt32(ViSession Vi, ViConstString RepCapIdentifier, ViAttr AttributeID, ViInt32* AttributeValue);
ViStatus _VI_FUNC AgMD2_GetAttributeViInt64(ViSession Vi, ViConstString RepCapIdentifier, ViAttr AttributeID, ViInt64* AttributeValue);
ViStatus _VI_FUNC AgMD2_GetAttributeViReal64(ViSession Vi, ViConstString RepCapIdentifier, ViAttr AttributeID, ViReal64* AttributeValue);
ViStatus _VI_FUNC AgMD2_GetAttributeViBoolean(ViSession Vi, ViConstString RepCapIdentifier, ViAttr AttributeID, ViBoolean* AttributeValue);
ViStatus _VI_FUNC AgMD2_GetAttributeViSession(ViSession Vi, ViConstString RepCapIdentifier, ViAttr AttributeID, ViSession* AttributeValue);
ViStatus _VI_FUNC AgMD2_GetAttributeViString(ViSession Vi, ViConstString RepCapIdentifier, ViAttr AttributeID, ViInt32 AttributeValueBufferSize, ViChar AttributeValue[]);
ViStatus _VI_FUNC AgMD2_SetAttributeViInt32(ViSession Vi, ViConstString RepCapIdentifier, ViAttr AttributeID, ViInt32 AttributeValue);
ViStatus _VI_FUNC AgMD2_SetAttributeViInt64(ViSession Vi, ViConstString RepCapIdentifier, ViAttr AttributeID, ViInt64 AttributeValue);
ViStatus _VI_FUNC AgMD2_SetAttributeViReal64(ViSession Vi, ViConstString RepCapIdentifier, ViAttr AttributeID, ViReal64 AttributeValue);
ViStatus _VI_FUNC AgMD2_SetAttributeViBoolean(ViSession Vi, ViConstString RepCapIdentifier, ViAttr AttributeID, ViBoolean AttributeValue);
ViStatus _VI_FUNC AgMD2_SetAttributeViSession(ViSession Vi, ViConstString RepCapIdentifier, ViAttr AttributeID, ViSession AttributeValue);
ViStatus _VI_FUNC AgMD2_SetAttributeViString(ViSession Vi, ViConstString RepCapIdentifier, ViAttr AttributeID, ViConstString AttributeValue);

/*- Calibration */

ViStatus _VI_FUNC AgMD2_SelfCalibrate(ViSession Vi);

/*- Acquisition */

ViStatus _VI_FUNC AgMD2_ConfigureAcquisition(ViSession Vi, ViInt64 NumRecordsToAcquire, ViInt64 RecordSize, ViReal64 SampleRate);

/*- Channel */

ViStatus _VI_FUNC AgMD2_ConfigureChannel(ViSession Vi, ViConstString ChannelName, ViReal64 Range, ViReal64 Offset, ViInt32 Coupling, ViBoolean Enabled);
ViStatus _VI_FUNC AgMD2_ConfigureInputFilter(ViSession Vi, ViConstString ChannelName, ViReal64 MinFrequency, ViReal64 MaxFrequency);
ViStatus _VI_FUNC AgMD2_GetChannelName(ViSession Vi, ViInt32 Index, ViInt32 NameBufferSize, ViChar Name[]);

/*- Interleaved Data */

ViStatus _VI_FUNC AgMD2_ConfigureTimeInterleavedChannelList(ViSession Vi, ViConstString ChannelName, ViConstString ChannelList);

/*- Reference Oscillator */

ViStatus _VI_FUNC AgMD2_ConfigureReferenceOscillator(ViSession Vi, ViInt32 Source, ViReal64 Frequency);
ViStatus _VI_FUNC AgMD2_ConfigureReferenceOscillatorOutputEnabled(ViSession Vi, ViBoolean Enabled);

/*- Sample Clock */

ViStatus _VI_FUNC AgMD2_ConfigureSampleClock(ViSession Vi, ViInt32 Source, ViReal64 Frequency, ViReal64 Divider);
ViStatus _VI_FUNC AgMD2_ConfigureSampleClockOutputEnabled(ViSession Vi, ViBoolean Enabled);

/*- Trigger */

ViStatus _VI_FUNC AgMD2_ConfigureEdgeTriggerSource(ViSession Vi, ViConstString Source, ViReal64 Level, ViInt32 Slope);
ViStatus _VI_FUNC AgMD2_ConfigureGlitchTriggerSource(ViSession Vi, ViConstString Source, ViReal64 Level, ViReal64 Width, ViInt32 Polarity, ViInt32 Condition);
ViStatus _VI_FUNC AgMD2_ConfigureRuntTriggerSource(ViSession Vi, ViConstString Source, ViReal64 ThresholdLow, ViReal64 ThresholdHigh, ViInt32 Polarity);
ViStatus _VI_FUNC AgMD2_ConfigureTVTriggerSource(ViSession Vi, ViConstString Source, ViInt32 SignalFormat, ViInt32 Event, ViInt32 Polarity);
ViStatus _VI_FUNC AgMD2_ConfigureWidthTriggerSource(ViSession Vi, ViConstString Source, ViReal64 Level, ViReal64 ThresholdLow, ViReal64 ThresholdHigh, ViInt32 Polarity, ViInt32 Condition);
ViStatus _VI_FUNC AgMD2_ConfigureWindowTriggerSource(ViSession Vi, ViConstString Source, ViReal64 ThresholdLow, ViReal64 ThresholdHigh, ViInt32 Condition);
ViStatus _VI_FUNC AgMD2_ConfigureMultiTrigger(ViSession Vi, ViConstString SourceList, ViInt32 Operator);
ViStatus _VI_FUNC AgMD2_GetTriggerSourceName(ViSession Vi, ViInt32 Index, ViInt32 NameBufferSize, ViChar Name[]);
ViStatus _VI_FUNC AgMD2_ConfigurePretriggerSamples(ViSession Vi, ViInt64 PretriggerSamples);
ViStatus _VI_FUNC AgMD2_ConfigureTriggerHoldoff(ViSession Vi, ViReal64 Holdoff);

/*- Waveform Acquisition */

ViStatus _VI_FUNC AgMD2_ReadWaveformInt16(ViSession Vi, ViConstString ChannelName, ViInt32 MaxTimeMilliseconds, ViInt64 WaveformArraySize, ViInt16 WaveformArray[], ViInt64* ActualPoints, ViInt64* FirstValidPoint, ViReal64* InitialXOffset, ViReal64* InitialXTimeSeconds, ViReal64* InitialXTimeFraction, ViReal64* XIncrement, ViReal64* ScaleFactor, ViReal64* ScaleOffset);
ViStatus _VI_FUNC AgMD2_ReadWaveformInt32(ViSession Vi, ViConstString ChannelName, ViInt32 MaxTimeMilliseconds, ViInt64 WaveformArraySize, ViInt32 WaveformArray[], ViInt64* ActualPoints, ViInt64* FirstValidPoint, ViReal64* InitialXOffset, ViReal64* InitialXTimeSeconds, ViReal64* InitialXTimeFraction, ViReal64* XIncrement, ViReal64* ScaleFactor, ViReal64* ScaleOffset);
ViStatus _VI_FUNC AgMD2_ReadWaveformInt8(ViSession Vi, ViConstString ChannelName, ViInt32 MaxTimeMilliseconds, ViInt64 WaveformArraySize, ViInt8 WaveformArray[], ViInt64* ActualPoints, ViInt64* FirstValidPoint, ViReal64* InitialXOffset, ViReal64* InitialXTimeSeconds, ViReal64* InitialXTimeFraction, ViReal64* XIncrement, ViReal64* ScaleFactor, ViReal64* ScaleOffset);
ViStatus _VI_FUNC AgMD2_ReadWaveformReal64(ViSession Vi, ViConstString ChannelName, ViInt32 MaxTimeMilliseconds, ViInt64 WaveformArraySize, ViReal64 WaveformArray[], ViInt64* ActualPoints, ViInt64* FirstValidPoint, ViReal64* InitialXOffset, ViReal64* InitialXTimeSeconds, ViReal64* InitialXTimeFraction, ViReal64* XIncrement);

/*- Low-Level Acquisition */

ViStatus _VI_FUNC AgMD2_InitiateAcquisition(ViSession Vi);
ViStatus _VI_FUNC AgMD2_Abort(ViSession Vi);
ViStatus _VI_FUNC AgMD2_SendSoftwareArm(ViSession Vi);
ViStatus _VI_FUNC AgMD2_SendSoftwareTrigger(ViSession Vi);
ViStatus _VI_FUNC AgMD2_WaitForAcquisitionComplete(ViSession Vi, ViInt32 MaxTimeMilliseconds);
ViStatus _VI_FUNC AgMD2_FetchWaveformReal64(ViSession Vi, ViConstString ChannelName, ViInt64 WaveformArraySize, ViReal64 WaveformArray[], ViInt64* ActualPoints, ViInt64* FirstValidPoint, ViReal64* InitialXOffset, ViReal64* InitialXTimeSeconds, ViReal64* InitialXTimeFraction, ViReal64* XIncrement);
ViStatus _VI_FUNC AgMD2_FetchWaveformInt8(ViSession Vi, ViConstString ChannelName, ViInt64 WaveformArraySize, ViInt8 WaveformArray[], ViInt64* ActualPoints, ViInt64* FirstValidPoint, ViReal64* InitialXOffset, ViReal64* InitialXTimeSeconds, ViReal64* InitialXTimeFraction, ViReal64* XIncrement, ViReal64* ScaleFactor, ViReal64* ScaleOffset);
ViStatus _VI_FUNC AgMD2_FetchWaveformInt16(ViSession Vi, ViConstString ChannelName, ViInt64 WaveformArraySize, ViInt16 WaveformArray[], ViInt64* ActualPoints, ViInt64* FirstValidPoint, ViReal64* InitialXOffset, ViReal64* InitialXTimeSeconds, ViReal64* InitialXTimeFraction, ViReal64* XIncrement, ViReal64* ScaleFactor, ViReal64* ScaleOffset);
ViStatus _VI_FUNC AgMD2_FetchWaveformInt32(ViSession Vi, ViConstString ChannelName, ViInt64 WaveformArraySize, ViInt32 WaveformArray[], ViInt64* ActualPoints, ViInt64* FirstValidPoint, ViReal64* InitialXOffset, ViReal64* InitialXTimeSeconds, ViReal64* InitialXTimeFraction, ViReal64* XIncrement, ViReal64* ScaleFactor, ViReal64* ScaleOffset);
ViStatus _VI_FUNC AgMD2_IsIdle(ViSession Vi, ViInt32* Status);
ViStatus _VI_FUNC AgMD2_IsMeasuring(ViSession Vi, ViInt32* Status);
ViStatus _VI_FUNC AgMD2_IsWaitingForArm(ViSession Vi, ViInt32* Status);
ViStatus _VI_FUNC AgMD2_IsWaitingForTrigger(ViSession Vi, ViInt32* Status);
ViStatus _VI_FUNC AgMD2_QueryMinWaveformMemory(ViSession Vi, ViInt32 DataWidth, ViInt64 NumRecords, ViInt64 OffsetWithinRecord, ViInt64 NumPointsPerRecord, ViInt64* NumSamples);
ViStatus _VI_FUNC AgMD2_FetchAccumulatedWaveformInt32(ViSession Vi, ViConstString ChannelName, ViInt64 FirstRecord, ViInt64 NumRecords, ViInt64 OffsetWithinRecord, ViInt64 NumPointsPerRecord, ViInt64 WaveformArraySize, ViInt32 WaveformArray[], ViInt32* ActualAverages, ViInt64* ActualRecords, ViInt64 ActualPoints[], ViInt64 FirstValidPoint[], ViReal64* InitialXOffset, ViReal64 InitialXTimeSeconds[], ViReal64 InitialXTimeFraction[], ViReal64* XIncrement, ViReal64* ScaleFactor, ViReal64* ScaleOffset, ViInt32 Flags[]);
ViStatus _VI_FUNC AgMD2_FetchAccumulatedWaveformReal64(ViSession Vi, ViConstString ChannelName, ViInt64 FirstRecord, ViInt64 NumRecords, ViInt64 OffsetWithinRecord, ViInt64 NumPointsPerRecord, ViInt64 WaveformArraySize, ViReal64 WaveformArray[], ViInt32* ActualAverages, ViInt64* ActualRecords, ViInt64 ActualPoints[], ViInt64 FirstValidPoint[], ViReal64* InitialXOffset, ViReal64 InitialXTimeSeconds[], ViReal64 InitialXTimeFraction[], ViReal64* XIncrement, ViInt32 Flags[]);

/*- Multi-Record Acquisition */

ViStatus _VI_FUNC AgMD2_FetchMultiRecordWaveformInt16(ViSession Vi, ViConstString ChannelName, ViInt64 FirstRecord, ViInt64 NumRecords, ViInt64 OffsetWithinRecord, ViInt64 NumPointsPerRecord, ViInt64 WaveformArrayBufferSize, ViInt16 WaveformArray[], ViInt64* WaveformArrayActualSize, ViInt64* ActualRecords, ViInt64 ActualPoints[], ViInt64 FirstValidPoint[], ViReal64 InitialXOffset[], ViReal64 InitialXTimeSeconds[], ViReal64 InitialXTimeFraction[], ViReal64* XIncrement, ViReal64* ScaleFactor, ViReal64* ScaleOffset);
ViStatus _VI_FUNC AgMD2_FetchMultiRecordWaveformInt8(ViSession Vi, ViConstString ChannelName, ViInt64 FirstRecord, ViInt64 NumRecords, ViInt64 OffsetWithinRecord, ViInt64 NumPointsPerRecord, ViInt64 WaveformArrayBufferSize, ViInt8 WaveformArray[], ViInt64* WaveformArrayActualSize, ViInt64* ActualRecords, ViInt64 ActualPoints[], ViInt64 FirstValidPoint[], ViReal64 InitialXOffset[], ViReal64 InitialXTimeSeconds[], ViReal64 InitialXTimeFraction[], ViReal64* XIncrement, ViReal64* ScaleFactor, ViReal64* ScaleOffset);
ViStatus _VI_FUNC AgMD2_FetchMultiRecordWaveformInt32(ViSession Vi, ViConstString ChannelName, ViInt64 FirstRecord, ViInt64 NumRecords, ViInt64 OffsetWithinRecord, ViInt64 NumPointsPerRecord, ViInt64 WaveformArrayBufferSize, ViInt32 WaveformArray[], ViInt64* WaveformArrayActualSize, ViInt64* ActualRecords, ViInt64 ActualPoints[], ViInt64 FirstValidPoint[], ViReal64 InitialXOffset[], ViReal64 InitialXTimeSeconds[], ViReal64 InitialXTimeFraction[], ViReal64* XIncrement, ViReal64* ScaleFactor, ViReal64* ScaleOffset);
ViStatus _VI_FUNC AgMD2_FetchMultiRecordWaveformReal64(ViSession Vi, ViConstString ChannelName, ViInt64 FirstRecord, ViInt64 NumRecords, ViInt64 OffsetWithinRecord, ViInt64 NumPointsPerRecord, ViInt64 WaveformArrayBufferSize, ViReal64 WaveformArray[], ViInt64* WaveformArrayActualSize, ViInt64* ActualRecords, ViInt64 ActualPoints[], ViInt64 FirstValidPoint[], ViReal64 InitialXOffset[], ViReal64 InitialXTimeSeconds[], ViReal64 InitialXTimeFraction[], ViReal64* XIncrement);

/*- Private */

ViStatus _VI_FUNC AgMD2_WriteReg32(ViSession Vi, ViInt32 SpaceAddress, ViInt32 RegisterAddress, ViInt32 Value);
ViStatus _VI_FUNC AgMD2_ReadReg32(ViSession Vi, ViInt32 SpaceAddress, ViInt32 RegisterAddress, ViInt32* Value);
ViStatus _VI_FUNC AgMD2_ReadBurstInt32(ViSession Vi, ViInt32 SpaceAddress, ViInt64 RegisterAddress, ViInt64 NumberOfElements, ViInt64 DataArrayBufferSize, ViInt32 DataArray[], ViInt64* DataArrayActualSize, ViInt64* FirstValidElement);
ViStatus _VI_FUNC AgMD2_WriteBurstInt32(ViSession Vi, ViInt32 SpaceAddress, ViInt64 RegisterAddress, ViInt32 DataArrayBufferSize, ViInt32 DataArray[]);

/*- PrivateFirmware */

ViStatus _VI_FUNC AgMD2_GetPrivateFirmwareName(ViSession Vi, ViInt32 Index, ViInt32 NameBufferSize, ViChar Name[]);
ViStatus _VI_FUNC AgMD2_LoadFirmwareFromFile(ViSession Vi, ViConstString PrivateFirmware, ViConstString Path);

/*- PrivateStore */

ViStatus _VI_FUNC AgMD2_GetPrivateStoreName(ViSession Vi, ViInt32 Index, ViInt32 NameBufferSize, ViChar Name[]);
ViStatus _VI_FUNC AgMD2_LoadPrivateStoreFromFile(ViSession Vi, ViConstString PrivateStore, ViConstString Path);
ViStatus _VI_FUNC AgMD2_SavePrivateStoreToFile(ViSession Vi, ViConstString PrivateStore, ViConstString Path);
ViStatus _VI_FUNC AgMD2_LoadPrivateStoreFromAttributes(ViSession Vi, ViConstString PrivateStore);
ViStatus _VI_FUNC AgMD2_ReadAttributesFromPrivateStore(ViSession Vi, ViConstString PrivateStore);

/*- EepromModuleGeneration */

ViStatus _VI_FUNC AgMD2_EepromModuleGenerationSaveToFile(ViSession Vi, ViConstString Path);

/*- PrivateCalibration */

ViStatus _VI_FUNC AgMD2_GetCalibrationValueReal64(ViSession Vi, ViConstString Name, ViReal64* Value);
ViStatus _VI_FUNC AgMD2_SetCalibrationValueReal64(ViSession Vi, ViConstString Name, ViReal64 Value);
ViStatus _VI_FUNC AgMD2_GetCalibrationValueInt32(ViSession Vi, ViConstString Name, ViInt32* Value);
ViStatus _VI_FUNC AgMD2_SetCalibrationValueInt32(ViSession Vi, ViConstString Name, ViInt32 Value);
ViStatus _VI_FUNC AgMD2_SetCalibrationValueString(ViSession Vi, ViConstString Name, ViConstString Value);
ViStatus _VI_FUNC AgMD2_GetCalibrationValueString(ViSession Vi, ViConstString Name, ViInt32 ValueBufferSize, ViChar Value[]);
ViStatus _VI_FUNC AgMD2_SetCalibrationValueBoolean(ViSession Vi, ViConstString Name, ViBoolean Value);
ViStatus _VI_FUNC AgMD2_GetCalibrationValueBoolean(ViSession Vi, ViConstString Name, ViBoolean* Value);
ViStatus _VI_FUNC AgMD2_GetCalibrationArraySize(ViSession Vi, ViConstString Name, ViInt32* ArraySize);
ViStatus _VI_FUNC AgMD2_GetCalibrationArrayInt32(ViSession Vi, ViConstString Name, ViInt32 ValuesBufferSize, ViInt32 Values[], ViInt32* ValuesActualSize);
ViStatus _VI_FUNC AgMD2_SetCalibrationArrayInt32(ViSession Vi, ViConstString Name, ViInt32 ValuesBufferSize, ViInt32 Values[]);
ViStatus _VI_FUNC AgMD2_GetCalibrationArrayReal64(ViSession Vi, ViConstString Name, ViInt32 ValuesBufferSize, ViReal64 Values[], ViInt32* ValuesActualSize);
ViStatus _VI_FUNC AgMD2_SetCalibrationArrayReal64(ViSession Vi, ViConstString Name, ViInt32 ValuesBufferSize, ViReal64 Values[]);

/*- PrivateDataLock */

ViStatus _VI_FUNC AgMD2_ArmDataLock(ViSession Vi);
ViStatus _VI_FUNC AgMD2_UnlockData(ViSession Vi);

/*- LogicDevice */

ViStatus _VI_FUNC AgMD2_GetLogicDeviceName(ViSession Vi, ViInt32 Index, ViInt32 NameBufferSize, ViChar Name[]);
ViStatus _VI_FUNC AgMD2_LogicDeviceLoadFromFile(ViSession Vi, ViConstString LogicDevice, ViConstString Path);
ViStatus _VI_FUNC AgMD2_LogicDeviceReadIndirectInt32(ViSession Vi, ViConstString LogicDevice, ViInt32 Id, ViInt32 StartAddress, ViInt64 NumElements, ViInt64 DataBufferSize, ViInt32 Data[], ViInt64* ActualElements, ViInt64* FirstValidElement);
ViStatus _VI_FUNC AgMD2_LogicDeviceReadRegisterInt32(ViSession Vi, ViConstString LogicDevice, ViInt32 Offset, ViInt32* Value);
ViStatus _VI_FUNC AgMD2_LogicDeviceWriteIndirectInt32(ViSession Vi, ViConstString LogicDevice, ViInt32 Id, ViInt32 StartAddress, ViInt32 NumElements, ViInt32 DataBufferSize, ViInt32 Data[]);
ViStatus _VI_FUNC AgMD2_LogicDeviceWriteRegisterInt32(ViSession Vi, ViConstString LogicDevice, ViInt32 Offset, ViInt32 Value);
ViStatus _VI_FUNC AgMD2_LogicDeviceConfigureBufferAddresses(ViSession Vi, ViConstString LogicDevice, ViInt32 BufferId, ViInt64 Base, ViInt64 Limit);
ViStatus _VI_FUNC AgMD2_LogicDeviceGetBufferAddresses(ViSession Vi, ViConstString LogicDevice, ViInt32 BufferId, ViInt64* Base, ViInt64* Limit);
ViStatus _VI_FUNC AgMD2_LogicDeviceGetCoreVersion(ViSession Vi, ViConstString LogicDevice, ViInt32 CoreId, ViInt32* Version, ViInt32 VersionStringBufferSize, ViChar VersionString[]);
ViStatus _VI_FUNC AgMD2_LogicDeviceWriteFirmwareStoreFromFile(ViSession Vi, ViConstString LogicDevice, ViInt32 FirmwareStore, ViConstString Path);
ViStatus _VI_FUNC AgMD2_LogicDeviceWriteStreamWaveformInt16(ViSession Vi, ViConstString LogicDevice, ViInt32 Stream, ViInt32 SamplesBufferSize, ViInt16 Samples[]);
ViStatus _VI_FUNC AgMD2_LogicDevicePlaybackStreamWaveforms(ViSession Vi, ViConstString LogicDevice);
ViStatus _VI_FUNC AgMD2_LogicDeviceWriteStreamWaveformInt8(ViSession Vi, ViConstString LogicDevice, ViInt32 Stream, ViInt32 SamplesBufferSize, ViInt8 Samples[]);

/*- LogicDeviceIFDL */

ViStatus _VI_FUNC AgMD2_LogicDeviceIFDLStartSelfTestReceiver(ViSession Vi, ViConstString LogicDeviceIFDL);
ViStatus _VI_FUNC AgMD2_LogicDeviceIFDLStartSelfTestTransmitter(ViSession Vi, ViConstString LogicDeviceIFDL);
ViStatus _VI_FUNC AgMD2_LogicDeviceIFDLCheckSelfTestReceiver(ViSession Vi, ViConstString LogicDeviceIFDL, ViBoolean* Val);
ViStatus _VI_FUNC AgMD2_GetLogicDeviceIFDLName(ViSession Vi, ViConstString LogicDeviceIFDL, ViInt32 Index, ViInt32 NameBufferSize, ViChar Name[]);

/*- LogicDeviceMemoryBank */

ViStatus _VI_FUNC AgMD2_GetLogicDeviceMemoryBankName(ViSession Vi, ViConstString LogicDeviceMemoryBank, ViInt32 Index, ViInt32 NameBufferSize, ViChar Name[]);

/*- Magnitude */

ViStatus _VI_FUNC AgMD2_TriggerMagnitudeConfigure(ViSession Vi, ViConstString TriggerSource, ViReal64 Level, ViReal64 Hysteresis, ViInt32 Slope);

/*- SelfTrigger */

ViStatus _VI_FUNC AgMD2_SelfTriggerAbortGeneration(ViSession Vi, ViConstString TriggerSource);
ViStatus _VI_FUNC AgMD2_SelfTriggerInitiateGeneration(ViSession Vi, ViConstString TriggerSource);

/*- SquareWave */

ViStatus _VI_FUNC AgMD2_SelfTriggerSquareWaveConfigure(ViSession Vi, ViConstString TriggerSource, ViReal64 Frequency, ViReal64 DutyCycle, ViInt32 Slope);

/*- CustomWave */

ViStatus _VI_FUNC AgMD2_SelfTriggerCustomWaveLoadConfigurationFile(ViSession Vi, ViConstString TriggerSource, ViConstString Path);

/*- ControlIO */

ViStatus _VI_FUNC AgMD2_GetControlIOName(ViSession Vi, ViInt32 Index, ViInt32 NameBufferSize, ViChar Name[]);

/*- Acquisition */

ViStatus _VI_FUNC AgMD2_ApplySetup(ViSession Vi);

/*- UserControl */

ViStatus _VI_FUNC AgMD2_UserControlReadControlRegisterInt32(ViSession Vi, ViInt32 Offset, ViInt32* Value);
ViStatus _VI_FUNC AgMD2_UserControlStartProcessing(ViSession Vi, ViInt32 ProcessingType);
ViStatus _VI_FUNC AgMD2_UserControlStartSegmentation(ViSession Vi);
ViStatus _VI_FUNC AgMD2_UserControlStopProcessing(ViSession Vi, ViInt32 ProcessingType);
ViStatus _VI_FUNC AgMD2_UserControlStopSegmentation(ViSession Vi);
ViStatus _VI_FUNC AgMD2_UserControlWaitForProcessingComplete(ViSession Vi, ViConstString LogicDevice, ViInt32 ProcessingType, ViInt32 MaxTimeMilliseconds);
ViStatus _VI_FUNC AgMD2_UserControlWriteControlRegisterInt32(ViSession Vi, ViInt32 Offset, ViInt32 Value);

/*- TSR */

ViStatus _VI_FUNC AgMD2_TSRContinue(ViSession Vi);

/*- InstrumentInfo */

ViStatus _VI_FUNC AgMD2_InstrumentInfoAttributeIDValueFromString(ViSession Vi, ViConstString Str, ViInt32* Value);
ViStatus _VI_FUNC AgMD2_InstrumentInfoAttributeIDValueToString(ViSession Vi, ViInt32 Value, ViInt32 StrBufferSize, ViChar Str[]);

/*- MonitoringValue */

ViStatus _VI_FUNC AgMD2_GetMonitoringValueName(ViSession Vi, ViInt32 Index, ViInt32 NameBufferSize, ViChar Name[]);

/*- Calibration */

ViStatus _VI_FUNC AgMD2_CalibrationCancel(ViSession Vi);
ViStatus _VI_FUNC AgMD2_CalibrationLoadFromFile(ViSession Vi, ViConstString Path);
ViStatus _VI_FUNC AgMD2_CalibrationSaveToFile(ViSession Vi, ViConstString Path);

/*- DelayControl */

ViStatus _VI_FUNC AgMD2_GetDelayControlName(ViSession Vi, ViInt32 Index, ViInt32 NameBufferSize, ViChar Name[]);

/*- NSA */

ViStatus _VI_FUNC AgMD2_NSAConfigure(ViSession Vi, ViConstString Channel, ViBoolean Enabled, ViInt32 Threshold, ViInt32 NoiseBase);

/*- BaselineCorrection */

ViStatus _VI_FUNC AgMD2_BaselineCorrectionConfigure(ViSession Vi, ViConstString Channel, ViInt32 Mode, ViInt32 ThresholdHigh, ViInt32 ThresholdLow, ViInt32 DigitalOffset);

/*- PeakDetection */

ViStatus _VI_FUNC AgMD2_PeakDetectionConfigure(ViSession Vi, ViConstString Channel, ViInt32 RisingDelta, ViInt32 FallingDelta, ViBoolean AmplitudeAccumulationEnabled);

/*- ModuleSynchronization */

ViStatus _VI_FUNC AgMD2_ModuleSynchronizationConfigureSlaves(ViSession Vi, ViInt32 SlavesCount, ViInt32 Slaves[]);
ViStatus _VI_FUNC AgMD2_ModuleSynchronizationGetSlaves(ViSession Vi, ViInt32 SlavesBufferSize, ViInt32 Slaves[], ViInt32* ActualSlaves);

/*- Stream */

ViStatus _VI_FUNC AgMD2_GetStreamName(ViSession Vi, ViInt32 Index, ViInt32 NameBufferSize, ViChar Name[]);
ViStatus _VI_FUNC AgMD2_StreamFetchDataInt32(ViSession Vi, ViConstString Stream, ViInt64 NbrElementsToFetch, ViInt64 ArrayBufferSize, ViInt32 Array[], ViInt64* ArrayActualSize, ViInt64* AvailableElements, ViInt64* ActualElements, ViInt64* FirstValidElement);

/*- DDCCore */

ViStatus _VI_FUNC AgMD2_GetDDCCoreName(ViSession Vi, ViInt32 Index, ViInt32 NameBufferSize, ViChar Name[]);
ViStatus _VI_FUNC AgMD2_DDCCoreFetchWaveformInt16(ViSession Vi, ViConstString DDCCore, ViInt64 FirstRecord, ViInt64 NumRecords, ViInt64 OffsetWithinRecord, ViInt64 NumPointsPerRecord, ViInt64 WaveformArrayBufferSize, ViInt16 WaveformArray[], ViInt64* ActualRecords, ViInt64 ActualPoints[], ViInt64 FirstValidPoint[], ViReal64 InitialXOffset[], ViReal64 InitialXTimeSeconds[], ViReal64 InitialXTimeFraction[], ViReal64* XIncrement, ViReal64* ScaleFactor, ViReal64* ScaleOffset, ViInt32 Flags[]);
ViStatus _VI_FUNC AgMD2_DDCCoreFetchWaveformInt32(ViSession Vi, ViConstString DDCCore, ViInt64 FirstRecord, ViInt64 NumRecords, ViInt64 OffsetWithinRecord, ViInt64 NumPointsPerRecord, ViInt64 WaveformArrayBufferSize, ViInt32 WaveformArray[], ViInt64* ActualRecords, ViInt64 ActualPoints[], ViInt64 FirstValidPoint[], ViReal64 InitialXOffset[], ViReal64 InitialXTimeSeconds[], ViReal64 InitialXTimeFraction[], ViReal64* XIncrement, ViReal64* ScaleFactor, ViReal64* ScaleOffset, ViInt32 Flags[]);


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


#define AGMD2_ERROR_CANNOT_RECOVER                          (IVIC_ERROR_BASE + 0x0000)
#define AGMD2_ERROR_INSTRUMENT_STATUS                       (IVIC_ERROR_BASE + 0x0001)
#define AGMD2_ERROR_CANNOT_OPEN_FILE                        (IVIC_ERROR_BASE + 0x0002)
#define AGMD2_ERROR_READING_FILE                            (IVIC_ERROR_BASE + 0x0003)
#define AGMD2_ERROR_WRITING_FILE                            (IVIC_ERROR_BASE + 0x0004)
#define AGMD2_ERROR_INVALID_PATHNAME                        (IVIC_ERROR_BASE + 0x000B)
#define AGMD2_ERROR_INVALID_VALUE                           (IVIC_ERROR_BASE + 0x0010)
#define AGMD2_ERROR_FUNCTION_NOT_SUPPORTED                  (IVIC_ERROR_BASE + 0x0011)
#define AGMD2_ERROR_ATTRIBUTE_NOT_SUPPORTED                 (IVIC_ERROR_BASE + 0x0012)
#define AGMD2_ERROR_VALUE_NOT_SUPPORTED                     (IVIC_ERROR_BASE + 0x0013)
#define AGMD2_ERROR_NOT_INITIALIZED                         (IVIC_ERROR_BASE + 0x001D)
#define AGMD2_ERROR_UNKNOWN_CHANNEL_NAME                    (IVIC_ERROR_BASE + 0x0020)
#define AGMD2_ERROR_TOO_MANY_OPEN_FILES                     (IVIC_ERROR_BASE + 0x0023)
#define AGMD2_ERROR_CHANNEL_NAME_REQUIRED                   (IVIC_ERROR_BASE + 0x0044)
#define AGMD2_ERROR_MISSING_OPTION_NAME                     (IVIC_ERROR_BASE + 0x0049)
#define AGMD2_ERROR_MISSING_OPTION_VALUE                    (IVIC_ERROR_BASE + 0x004A)
#define AGMD2_ERROR_BAD_OPTION_NAME                         (IVIC_ERROR_BASE + 0x004B)
#define AGMD2_ERROR_BAD_OPTION_VALUE                        (IVIC_ERROR_BASE + 0x004C)
#define AGMD2_ERROR_OUT_OF_MEMORY                           (IVIC_ERROR_BASE + 0x0056)
#define AGMD2_ERROR_OPERATION_PENDING                       (IVIC_ERROR_BASE + 0x0057)
#define AGMD2_ERROR_NULL_POINTER                            (IVIC_ERROR_BASE + 0x0058)
#define AGMD2_ERROR_UNEXPECTED_RESPONSE                     (IVIC_ERROR_BASE + 0x0059)
#define AGMD2_ERROR_FILE_NOT_FOUND                          (IVIC_ERROR_BASE + 0x005B)
#define AGMD2_ERROR_INVALID_FILE_FORMAT                     (IVIC_ERROR_BASE + 0x005C)
#define AGMD2_ERROR_STATUS_NOT_AVAILABLE                    (IVIC_ERROR_BASE + 0x005D)
#define AGMD2_ERROR_ID_QUERY_FAILED                         (IVIC_ERROR_BASE + 0x005E)
#define AGMD2_ERROR_RESET_FAILED                            (IVIC_ERROR_BASE + 0x005F)
#define AGMD2_ERROR_RESOURCE_UNKNOWN                        (IVIC_ERROR_BASE + 0x0060)
#define AGMD2_ERROR_ALREADY_INITIALIZED                     (IVIC_ERROR_BASE + 0x0061)
#define AGMD2_ERROR_CANNOT_CHANGE_SIMULATION_STATE          (IVIC_ERROR_BASE + 0x0062)
#define AGMD2_ERROR_INVALID_NUMBER_OF_LEVELS_IN_SELECTOR    (IVIC_ERROR_BASE + 0x0063)
#define AGMD2_ERROR_INVALID_RANGE_IN_SELECTOR               (IVIC_ERROR_BASE + 0x0064)
#define AGMD2_ERROR_UNKOWN_NAME_IN_SELECTOR                 (IVIC_ERROR_BASE + 0x0065)
#define AGMD2_ERROR_BADLY_FORMED_SELECTOR                   (IVIC_ERROR_BASE + 0x0066)
#define AGMD2_ERROR_UNKNOWN_PHYSICAL_IDENTIFIER             (IVIC_ERROR_BASE + 0x0067)
#define AGMD2_ERROR_INVALID_ATTRIBUTE                       (IVIC_ERROR_BASE + 0x000C)
#define AGMD2_ERROR_TYPES_DO_NOT_MATCH                      (IVIC_ERROR_BASE + 0x0015)
#define AGMD2_ERROR_IVI_ATTR_NOT_WRITABLE                   (IVIC_ERROR_BASE + 0x000D)
#define AGMD2_ERROR_IVI_ATTR_NOT_READABLE                   (IVIC_ERROR_BASE + 0x000E)
#define AGMD2_ERROR_INVALID_SESSION_HANDLE                  (IVIC_ERROR_BASE + 0x1190)



#define AGMD2_SUCCESS                                       0
#define AGMD2_WARN_NSUP_ID_QUERY                            (IVIC_WARN_BASE + 0x0065)
#define AGMD2_WARN_NSUP_RESET                               (IVIC_WARN_BASE + 0x0066)
#define AGMD2_WARN_NSUP_SELF_TEST                           (IVIC_WARN_BASE + 0x0067)
#define AGMD2_WARN_NSUP_ERROR_QUERY                         (IVIC_WARN_BASE + 0x0068)
#define AGMD2_WARN_NSUP_REV_QUERY                           (IVIC_WARN_BASE + 0x0069)



#define AGMD2_ERROR_IO_GENERAL                              (IVIC_SPECIFIC_ERROR_BASE + 0x0214)
#define AGMD2_ERROR_IO_TIMEOUT                              (IVIC_SPECIFIC_ERROR_BASE + 0x0215)
#define AGMD2_ERROR_MODEL_NOT_SUPPORTED                     (IVIC_SPECIFIC_ERROR_BASE + 0x0216)
#define AGMD2_ERROR_PERSONALITY_NOT_ACTIVE                  (IVIC_SPECIFIC_ERROR_BASE + 0x0211)
#define AGMD2_ERROR_PERSONALITY_NOT_LICENSED                (IVIC_SPECIFIC_ERROR_BASE + 0x0213)
#define AGMD2_ERROR_PERSONALITY_NOT_INSTALLED               (IVIC_SPECIFIC_ERROR_BASE + 0x0212)
#define AGMD2_ERROR_CHANNEL_NOT_ENABLED                     (IVIC_CLASS_ERROR_BASE + 0x0001)
#define AGMD2_ERROR_MAX_TIME_EXCEEDED                       (IVIC_CLASS_ERROR_BASE + 0x0002)
#define AGMD2_ERROR_TRIGGER_NOT_SOFTWARE                    (IVIC_CROSS_CLASS_ERROR_BASE + 0x0001)
#define AGMD2_ERROR_ARM_NOT_SOFTWARE                        (IVIC_CLASS_ERROR_BASE + 0x0003)
#define AGMD2_ERROR_INCOMPATIBLE_FETCH                      (IVIC_CLASS_ERROR_BASE + 0x0004)
#define AGMD2_ERROR_SIMULATION_NOT_IMPLEMENTED              (IVIC_SPECIFIC_ERROR_BASE + 0x0001)
#define AGMD2_ERROR_NO_DATA_AVAILABLE                       (IVIC_SPECIFIC_ERROR_BASE + 0x0002)
#define AGMD2_ERROR_ACQUISITION_RUNNING                     (IVIC_SPECIFIC_ERROR_BASE + 0x0003)
#define AGMD2_ERROR_INSTRUMENT_IDLE                         (IVIC_SPECIFIC_ERROR_BASE + 0x0004)
#define AGMD2_ERROR_PRIVATE_ACCESS_DENIED                   (IVIC_SPECIFIC_ERROR_BASE + 0x0005)
#define AGMD2_ERROR_FIRMWARE_NOT_SUPPORTED                  (IVIC_SPECIFIC_ERROR_BASE + 0x0006)
#define AGMD2_ERROR_NOT_SUPPORTED_IN_CURRENT_STATE          (IVIC_SPECIFIC_ERROR_BASE + 0x0007)
#define AGMD2_ERROR_ADDITIONAL_POWER_NOT_CONNECTED          (IVIC_SPECIFIC_ERROR_BASE + 0x0008)
#define AGMD2_ERROR_CALIBRATION_REQUIRED                    (IVIC_SPECIFIC_ERROR_BASE + 0x0009)
#define AGMD2_ERROR_NOT_APPLICABLE                          (IVIC_SPECIFIC_ERROR_BASE + 0x000A)
#define AGMD2_ERROR_MODULE_OPTION_REQUIRED                  (IVIC_SPECIFIC_ERROR_BASE + 0x000B)
#define AGMD2_ERROR_STREAM_OVERFLOW                         (IVIC_SPECIFIC_ERROR_BASE + 0x000C)
#define AGMD2_ERROR_ADC_OVERRANGE                           (IVIC_SPECIFIC_ERROR_BASE + 0x000D)




/****************************************************************************
 *---------------------------- End Include File ----------------------------*
 ****************************************************************************/
#if defined(__cplusplus) || defined(__cplusplus__)
}
#endif
#endif // __AGMD2_HEADER
