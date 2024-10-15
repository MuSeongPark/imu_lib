SRCS = main.c imu_lib.c i2c_lib.c
OBJS = $(SRCS:.c=.o)

TARGET = main
$(TARGET): $(OBJS)
	gcc -o $(TARGET) $(OBJS)


main.o: main.c imu_lib.h
	gcc -c main.c

imu_lib.o: imu_lib.c imu_lib.h i2c_lib.h
	gcc -c imu_lib.c

i2c_lib.o: i2c_lib.c i2c_lib.h
	gcc -c i2c_lib.c

clean:
	rm -f $(OBJS) $(TARGET)