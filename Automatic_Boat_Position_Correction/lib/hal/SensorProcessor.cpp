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
    Position pos = {0,0,0};
    Position angles = {0,0,0};

    float angleX = 0;
    float angleY = 0;
    float angleZ = 0;
    float rateX = 0;
    float rateY = 0;
    float rateZ = 0;
    

    pos = gyroscope.Read();
    rateX = pos.x * gyroscope.GetSensitivity();
    rateY = pos.y * gyroscope.GetSensitivity();
    rateZ = pos.z * gyroscope.GetSensitivity();
    angleX += rateX * DT;
    angleY += rateY * DT;
    angleZ += rateZ * DT;

    angles = {angleX, angleY, angleZ};
    return angles;
}
Position SensorProcessor::GetAnglesFromAcc(float deltaTime)
{
    
    Position pos = accelerometer.Read();
    float angleX = (float) (atan2(pos.y,pos.z)+PI)*RAD_TO_DEG;
    float angleY = (float) (atan2(pos.z,pos.x)+PI)*RAD_TO_DEG;
    return {angleX,angleY,0};
}

Position SensorProcessor::GetFilteredRotation(Position anglesGyro, Position anglesAcc)
{
   //Complementary filter
   //Current angle = 98% x (current angle + gyro rotation rate) + (2% * Accelerometer angle)
    float angleX = 0;
    float angleY = 0;
    angleX = 0.98 * (anglesGyro.x) + (0.02 * anglesAcc.x);
    angleY = 0.98 * (anglesGyro.y) + (0.02 * anglesAcc.y);



    return {angleX,angleY,0};
}