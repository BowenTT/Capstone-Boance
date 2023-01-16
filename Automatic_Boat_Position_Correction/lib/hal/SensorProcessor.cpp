#include "../hal/SensorProcessor.hpp"

SensorProcessor::SensorProcessor(IAccelerometer& accel, IGyroscope& gyro)
:accelerometer(accel)
,gyroscope(gyro)
,lastRotation(Position{0,0,0})
,currentTime(millis())
,previousTime(0)
,elapsedTime(0)
{
}

int SensorProcessor::Initialize()
{
    LSM6DSL imu(LSM6DSL_MODE_I2C, 0x6B);

    if(!imu.begin())
    {
        return -1;
    }

    return 0;
}


/*
    Calibrates the offsets of the LSM6DSL Accelerometer + Gyroscope by taking nrOfSamples 
    Offset gets used to counteract the bias instability of the sensor
    Sensor should be placed on a flat surface for best results
*/
void SensorProcessor::Calibrate(int nrOfSamples, int accelSens)
{
    //TODO
}

/*
    Returns the average of 'nrOfReadings' accelerometer readings
    Average is multiplied by ten for easier comparisons and visibility with plotting
*/
float SensorProcessor::GetLastAccelReadings(int nrOfReadings)
{
    Position pos = accelerometer.Read();
    return pos.x;
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
Position SensorProcessor::GetFilteredRotation()
{
    //TODO
    return {0,0,0};
}