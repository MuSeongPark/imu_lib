SRCS = main.c imu_lib.c
OBJS = $(SRCS:.c=.o)

TARGET = main
$(TARGET): $(OBJS)
	gcc -o $(TARGET) $(OBJS) -lwiringPi


main.o: main.c imu_lib.h
	gcc -c main.c

imu_lib.o: imu_lib.c imu_lib.h
	gcc -c imu_lib.c

clean:
	rm -f $(OBJS) $(TARGET)