#include <Arduino.h>
#include <../hal/Accelerometer.hpp>
#include <../hal/Gyroscope.hpp>
#include <LSM6DSL-Arduino/src/LSM6DSL.h>

Accelerometer a(0x6B, int16_t(-SIXTEEN_BIT), int16_t(SIXTEEN_BIT));
Gyroscope g(0x6B, int16_t(-SIXTEEN_BIT), int16_t(SIXTEEN_BIT));
LSM6DSL imu(LSM6DSL_MODE_I2C, 0x6B);

void setup() 
{
  Wire.begin();
  Serial.begin(9600);
  while(!Serial)
  {
    //Do nothing
  }

  lsm6dsl_status_t status = imu.begin();
  if(status != IMU_SUCCESS)
  {
    Serial.println(status);
  }

  Serial.println("START");

}

void loop() 
{
  Serial.print("X: ");
  Serial.println(a.GetAccelerationX());
  Serial.print("Y = ");
  Serial.println(a.GetAccelerationY());
  Serial.print("Z = ");
  Serial.println(a.GetAccelerationZ());


  // Serial.print("X: ");
  // Serial.println(g.GetRotationX());
  // Serial.print("Y = ");
  // Serial.println(g.GetRotationY());
  // Serial.print("Z = ");
  // Serial.println(g.GetRotationZ());
  delay(1000);
}