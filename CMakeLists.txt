cmake_minimum_required(VERSION 2.6.4)
project(CFE_IMU_LIB C)

include_directories(fsw/public_inc)
include_directories(fsw/src)

include_directories(${i2c_lib_MISSION_DIR}/fsw/public_inc)

aux_source_directory(fsw/src LIB_SRC_FILES)

# Create the app module
add_cfe_app(imu_lib ${LIB_SRC_FILES})



