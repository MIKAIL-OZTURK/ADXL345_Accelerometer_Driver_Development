# ADXL345 Accelerometer Driver Development (I2C)

This repository provides a lightweight and clean STM32 driver for the ADXL345 3-axis accelerometer, using the I2C communication protocol.

## 📚 Features
- Read acceleration data (X, Y, Z axes)
- Configure power control, data format, and bandwidth settings
- Scale raw data to g-units easily
- Easy to integrate with STM32 HAL library

## 📦 Folder Structure
- `Drivers/ADXL345/Inc/` : Header files
- `Drivers/ADXL345/Src/` : Source files
- `Examples/Basic_Read/` : Example project using the driver

## 🛠️ Requirements
- STM32F4 Series MCU (or compatible)
- STM32CubeIDE
- HAL Library enabled (especially I2C)

## 🚀 Quick Start
1. Initialize I2C Peripheral.
2. Call `ADXL345_Init(&hi2c1);`
3. Use `ADXL345_getGValue(&hi2c1, X, SCALE_FACTOR_4G);` to read axis data.

## 📜 License
This project is licensed under the MIT License - see the LICENSE file for details.
