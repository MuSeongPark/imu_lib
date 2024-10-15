

/*
*
* This is library header file for IMU Sensor (ICM-20689)
*
* Developer: Museong Park
*
*
*/


#ifndef IMU_LIB_H
#define IMU_LIB_H

#include <stdint.h>
#include "imu_lib.h"

typedef struct Gyro_Vector
{
    float x;
    float y;
    float z;

}Gyro_Vector;

int32_t IMU_LibInit(void);
Gyro_Vector GetGyroData(void);
float GetTempData(void);

#endif