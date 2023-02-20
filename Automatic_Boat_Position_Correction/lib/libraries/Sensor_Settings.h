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

#define TRIMTAB_MAX_ANGLE       45
#define ROLL_THRESHOLD          15 // Degrees threshold which the roll angle needs to exceed before actuation of trim tabs
#define DEFAULT_ACTUATION_TIME  500 // ms
#define DEFAULT_ACTUATION_ANGLE 5 // degrees
#define ROLL_CHANGE_THRESHOLD   5 // Degrees the boat should change after each actuation to assume the boat will balance itself out again
#define FUZZY_LOGIC_RESOLUTION  10
#define MAX_ACTUATION_TIME      5000 // ms
#endif