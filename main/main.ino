#include <Arduino.h>
#include <Wire.h>
#include <Servo.h>
#include <math.h>

#include <LSM6DSL.h> // https://github.com/dycodex/LSM6DSL-Arduino



// Using I2C mode by default.
LSM6DSL imu(LSM6DSL_MODE_I2C, 0x6B); // This initializes I2C interface. // A4 (SDA), A5 (SCL). https://www.arduino.cc/reference/en/language/functions/communication/wire/ 
Servo trimtab;

const int buffLen = 10;
float inVals[buffLen] = {0};
int readIdx = 0;

float accel_calculate_roll(float y, float z)
{
  return (atan2(y, z) * RAD_TO_DEG);
}

void setup() {  
    Serial.begin(9600);
    delay(2000);

    Serial.println("It starts!");

    if (!imu.begin()) {
        Serial.println("Failed initializing LSM6DSL");
    }

    trimtab.attach(9);
}

void loop() {

    
    float x = imu.readFloatAccelX();
    float y = imu.readFloatAccelY();
    float z = imu.readFloatAccelZ();

    Serial.println(accel_calculate_roll(y,z));
    delay(100);
    
    // inVals[readIdx++] = y;
    // float avg = 0;
    // for (auto val : inVals) {
    //   avg += val;
    // }
    // avg = avg / buffLen;
    // if (readIdx >= buffLen) {
    //   readIdx = 0;
    // }
    // // float temp = x * 100;
    // // int val = map(temp, -102, 102, 0, 181);
    // // trimtab.write(val);
    // // delay(15);

    // // Serial plotter
    // Serial.print("AVG:");
    // Serial.print(avg);
    // Serial.print("\t\t");
    // Serial.print("X:");
    // Serial.print(x);
    // Serial.print("val:");
    // Serial.println(val);
    // delay(100);

}
