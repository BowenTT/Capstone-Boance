#include <Arduino.h>
#include <math.h>
#include <../hal/Accelerometer.hpp>
#include <../hal/Gyroscope.hpp>
#include <LSM6DSL-Arduino/src/LSM6DSL.h>

Accelerometer a(LSM6DSL_DEFAULT_ADDRESS, int16_t(-SIXTEEN_BIT), int16_t(SIXTEEN_BIT));
Gyroscope g(LSM6DSL_DEFAULT_ADDRESS, int16_t(-SIXTEEN_BIT), int16_t(SIXTEEN_BIT));

void setup() 
{
  Wire.begin();
  Serial.begin(9600);
  while(!Serial)
  {
    //Do nothing
  }

  a.Setup();
  Serial.print("ACCEL SENS = ");
  Serial.println(a.GetSensitivity());

  g.Setup();
  Serial.print("GYRO SENS = ");
  Serial.println(g.GetSensitivity());

  Serial.println("START");

}

void loop() 
{

  float RADIANS_TO_DEGREES = 180/M_PI;

  Position accel = a.Read();
  float roll = atan(-1*accel.x/sqrt(pow(accel.y,2) + pow(accel.z,2))) * RADIANS_TO_DEGREES;

  Serial.print("roll = ");
  Serial.println(roll);
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
  delay(1000);
}