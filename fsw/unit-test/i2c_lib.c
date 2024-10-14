#include <linux/i2c-dev.h>
#include <i2c/smbus.h>
#include <sys/ioctl.h>
#include <stdint.h>
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>


int main(void)
{
    
    int32_t file;
    int32_t adapter_nr = 1;
    int32_t addr = 0x40; //I2C address
    char filename[20];


    snprintf(filename, 19, "/dev/i2c-%d", adapter_nr);
    file = open(filename, O_RDWR);
    if(file < 0)
    {
        printf("Error: Can't open i2c device %s\n", errno);
        return -1;
    }

    if(ioctl(file, I2C_SLAVE, addr) < 0)
    {
        printf("Error: Can't access to address %x, %s\n", addr, errno);
        return -1;
    }

    __u8 reg = 0x10; /* Device register to access */
    int8_t res;
    char buf[10];

    /* Using SMBus commands */
    res = i2c_smbus_read_word_data(file, reg);
    if(res < 0)
    {
        printf("Error: I2C Transactrion is failed! %s\n", errno);
    }
    printf("Register Value: %x (Reg Address: %x)\n", res, reg);


    return 0;




}

