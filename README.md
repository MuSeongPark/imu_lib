# core Flight System (cFS) IMU Library

## Introduction
본 cFS Library는 구현된 I2C Library를 바탕으로 ICM-20602 IMU 센서가 측정한 온도값과 자이로값을 읽어서 계산하는 함수를 제공한다.

```C

int32 IMU_HWInit(void); //IMU 센서 초기화
int32 IMU_LibInit(void); //라이브러리 초기화
Gyro_Vector GetGyroData(void); //자이로 값 읽어오기
float GetTempData(void); //온도 값 읽어오기

```


## Required Software
cFS Framework (cFE, OSAL, PSP)를 요구합니다.<br>
cFE, OSAL, PSP를 포함한 통합 번들은 다음을 참고하세요.<br>
[core Flight System](https://github.com/nasa/cFS)


## About cFS
cFS는 나사 고다드 우주 비행 센터(NASA Goddard Space Flight Center)에서 개발된 소프트웨어 프레임 워크로, 기본적으로 인공위성의 비행 소프트웨어(FSW) 또는 다른 임베디드 시스템 계열에 사용이 가능합니다.<br>
cFS는 재사용 가능한 소프트웨어 프레임워크로, 여러 애플리케이션과 cFE, 추상화계층 등을 포함하고 있습니다.<br>
cFS와 관련된 상세 설명은 다음을 참고하세요.<br>
[Details about cFS](http://cfs.gsfc.nasa.gov)