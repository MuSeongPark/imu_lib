/*
*
* This is library source file for IMU Sensor (ICM-20689)
* 
* Developer: Museong Park
*
*
*/


#define SELF_TEST_X_GYRO 0x00
#define SELF_TEST_Y_GYRO 0x01
#define SELF_TEST_Z_GYRO 0x02
#define SELF_TEST_X_ACCEL 0x0D
#define SELF_TEST_Y_ACCEL 0x0E
#define SELF_TEST_Z_ACCEL 0x0F

#define XG_OFFS_USRH 0x13
#define XG_OFFS_USRL 0x14
#define YG_OFFS_USRH 0x15
#define YG_OFFS_USRL 0x16
#define ZG_OFFS_USRH 0x17
#define ZG_OFFS_USRL 0x18

#define SMPLRT_DIV 0x19
#define CONFIG 0x1A
#define GYRO_CONFIG 0x1B
#define ACCEL_CONFIG 0x1C
#define ACCEL_CONFIG_2 0x1D
#define LP_MODE_CFG 0x1E
#define ACCEL_WOM_THR 0x1F
#define FIFO_EN 0x23
#define FSYNC_INT 0x36
#define INT_PIN_CFG 0x37
#define INT_ENABLE 0x38
#define DMP_INT_STATUS 0x39
#define INT_STATUS 0x3A

#define ACCEL_XOUT_H 0x3B
#define ACCEL_XOUT_L 0x3C
#define ACCEL_YOUT_H 0x3D
#define ACCEL_YOUT_L 0x3E
#define ACCEL_ZOUT_H 0x3F
#define ACCEL_ZOUT_L 0x40

#define TEMP_OUT_H 0x41
#define TEMP_OUT_L 0x42

#define GYRO_XOUT_H 0x43
#define GYRO_XOUT_L 0x44
#define GYRO_YOUT_H 0x45
#define GYRO_YOUT_L 0x46
#define GYRO_ZOUT_H 0x47
#define GYRO_ZOUT_L 0x48

#define SIGNAL_PATH_RESET 0x68
#define ACCEL_INTEL_CTRL 0x69
#define USER_CTRL 0x6A
#define PWR_MGMT_1 0x6B
#define PWR_MGMT_2 0x6C

#define FIFO_COUNTH 0x72
#define FIFO_COUNTL 0x73
#define FIFO_R_W 0x74
#define WHO_AM_I 0x75

#define XA_OFFSET_H 0x77
#define XA_OFFSET_L 0x78
#define YA_OFFSET_H 0x7A
#define YA_OFFSET_L 0x7B
#define ZA_OFFSET_H 0x7D
#define ZA_OFFSET_L 0x7E

#define ADDRES 0x68 //this is depend on the device env.

#include "cfe.h"
#include <wiringPi.h>
#include <errno.h>

int32 IMU_LibInit()
{
    int32 fd = wiringPiI2CSetup(ADDRES);
    if(fd < 0)
    {
        OS_printf("Error: I2C Device Setup for IMU Sensor %s\n", errno);
        return -1;
    }


    return CFE_SUCCESS;
}


int32 IMU_HWInit()
{
    int32 fd = wiringPiI2CSetup(ADDRES);
    if(fd < 0)
    {
        OS_printf("Error: I2C Device Setup for IMU Sensor %s\n", errno);
        return -1;
    }

    int32 whoami = wiringPiI2CReadReg8(fd, WHO_AM_I);
    if(whoami != 0x98)


    return CFE_SUCCESS;

}