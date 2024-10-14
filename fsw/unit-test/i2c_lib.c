#include <linux/i2c-dev.h>
#include <linux/i2c.h>
#include <linux/types.h>

#include <sys/ioctl.h>
#include <asm/ioctl.h>


#include <stdio.h>
#include <errno.h>
#include <fcntl.h>

#include "i2c_lib.h"


int32_t i2cDeviceInit(uint8_t adapter_num, uint8_t devAddr)
{
    char dev[20];

    sprintf(dev, "/dev/i2c-%d", adapter_num);

    int32_t fd = open(dev, O_RDWR);
    if(fd < 0)
    {
        printf("Error: Can't open i2c device %s, %s\n", *dev, errno);
        return -1;
    }

    if(ioctl(fd, I2C_SLAVE, devAddr) < 0)
    {
        printf("Error: Can't access to i2c device address %x, %s\n", devAddr, errno);
        return -1;
    }
    return fd;
}


uint8_t i2cReadReg8(int32_t fd, uint8_t regAddr)
{
    union i2c_smbus_data data;
    struct i2c_smbus_ioctl_data args; //This is defined at linux/i2c-dev.h

    args.read_write = I2C_SMBUS_READ;
    args.command = regAddr;
    args.size = I2C_SMBUS_BYTE_DATA; // 1byte
    args.data = &data;

    if (ioctl(fd, I2C_SMBUS, &args) < 0) { return -1; }

    return data.byte & 0xFF;
}


int8_t i2CWriteReg8(int32_t fd, uint8_t regAddr, int8_t data)
{

}



