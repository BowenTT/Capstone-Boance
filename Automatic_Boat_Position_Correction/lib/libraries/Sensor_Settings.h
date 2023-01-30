#ifndef SENSOR_SETTINGS_H_
#define SENSOR_SETTINGS_H_

//Accelerometer
#define accelEnabled            1
#define accelODROff             1
#define accelRange              16
#define accelSampleRate         416
#define accelBandWidth          100
#define accelFifoEnabled        1
#define accelFifoDecimation     1

//Gyroscope
#define gyroEnabled             1
#define gyroRange               2000
#define gyroSampleRate          416
#define gyroFifoEnabled         1
#define gyroFifoDecimation      1

//TODO: Later implementation of configurable settings (speed, weight of boat, etc)
// #define boat_speed ...
// #define boat_weight ...
// #define ...?

#endif