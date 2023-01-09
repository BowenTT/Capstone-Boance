#ifndef _SENSOR_PROCESSOR_H
#define _SENSOR_PROCESSOR_H

#include "../libraries/LSM6DSL-Arduino/src/LSM6DSL.h"
#include "../POSITION.hpp"

class SensorProcessor
{
    public:
        SensorProcessor(LSM6DSL sensor){}
        ~SensorProcessor(){}

        void Calibrate(int nrOfSamples, int accelSens);

        Position GetFilteredRotation();
        
        float GetLastAccelReadings(int nrOfReadings);
        Position GetLastRotationReadings(int nrOfReadings);

    private:

        position lastRotation;
        unsigned long currentTime;
        unsigned long previousTime;
        unsigned long elapsedTime;

}