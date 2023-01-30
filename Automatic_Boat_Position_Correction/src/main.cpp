#include <Arduino.h>
#include <math.h>
#include <../hal/Accelerometer.hpp>
#include <../hal/Gyroscope.hpp>
#include <../hal/SensorProcessor.hpp>
#include <LSM6DSL-Arduino/src/LSM6DSL.h>

Accelerometer a(LSM6DSL_DEFAULT_ADDRESS, int16_t(-SIXTEEN_BIT), int16_t(SIXTEEN_BIT));
Gyroscope g(LSM6DSL_DEFAULT_ADDRESS, int16_t(-SIXTEEN_BIT), int16_t(SIXTEEN_BIT));
SensorProcessor sp(a,g);
Position pos = {0,0,0};

void setup() 
{
  Wire.begin();
  Serial.begin(19200);
  while(!Serial)
  {
    //Do nothing
  }

  a.Setup();
  // Serial.print("ACCEL SENS = ");
  // Serial.println(a.GetSensitivity(), 6);

  g.Setup();
  // Serial.print("GYRO SENS = ");
  // Serial.println(g.GetSensitivity(), 4);
  //sp.Calibrate(250);
  Serial.println("DONE......... STARTING NOW");

}

void loop() 
{

  // Position pos = {0,0,0};
  pos = sp.GetLastRotationReadings(25);
  Serial.print(pos.x);
  Serial.print(',');
  Serial.print(pos.y);
  Serial.print(',');
  Serial.println(pos.z);
  // Serial.print("X: ");
  // Serial.println(pos.x);
  // Serial.print("Y: ");
  // Serial.println(pos.y);
  // Serial.print("Z: ");
  // Serial.println(pos.z);

  // Position accel = a.Read();
  // float roll = atan(-1*accel.x/sqrt(pow(accel.y,2) + pow(accel.z,2))) * RADIANS_TO_DEGREES;

  // Serial.print("roll = ");
  // Serial.println(roll);
  // Serial.print("X: ");
  // Serial.println(a.GetAccelerationX());
  // Serial.print("Y = ");
  // Serial.println(a.GetAccelerationY());
  // Serial.print("Z = ");
  // Serial.println(a.GetAccelerationZ());


  // Serial.print("X: ");
  // Serial.println(g.GetRotationX());
  // Serial.print("Y = ");
  // Serial.println(g.GetRotationY());
  // Serial.print("Z = ");
  // Serial.println(g.GetRotationZ());
  //delay(1000);
}