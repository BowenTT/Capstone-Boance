#ifndef _SENSOR_PROCESSOR_H
#define _SENSOR_PROCESSOR_H

#include "../interfaces/IAccelerometer.hpp"
#include "../interfaces/IGyroscope.hpp"
#include "../libraries/LSM6DSL-Arduino/src/LSM6DSL.h"


class SensorProcessor
{
    public:
        SensorProcessor(IAccelerometer& accel, IGyroscope& gyro);
        ~SensorProcessor(){}

        void Calibrate(int nrOfSamples);

        Position GetFilteredRotation();
        
        Position GetLastAccelReadings(unsigned long ms);
        Position GetLastRotationReadings(unsigned long ms);

    private:

        IAccelerometer& accelerometer;
        IGyroscope& gyroscope;

        Position lastRotation;
        unsigned long currentTime;
        unsigned long previousTime;
        unsigned long elapsedTime;

};

#endif