#ifndef I2C_LIB_H
#define I2C_LIB_H

#include <stdint.h>
#include "i2c_lib.h"

int32_t i2cDeviceInit(uint8_t adapter_num, uint8_t devAddr);
int32_t i2cReadReg8(int32_t fd, uint8_t regAddr);


#endif