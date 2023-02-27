#include <Arduino.h>
#include <math.h>
#include <../hal/Accelerometer.hpp>
#include <../hal/Gyroscope.hpp>
#include <../hal/SensorProcessor.hpp>
#include <../hal/Stabilization.hpp>
#include <LSM6DSL-Arduino/src/LSM6DSL.h>

Accelerometer accelerometer(LSM6DSL_DEFAULT_ADDRESS, int16_t(-SIXTEEN_BIT), int16_t(SIXTEEN_BIT));
Gyroscope gyroscope(LSM6DSL_DEFAULT_ADDRESS, int16_t(-SIXTEEN_BIT), int16_t(SIXTEEN_BIT));
SensorProcessor sensorProcessor(accelerometer,gyroscope);
PWMServo leftTrimTab;
PWMServo rightTrimTab;
Position previous_position = {0,0,0};
Position current_position = {0,0,0};

bool BalancedState = true;
bool BalancingState = false;
bool PassiveState = false;

bool tiltedLeft = false;
bool tiltedRight = false;

bool test = false;

void setup() 
{
  Wire.begin();
  Serial.begin(19200);
  while(!Serial)
  {
    //Do nothing
  }

  accelerometer.Setup();
  Serial.print("ACCEL SENS = ");
  Serial.println(accelerometer.GetSensitivity(), 6);

  gyroscope.Setup();
  Serial.print("GYRO SENS = ");
  Serial.println(gyroscope.GetSensitivity(), 4);
  sensorProcessor.Calibrate(250);

  leftTrimTab.attach(9);
  rightTrimTab.attach(10);

  Serial.println("DONE......... STARTING NOW");

}


void loop() 
{
  if(test)
  {
    //TEST, REMOVE ON PRODUCTION
    current_position = sensorProcessor.GetLastRotationReadings(250);
    Serial.println(current_position.y);
    delay(100);
  }

  else if(BOAT_SPEED >= MIN_BOAT_SPEED)
  {

    while(BalancedState)
    {

      tiltedLeft = false;
      tiltedRight = false;

      //Get the average rotation of the past [ms] milliseconds
      current_position = sensorProcessor.GetLastRotationReadings(100);

      //DEBUG LINE, REMOVE ON PRODUCTION
      Serial.print("In Balanced State, roll = ");
      Serial.println(current_position.y);

      //Check if the boat is tilted enough, if so, move to BalancingState.
      if(abs(current_position.y) >= ROLL_THRESHOLD)
      {
        //Check if tilted left or right, negative = left, positive = right
        if(current_position.y <= ROLL_THRESHOLD)
        {
          tiltedLeft = true;
        }

        else if(current_position.y >= ROLL_THRESHOLD)
        {
          tiltedRight = true;
        }

        BalancedState = false;
        PassiveState = false;
        BalancingState = true;
        break;
      }
    }
    

    while(BalancingState)
    {

      previous_position = current_position;
      //Get the average rotation of the past [ms] milliseconds
      current_position = sensorProcessor.GetLastRotationReadings(100);

      //DEBUG LINE, REMOVE ON PRODUCTION
      Serial.print("In Balancing State, roll = ");
      Serial.println(current_position.y);

      Position positionDelta = {0,0,0};
      PWMServo activeTrimTab;
      //Calculation of the delta rotation is reversed for the left and right trimtabs because of the negative & positive changes respectively
      //Therefore, the CalculateDeltaRotation has to be reversed for each trim tab the check to make sense
      if(tiltedLeft)
      {
        Serial.println("Tilted left");
        rightTrimTab.write(0);
        positionDelta = Stabilization::CalculateDeltaRotation(current_position, previous_position);
        activeTrimTab = leftTrimTab;
      }
      else if(tiltedRight)
      {
        Serial.println("Tilted right");
        leftTrimTab.write(0);
        positionDelta = Stabilization::CalculateDeltaRotation(previous_position, current_position);
        activeTrimTab = rightTrimTab;
      }

      //Check if the last actuation time has a positive enough impact
      if(positionDelta.y >= ROLL_CHANGE_THRESHOLD)
        {
          // Positive enough, go to Passive Posture Correction State
          BalancingState = false;
          PassiveState = true;
          break;
        }
        else
        {
          //Calculate the actuation time based on the angle and actuate the correct trimtab
          double timeOfAct = Stabilization::CalculateTimeOfAct(current_position, 0);
          Stabilization::ActuateTrimTab(activeTrimTab, timeOfAct);
        }
      }

    while(PassiveState)
    {



      previous_position = current_position;
      current_position = sensorProcessor.GetLastRotationReadings(100);

      //DEBUG LINE, REMOVE ON PRODUCTION
      Serial.print("In Passive Correction State, roll = ");
      Serial.println(current_position.y);

      Position positionDelta = {0,0,0};

      if(tiltedLeft)
      {
        positionDelta = Stabilization::CalculateDeltaRotation(current_position, previous_position);
      }
      else if(tiltedRight)
      {
        positionDelta = Stabilization::CalculateDeltaRotation(previous_position, current_position);
      }

      //Negative change (rolling the wrong way)
      if(positionDelta.y <= ROLL_CHANGE_THRESHOLD)
      {
        PassiveState = false;
        BalancingState = true;
        break;
      }

      //Check if boat is balanced (where -ROLL_THRESHOLD <= current.y <= ROLL_THRESHOLD)
      //If so, go to balanced state
      if(current_position.y >= -ROLL_THRESHOLD && current_position.y <= ROLL_THRESHOLD)
      {
        PassiveState = false;
        BalancedState = true;
        break;
      }
    }
  }
  else
  {
    Serial.println("Boat is not going fast enough... ");
    Serial.print("Minimum speed required = ");
    Serial.println(MIN_BOAT_SPEED);
    Serial.print("Current boat speed = ");
    Serial.println(BOAT_SPEED);
    delay(1000);
  }
}