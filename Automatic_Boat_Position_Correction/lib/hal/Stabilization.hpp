#ifndef STABILIZATION_H_
#define STABILIZATION_H_

#include "SensorProcessor.hpp"
#include "../Position.hpp"
#include <PWMServo.h>
#include <Sensor_Settings.h>

class Stabilization
{
    public:
        static double CalculateTimeOfAct(const Position& rotation, int speed);
        static double ActuateTrimTab(PWMServo& trimtab, double timeOfAct, bool isLeft);
        static Position CalculateDeltaRotation(const Position& previousPos, const Position& currentPos);
    
    private:
        unsigned long current_time = 0;
        unsigned long previous_time = 0;

};

#endif