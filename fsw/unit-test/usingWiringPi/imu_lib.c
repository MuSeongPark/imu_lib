/*
*
* This is library source file for IMU Sensor (ICM-20689)
* 
* Developer: Museong Park
*
*
*/


#define XG_OFFS_TC_H 0x04
#define XG_OFFS_TC_L 0x05
#define YG_OFFS_TC_H 0x07
#define YG_OFFS_TC_L 0x08
#define ZG_OFFS_TC_H 0x0A
#define ZG_OFFS_TC_L 0x0B

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
#define ACCEL_WOM_X_THR 0x20
#define ACCEL_WOM_Y_THR 0x21
#define ACCEL_WOM_Z_THR 0x22
#define FIFO_EN 0x23
#define FSYNC_INT 0x36
#define INT_PIN_CFG 0x37
#define INT_ENABLE 0x38
#define FIFO_WM_INT_STATUS 0x39
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

#define SELF_TEST_X_GYRO 0x50
#define SELF_TEST_Y_GYRO 0x51
#define SELF_TEST_Z_GYRO 0x52

#define FIFO_WM_TH1 0x60
#define FIFO_WM_TH2 0x61
#define SIGNAL_PATH_RESET 0x68
#define ACCEL_INTEL_CTRL 0x69
#define USER_CTRL 0x6A
#define PWR_MGMT_1 0x6B
#define PWR_MGMT_2 0x6C
#define I2C_IF 0x70
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

//Gyro Scale
#define GYRO_SCALE_250DPS (0 << 3)
#define GYRO_SCALE_500DPS (1 << 3)
#define GYRO_SCALE_1000DPS (2 << 3)
#define GYRO_SCALE_2000DPS (3 << 3)


#define ADDRESS 0x68 //this is depend on the device env.

#include <wiringPiI2C.h>
#include <errno.h>
#include <string.h>

#include "imu_lib.h"

int32_t IMU_HWInit(void);


int32_t IMU_LibInit(void)
{
    int32_t status = IMU_HWInit();
    if (status != 0) { return -1; }

    return 0;
}


int32_t IMU_HWInit(void)
{
    int32_t fd = wiringPiI2CSetup(ADDRESS);
    if(fd < 0) { return -1; }

    int32_t whoami = wiringPiI2CReadReg8(fd, WHO_AM_I);
    
    if(whoami != 0x12) //0x12
    {
        fprintf(stderr, "Error: who am i register value is not 0x12 %s\n", strerror(errno));
        return -1;
    }

    wiringPiI2CWriteReg8(fd, CONFIG, 0x00);
    wiringPiI2CWriteReg8(fd, GYRO_CONFIG, GYRO_SCALE_500DPS);
    wiringPiI2CWriteReg8(fd, PWR_MGMT_1, 0x01);
    wiringPiI2CWriteReg8(fd, PWR_MGMT_2, 0x38);
    
    return 0;

}


Gyro_Vector GetGyroData(void)
{
    Gyro_Vector gyroData;
    int32_t fd = wiringPiI2CSetup(ADDRESS);
    
    //_H: high bytes, _L:low bytes
    int16_t x_raw = (int16_t)(wiringPiI2CReadReg8(fd, GYRO_XOUT_L) | (wiringPiI2CReadReg8(fd, GYRO_XOUT_H) << 8));
    int16_t y_raw = (int16_t)(wiringPiI2CReadReg8(fd, GYRO_YOUT_L) | (wiringPiI2CReadReg8(fd, GYRO_YOUT_H) << 8));
    int16_t z_raw = (int16_t)(wiringPiI2CReadReg8(fd, GYRO_ZOUT_L) | (wiringPiI2CReadReg8(fd, GYRO_ZOUT_H) << 8));
    gyroData.x = (float)x_raw / 131.F;
    gyroData.y = (float)y_raw / 131.F;
    gyroData.z = (float)z_raw / 131.F;

    return gyroData;
}

float GetTempData(void)
{
    int32_t fd = wiringPiI2CSetup(ADDRESS);
    
    //_H: high bytes, _L:low bytes
    int16_t RawTempData = (int16_t)(wiringPiI2CReadReg8(fd, TEMP_OUT_L)) | (int16_t)(wiringPiI2CReadReg8(fd, TEMP_OUT_H) << 8);

    //Room Temp Offset: default:0, Sensitivity: 326.8
    float TempData = (RawTempData/326.8) + 25;


    return TempData;
}