#include <Arduino.h>
#include <math.h>
#include <../hal/Accelerometer.hpp>
#include <../hal/Gyroscope.hpp>
#include <../hal/SensorProcessor.hpp>
#include <../hal/Stabilization.hpp>
#include <LSM6DSL-Arduino/src/LSM6DSL.h>

Accelerometer a(LSM6DSL_DEFAULT_ADDRESS, int16_t(-SIXTEEN_BIT), int16_t(SIXTEEN_BIT));
Gyroscope g(LSM6DSL_DEFAULT_ADDRESS, int16_t(-SIXTEEN_BIT), int16_t(SIXTEEN_BIT));
SensorProcessor sp(a,g);
PWMServo trimtab;
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
  Serial.print("ACCEL SENS = ");
  Serial.println(a.GetSensitivity(), 6);

  g.Setup();
  Serial.print("GYRO SENS = ");
  Serial.println(g.GetSensitivity(), 4);
  sp.Calibrate(250);

  trimtab.attach(9);
  Serial.println("DONE......... STARTING NOW");

}


void loop() 
{
  trimtab.write(0);
  delay(2000);

  Position curr_pos = {0,45,0};
  double timeOfAct = Stabilization::CalculateTimeOfAct(curr_pos, 0);
  Serial.print("timeOfAct = ");
  Serial.println(timeOfAct);
  double res = Stabilization::ActuateTrimTab(trimtab, timeOfAct);
  Serial.print("res = ");
  Serial.println(res);
  // Position prev_pos = {0,-45,0};
  // Position res = Stabilization::CalculateDeltaRotation(prev_pos, curr_pos);
  // if(-res.y >= ROLL_CHANGE_THRESHOLD)
  // {
  //   Serial.println("Wow, good job; You're going to be balanced soon");
  // }
  delay(5000);
}