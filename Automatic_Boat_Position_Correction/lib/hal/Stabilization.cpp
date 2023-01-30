#include "Stabilization.hpp"

my_time Stabilization::CalculateTimeOfAct(const Position& rotation, int speed)
{
    return {0,0};
}

int Stabilization::ActuateTrimTab(my_time timeOfAct)
{
    return 0;
}

Position Stabilization::CalculateDeltaRotation(const Position& previousPos, const Position& currentPos, const my_time& previousTime)
{
    return {0,0,0};
}