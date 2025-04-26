#ifndef INC_ADXL345_H_
#define INC_ADXL345_H_

#include "main.h"

/** 
 * @defgroup Device_Address Device I2C Address
 * @{
 */
#define ADXL345_DEVICE_ADDRESS 0xA6
/** @} */

/** 
 * @defgroup Register_Definitions ADXL345 Register Map
 * @{
 */
#define DEVID           0x00
#define THRESH_TAP      0x1D
#define OFSX            0x1E
#define OFSY            0x1F
#define OFSZ            0x20
#define DUR             0x21
#define LATENT          0x22
#define WINDOW          0x23
#define THRESH_ACT      0x24
#define THRESH_INACT    0x25
#define TIME_INACT      0x26
#define ACT_INACT_CTL   0x27
#define THRESH_FF       0x28
#define TIME_FF         0x29
#define TAP_AXES        0x2A
#define ACT_TAP_STATUS  0x2B
#define BW_RATE         0x2C
#define POWER_CTL       0x2D
#define INT_ENABLE      0x2E
#define INT_MAP         0x2F
#define INT_SOURCE      0x30
#define DATA_FORMAT     0x31
#define DATAX0          0x32
#define DATAX1          0x33
#define DATAY0          0x34
#define DATAY1          0x35
#define DATAZ0          0x36
#define DATAZ1          0x37
#define FIFO_CTL        0x38
#define FIFO_STATUS     0x39
/** @} */

/**
 * @brief Timeout value for I2C operations in milliseconds
 */
#define TIMEOUT         1000

/** 
 * @defgroup Axis_Definitions Axis Register Addresses
 * @{
 */
#define X               DATAX0
#define Y               DATAY0
#define Z               DATAZ0
/** @} */

/**
 * @defgroup Scale_Factors Scale factors for different measurement ranges
 * @{
 */
#define SCALE_FACTOR_2G    (float)1/256.0
#define SCALE_FACTOR_4G    (float)1/128.0
#define SCALE_FACTOR_8G    (float)1/64.0
#define SCALE_FACTOR_16G   (float)1/32.0
/** @} */

/**
 * @defgroup Wakeup_Rates Wakeup Rates Configuration
 * @{
 */
#define WAKEUP_8HZ      0x00
#define WAKEUP_4HZ      0x01
#define WAKEUP_2HZ      0x02
#define WAKEUP_1HZ      0x03
/** @} */

/**
 * @defgroup G_Ranges G-Force Range Settings
 * @{
 */
#define RANGE_2G        0x00
#define RANGE_4G        0x01
#define RANGE_8G        0x02
#define RANGE_16G       0x03
/** @} */

/**
 * @defgroup Bandwidth_Rates Output Data Rate and Bandwidth Settings
 * @{
 */
#define BANDWIDTH_RATE_1600    0x0F
#define BANDWIDTH_RATE_800     0x0E
#define BANDWIDTH_RATE_400     0x0D
#define BANDWIDTH_RATE_200     0x0C
#define BANDWIDTH_RATE_100     0x0B
#define BANDWIDTH_RATE_50      0x0A
#define BANDWIDTH_RATE_25      0x09
#define BANDWIDTH_RATE_12_5    0x08
#define BANDWIDTH_RATE_6_25    0x07
#define BANDWIDTH_RATE_3_13    0x06
#define BANDWIDTH_RATE_1_56    0x05
#define BANDWIDTH_RATE_0_78    0x04
#define BANDWIDTH_RATE_0_39    0x03
#define BANDWIDTH_RATE_0_20    0x02
#define BANDWIDTH_RATE_0_10    0x01
#define BANDWIDTH_RATE_0_05    0x00
/** @} */

/**
 * @brief Enumeration for ADXL345 Read Operation Status
 */
typedef enum {
    READ_FAIL = 0,   /**< Read operation failed */
    READ_SUCCESS = 1 /**< Read operation succeeded */
} ADXL345ReadStatus;

/**
 * @brief Enumeration for ADXL345 Write Operation Status
 */
typedef enum {
    Write_FAIL = 0,   /**< Write operation failed */
    Write_SUCCESS = 1 /**< Write operation succeeded */
} ADXL345WriteStatus;

/**
 * @brief Enumeration for ADXL345 Initialization Status
 */
typedef enum {
    INIT_FAIL = 0,   /**< Initialization failed */
    INIT_SUCCESS = 1 /**< Initialization succeeded */
} ADXL345InitStatus;

/**
 * @brief Structure representing the POWER_CTL register configuration
 */
typedef struct {
    uint8_t Wakeup: 2;    /**< Wakeup frequency selection */
    uint8_t Sleep: 1;     /**< Sleep mode enable/disable */
    uint8_t Measure: 1;   /**< Measurement mode enable */
    uint8_t AUTO_SLEEP: 1;/**< Auto-sleep mode enable */
    uint8_t Link: 1;      /**< Link activity enable */
    uint8_t Reserved: 2;  /**< Reserved bits */
} PowerControlRegister_t;

/**
 * @brief Structure representing the DATA_FORMAT register configuration
 */
typedef struct {
    uint8_t Range: 2;      /**< G-range selection */
    uint8_t Justify: 1;    /**< Data justification (left/right) */
    uint8_t FULL_RES: 1;   /**< Full resolution mode */
    uint8_t Reserved: 1;   /**< Reserved bit */
    uint8_t INT_INVERT: 1; /**< Interrupt active level (high/low) */
    uint8_t SPI: 1;        /**< SPI mode selection */
    uint8_t SELF_TEST: 1;  /**< Self-test enable */
} DataFormatRegister_t;

/**
 * @brief Structure representing the BW_RATE register configuration
 */
typedef struct {
    uint8_t Range: 4;      /**< Output data rate setting */
    uint8_t LOW_POWER: 1;  /**< Low power mode enable */
    uint8_t Reserved: 3;   /**< Reserved bits */
} BWRATERegister_t;

/* Function Prototypes */
int ADXL345_ScanDeviceID(I2C_HandleTypeDef *hi2cx);
ADXL345InitStatus ADXL345_Init(I2C_HandleTypeDef *hi2cx);
int16_t ADXL345_getAxisValue(I2C_HandleTypeDef *hi2cx, uint8_t axis);
float ADXL345_getGValue(I2C_HandleTypeDef *hi2cx, uint8_t axis, float scaleFactor);

#endif /* INC_ADXL345_H_ */
