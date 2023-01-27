#ifndef STABILIZATION_H_
#define STABILIZATION_H_

#include "../time.hpp"
#include "SensorProcessor.hpp"
#include "../Position.hpp"

class Stabilization
{
    public:
        time CalculateTimeOfAct(const Position rotation, int speed);
        int ActuateTrimTab(time timeOfAct);
        Position CalculateDeltaRotation(const Position& previousPos, const Position& currentPos, const time& previousTime);
        

}


#endif