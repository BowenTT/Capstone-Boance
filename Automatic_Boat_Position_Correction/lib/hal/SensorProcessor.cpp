#include "../hal/SensorProcessor.hpp"
#include <math.h>
#define RAD_TO_DEG 57.29578
#define PI 3.14159265358979323846

SensorProcessor::SensorProcessor(IAccelerometer& accel, IGyroscope& gyro)
:accelerometer(accel)
,gyroscope(gyro)
,lastRotation(Position{0,0,0})
,currentTime(millis())
,previousTime(0)
,elapsedTime(0)
{
}

/*
    Calibrates the offsets of the LSM6DSL Accelerometer + Gyroscope by taking nrOfSamples 
    Offset gets used to counteract the bias instability of the sensor
    Sensor should be placed on a flat surface for best results
*/
void SensorProcessor::Calibrate(int nrOfSamples, int accelSens)
{
    // Perhaps this is not needed, factory calibration might be enough
}

/*
    Returns the average of 'nrOfReadings' accelerometer readings
    Average is multiplied by ten for easier comparisons and visibility with plotting
*/
float SensorProcessor::GetLastAccelReadings(int nrOfReadings)
{
    //TODO
    return 0.0;
}

/* 
    Returns the average of 'nrOfReadings' gyroscope readings
    Return value = {x, y, z}
*/
Position SensorProcessor::GetLastRotationReadings(int nrOfReadings)
{
    //TODO
    return {0,0,0};
}

/*
    Gets the angular rotation of the sensor by first getting the roll and pitch from the accelerometer
    then it integrates the gyroscope data over time to get angular rotation from the gyryscope
    at last, a complementary filter is used to combined both datastreams for a more accurate representation
*/

Position SensorProcessor::GetAnglesFromGyro(float deltaTime)
{
    float DT = deltaTime;
    Position pos;
    Position angles;
    float[] rate;
    float angleX, angleY, angleX;
    pos = gyroscope.Read();
    rate[0] = pos.x * gyroscope.GetSensitivity();
    rate[1] = pos.y * gyroscope.GetSensitivity();
    rate[2] = pos.z * gyroscope.GetSensitivity();
    angleX =+ rate[0] * DT;
    angleY =+ rate[1] * DT;
    angleZ =+ rate[2] * DT;

    angles = {angleX, angleY, angleX}
    return angles;
}
Position SensorProcessor::GetAnglesFromAcc(float deltaTime)
{
    
    Position pos = accelerometer.Read();
    angleX = (float) (atan2(pos.y,pos.z)+PI)*RAD_TO_DEG;
    angleY = (float) (atan2(pos.z,pos.x)+PI)*RAD_TO_DEG;
    return {angleX,angleY,0}
}

Position SensorProcessor::GetFilteredRotation(Position anglesGyro, Position anglesAcc)
{
    



    return {0,0,0};
}