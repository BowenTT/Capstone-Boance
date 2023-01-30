#ifndef STABILIZATION_H_
#define STABILIZATION_H_

#include "../my_time.hpp"
#include "SensorProcessor.hpp"
#include "../Position.hpp"

class Stabilization
{
    public:
        my_time CalculateTimeOfAct(const Position& rotation, int speed);
        int ActuateTrimTab(my_time timeOfAct);
        Position CalculateDeltaRotation(const Position& previousPos, const Position& currentPos, const my_time& previousTime);
        

};

#endif