#include "adxl345.h"

/**
  * @brief  Scans the I2C bus to find the address of the ADXL345 device.
  * @param  hi2cx: Pointer to the I2C handle structure.
  * @retval Found device address (0-255) or -1 if no device is found.
  */
int ADXL345_ScanDeviceID(I2C_HandleTypeDef *hi2cx){
    for (int addressX = 0; addressX <= 255; addressX++) {
        if (HAL_I2C_IsDeviceReady(hi2cx, addressX, 1, 10) == HAL_OK) {
            return addressX;
        }
    }
    return -1;
}

/**
  * @brief  Reads data from a specific register of the ADXL345 (internal use).
  * @param  hi2cx: Pointer to the I2C handle structure.
  * @param  registerAddress: Address of the register to be read.
  * @param  sizeofData: Number of bytes to read.
  * @param  dataBuffer: Pointer to the buffer where read data will be stored.
  * @retval Read operation status (READ_SUCCESS or READ_FAIL).
  */
static ADXL345ReadStatus ADXL345_ReadRegisterData(I2C_HandleTypeDef *hi2cx, uint16_t registerAddress, uint16_t sizeofData, uint8_t *dataBuffer){
    if (HAL_I2C_Mem_Read(hi2cx, ADXL345_DEVICE_ADDRESS, registerAddress, 1, dataBuffer, sizeofData, TIMEOUT) == HAL_OK) {
        return READ_SUCCESS;
    }
    return READ_FAIL;
}

/**
  * @brief  Writes data to a specific register of the ADXL345 (internal use).
  * @param  hi2cx: Pointer to the I2C handle structure.
  * @param  registerAddress: Address of the register to write to.
  * @param  value: Value to be written into the register.
  * @retval Write operation status (Write_SUCCESS or Write_FAIL).
  */
static ADXL345WriteStatus ADXL345_WriteRegisterData(I2C_HandleTypeDef *hi2cx, uint16_t registerAddress, uint16_t value){
    uint8_t data[2] = {0};
    data[0] = registerAddress;
    data[1] = value;

    if (HAL_I2C_Master_Transmit(hi2cx, ADXL345_DEVICE_ADDRESS, data, sizeof(data), TIMEOUT) == HAL_OK) {
        return Write_SUCCESS;
    }
    return Write_FAIL;
}

/**
  * @brief  Initializes the ADXL345 sensor with default configurations.
  * @param  hi2cx: Pointer to the I2C handle structure.
  * @retval Initialization status (INIT_SUCCESS or INIT_FAIL).
  */
ADXL345InitStatus ADXL345_Init(I2C_HandleTypeDef *hi2cx){
    uint8_t dataBuffer = 0;
    ADXL345_ReadRegisterData(hi2cx, DEVID, 1, &dataBuffer);

    if (dataBuffer != 0xE5) {
        return INIT_FAIL;
    }

    uint8_t tempReg = 0;

    PowerControlRegister_t powerControl = {0};

    powerControl.Wakeup = WAKEUP_8HZ;
    powerControl.Sleep = 0x00;
    powerControl.Measure = 0x01;
    powerControl.AUTO_SLEEP = 0x00;
    powerControl.Link = 0x00;
    powerControl.Reserved = 0x00;

    tempReg = *((uint8_t*)&powerControl);
    ADXL345_WriteRegisterData(hi2cx, POWER_CTL, tempReg);

    DataFormatRegister_t dataFormatControl = {0};
    dataFormatControl.Range = RANGE_4G;
    dataFormatControl.Justify = 0x00;
    dataFormatControl.FULL_RES = 0x00;
    dataFormatControl.Reserved = 0x00;
    dataFormatControl.INT_INVERT = 0x00;
    dataFormatControl.SPI = 0x00;
    dataFormatControl.SELF_TEST = 0x00;

    tempReg = *((uint8_t*)&dataFormatControl);
    ADXL345_WriteRegisterData(hi2cx, DATA_FORMAT, tempReg);

    BWRATERegister_t BWRATEControl = {0};
    BWRATEControl.Range = BANDWIDTH_RATE_800;
    BWRATEControl.LOW_POWER = 0x00;
    BWRATEControl.Reserved = 0x00;

    tempReg = *((uint8_t*)&BWRATEControl);
    ADXL345_WriteRegisterData(hi2cx, BW_RATE, tempReg);

    return INIT_SUCCESS;
}

/**
  * @brief  Reads raw acceleration data from the specified axis register.
  * @param  hi2cx: Pointer to the I2C handle structure.
  * @param  axis: Starting address of the axis data (e.g., DATAX0, DATAY0, DATAZ0).
  * @retval 16-bit signed raw acceleration value.
  */
int16_t ADXL345_getAxisValue(I2C_HandleTypeDef *hi2cx, uint8_t axis){
    uint8_t data[2] = {0};
    int16_t outputData = 0;

    ADXL345_ReadRegisterData(hi2cx, axis, 2, data);
    outputData = ((data[1] << 8) | data[0]);

    return outputData;
}

/**
  * @brief  Converts raw acceleration data to G-force value.
  * @param  hi2cx: Pointer to the I2C handle structure.
  * @param  axis: Starting address of the axis data.
  * @param  scaleFactor: Scale factor to convert raw data to G (depends on sensitivity setting).
  * @retval G-force value as a floating-point number.
  */
float ADXL345_getGValue(I2C_HandleTypeDef *hi2cx, uint8_t axis, float scaleFactor){
    int16_t outputData = 0;
    float gData = 0;

    outputData = ADXL345_getAxisValue(hi2cx, axis);
    gData = (float)(outputData * scaleFactor);

    return gData;
}
