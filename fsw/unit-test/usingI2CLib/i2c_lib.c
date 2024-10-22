#include <linux/i2c-dev.h> //I2C_SLAVE flag
#include <linux/i2c.h>
#include <linux/types.h>

#include <sys/ioctl.h> //ioctl


#include <stdio.h> //snprintf etc.
#include <errno.h>
#include <fcntl.h> //flags like O_RDWR
#include <string.h>
#include <stdint.h> //int32_t
#include <unistd.h> //open, read, write

#include "i2c_lib.h"


int32_t I2C_DeviceInit(uint8_t adapter_num, uint8_t devAddr)
{
    /*
    adapter_num: /dev/i2c-(THIS NUMBER)
    devAddr: device address like 0x68
    */
    char dev[15];

    sprintf(dev, "/dev/i2c-%d", adapter_num);

    int32_t fd = open(dev, O_RDWR);
    if(fd < 0)
    {
        fprintf(stderr, "Error: Can't open i2c device %s, %s\n", dev, strerror(errno));
        return -1;
    }

    if(ioctl(fd, I2C_SLAVE, devAddr) < 0)
    {
        fprintf(stderr, "Error: Can't access to i2c device address %x, %s\n", devAddr, strerror(errno));
        return -1;
    }
    return fd;
}


uint8_t I2C_ReadReg8(int32_t fd, uint8_t regAddr)
{
    /*
    fd: file descripter
    regAddr: Register Address that you want to read
    */
    union i2c_smbus_data data;
    struct i2c_smbus_ioctl_data args; //This is defined at linux/i2c-dev.h

    args.read_write = I2C_SMBUS_READ;
    args.command = regAddr;
    args.size = I2C_SMBUS_BYTE_DATA; // 1byte
    args.data = &data;

    if (ioctl(fd, I2C_SMBUS, &args) < 0) { return -1; }

    return data.byte & 0xFF;
}


int32_t I2C_WriteReg8(int32_t fd, uint8_t regAddr, uint8_t value)
{
    /*
    fd: file descripter
    regAddr: Register Address that you want to write on
    value: The value to write in the register
    */
    union i2c_smbus_data data;
    struct i2c_smbus_ioctl_data args;
    data.byte = value;

    args.read_write = I2C_SMBUS_WRITE;
    args.command = regAddr;
    args.size = I2C_SMBUS_BYTE_DATA; // 1byte
    args.data = &data;

    if (ioctl(fd, I2C_SMBUS, &args) < 0) { return -1; }

    return 0;
    
}



uint8_t I2C_Read8(int32_t fd, uint8_t reg)
{
    /*I2C Read 1byte using write and read*/
    uint8_t data;
    if(write(fd, &reg, 1) < 0)
    {
        fprintf(stderr, "Error: Read 1 Byte from I2C %s\n", strerror(errno));
        return -1;
    }
    if(read(fd, &data, 1) < 0)
    {
        fprintf(stderr, "Error: Read 1 Byte from I2C %s\n", strerror(errno));
        return -1;
    }

    return data;

}

int32_t I2C_Write8(int32_t fd, uint8_t reg, uint8_t data)
{
    /*I2C write 1byte using write and read*/
    uint8_t buff[2] = {reg, data};

    if(write(fd, &buff, 2) < 0)
    {
        fprintf(stderr, "Error: Read 1 Byte from I2C %s\n", strerror(errno));
        return -1;
    }

    return 0;

}


int32_t I2C_Read(int32_t fd, uint8_t reg, void* data, size_t len)
{
    /*I2C Read using write and read*/
    //uint8_t* data = (uint8_t *) data;
    
    if(write(fd, &reg, 1) < 0)
    {
        fprintf(stderr, "Error: I2C Read, Can't access to register %s\n", strerror(errno));
        return -1;
    }
    if(read(fd, data, len) < 0)
    {
        fprintf(stderr, "Error: I2C Read, Can't read register value %s\n", strerror(errno));
        return -1;
    }

    return 0;

}



int32_t I2C_Write(int32_t fd, uint8_t reg, uint8_t* data, size_t len)
{
    //I2C Write using write and read
    uint8_t data_buff[len+1];
    data_buff[0] = reg;

    for(int i = 1; i<len+1; i++)
    {
        data_buff[i] = *(data++); 
    }
    if(write(fd, &reg, len+1) < 0)
    {
        fprintf(stderr, "Error: Read 1 Byte from I2C %s\n", strerror(errno));
        return -1;
    }

    return 0;

}

