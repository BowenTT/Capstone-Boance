#include "Stabilization.hpp"

double mapf(double x, double in_min, double in_max, double out_min, double out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

// Calculates the time needed to actuate the trim tab to balance the boat using its current roll angle
// TODO:: Implement speed of the boat factor 
double Stabilization::CalculateTimeOfAct(const Position& rotation, int speed)
{
    double fuzzyAngle = mapf(abs(rotation.y), 0, 90, 0, 1);
    double timeOfAct = fuzzyAngle * DEFAULT_ACTUATION_TIME * FUZZY_LOGIC_RESOLUTION; //See Sensor_Settings.h
    return timeOfAct;
}


//Actuates the (servo) trim tab given the time of act, because the servo can only be written to a certain angle,
//The decision had been made now to map the actuation time to angles given, so max actuation time of 5 seconds will result in max angle of the trim tab
double Stabilization::ActuateTrimTab(PWMServo& trimtab, double timeOfAct)
{
    double angle = mapf(timeOfAct, 0, MAX_ACTUATION_TIME, 0, TRIMTAB_MAX_ANGLE);
    trimtab.write(angle);
    return angle;
}

Position Stabilization::CalculateDeltaRotation(const Position& previousPos, const Position& currentPos)
{
    return previousPos - currentPos;
}