#include "../hal/SensorProcessor.hpp"

Position convertWithFactor(Position pos, float factor)
{
  Position force = {0,0,0};
  force.x = pos.x * factor;
  force.y = pos.y * factor;
  force.z = pos.z * factor;
  return force;
}

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
void SensorProcessor::Calibrate(int nrOfSamples)
{
    // Perhaps this is not needed, factory calibration might be enough
    Position offsetAccel = {0,0,0};
    Position offsetGyro = {0,0,0};

    for (int i = 0; i < nrOfSamples; i++)
    {
        offsetAccel = offsetAccel + accelerometer.Read();
        offsetGyro = offsetGyro + gyroscope.Read();
    }
    offsetAccel = offsetAccel / nrOfSamples;
    offsetGyro = offsetGyro / nrOfSamples;

    accelerometer.SetOffset((0- offsetAccel.x), (0 - offsetAccel.y), (0 - offsetAccel.z));
    gyroscope.SetOffset((0 - offsetGyro.x), (0 - offsetGyro.y), (0 - offsetGyro.z));
}

/*
    Returns the average of 'nrOfReadings' accelerometer readings
    Average is multiplied by ten for easier comparisons and visibility with plotting
*/
Position SensorProcessor::GetLastAccelReadings(unsigned long ms)
{
    Position average = {0,0,0};
    int cnt = 0;
    unsigned long start_time = millis();
    unsigned long end_time = start_time;

    while((end_time - start_time) <= ms)
    {
        Position accelValues = convertWithFactor(accelerometer.GetPos(accelerometer.Read()), accelerometer.GetSensitivity());
        average = average + accelValues;
        cnt++;
        end_time = millis();
    }

    average = average / cnt;
    return average;
}

/* 
    Returns the average of gyroscope readings over [ms] amount of time
    Return value = {x, y, z}
*/
Position SensorProcessor::GetLastRotationReadings(unsigned long ms)
{
    Position average = {0,0,0};
    int cnt = 0;
    unsigned long start_time = millis();
    unsigned long end_time = start_time;

    while((end_time - start_time) <= ms)
    {
        average = average + GetFilteredRotation();
        cnt++;
        end_time = millis();
    }

    average = average / cnt;
    return average;
}

/*
    Gets the angular rotation of the sensor by first getting the roll and pitch from the accelerometer
    then it integrates the gyroscope data over time to get angular rotation from the gyryscope
    at last, a complementary filter is used to combined both datastreams for a more accurate representation

    TODO:: Implement Kalman Filter here
*/
Position SensorProcessor::GetFilteredRotation()
{
    currentTime = millis();
    float RADIANS_TO_DEGREES = 180/M_PI;
    Position accel = accelerometer.Read();
    //Get roll and pitch from accelerometer
    float roll = atan(-1*accel.x/sqrt(pow(accel.y,2) + pow(accel.z,2))) * RADIANS_TO_DEGREES;
    float pitch = atan(accel.y/sqrt(pow(accel.x,2) + pow(accel.z,2))) * RADIANS_TO_DEGREES;
    //Get rotation from gyroscope
    Position rotation = convertWithFactor(gyroscope.GetPos(gyroscope.Read()), gyroscope.GetSensitivity());
    elapsedTime = (currentTime - previousTime) / 1000;
    Position integratedGyro = {rotation.x * elapsedTime + lastRotation.x,
                                rotation.y * elapsedTime + lastRotation.y,
                                rotation.z * elapsedTime + lastRotation.z};


    float alpha = 0.98;
    Position filteredRotation = {alpha * integratedGyro.x + (1 - alpha) * pitch
                                ,alpha * integratedGyro.y + (1 - alpha) * roll
                                ,integratedGyro.z};

    
    previousTime = currentTime;
    lastRotation = filteredRotation;
    return filteredRotation;
}