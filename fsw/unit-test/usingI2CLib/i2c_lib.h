#ifndef I2C_LIB_H
#define I2C_LIB_H

#include "i2c_lib.h"
#include <stdint.h> //int32_t

int32_t I2C_DeviceInit(uint8_t adapter_num, uint8_t devAddr);
uint8_t I2C_ReadReg8(int32_t fd, uint8_t regAddr);
int32_t I2C_WriteReg8(int32_t fd, uint8_t regAddr, uint8_t value);

uint8_t I2C_Read8(int32_t fd, uint8_t reg);
int32_t I2C_Write8(int32_t fd, uint8_t reg, uint8_t data);

int32_t I2C_Read(int32_t fd, uint8_t reg, void* data, size_t len);
int32_t I2C_Write(int32_t fd, uint8_t reg, uint8_t* data, size_t len);

#endif