#include "Stabilization.h"

time Stabilization::CalculateTimeOfAct(const Position& rotation, int speed)
{
    return {0,0}
}

int Stabilization::ActuateTrimTab(time timeOfAct)
{
    return 0;
}

Position Stabilization::CalculateDeltaRotation(const Position& previousPos, const Position& currentPos, const time& previousTime)
{
    return {0,0,0};
}