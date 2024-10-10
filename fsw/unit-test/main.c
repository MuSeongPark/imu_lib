
#include "imu_lib.h"

#include <stdio.h>
#include <errno.h>
#include <unistd.h>


int main(void)
{
    if (IMU_LibInit() != 0) { return -1; }

    while (1)
    {
        Gyro_Vector Gyrodata = GetGyroData();
        float temperature = GetTempData();

        printf("Gyro | x: %f, y:%f, z:%f\n", Gyrodata.x, Gyrodata.y, Gyrodata.z);
        printf("Temperature: %f\n", temperature);

        sleep(1);
        
    }
    

    return 0;
}