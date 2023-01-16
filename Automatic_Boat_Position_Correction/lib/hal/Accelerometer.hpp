#ifndef ACCELEROMETER_H_
#define ACCELEROMETER_H_

#include "../interfaces/IAccelerometer.hpp"
#include "../libraries/LSM6DSL-Arduino/src/LSM6DSL.h"
#include "../libraries/I2Cdev.hpp"
#include "Sensor_Settings.h"

class Accelerometer : public IAccelerometer
{
    public:
        Accelerometer(uint8_t devAddr, int16_t min_value, int16_t max_value);
        ~Accelerometer(){}

        void Setup();

        Position Read();
        int16_t GetAccelerationX();
        int16_t GetAccelerationY();
        int16_t GetAccelerationZ();
        const Position& GetOffset() const;
        const Position GetPos(const Position& rawData) const;
        int16_t GetMinValue() const;
        int16_t GetMaxValue() const;
        uint8_t GetDevAddr() const;
        int GetSensitivity() const;
        int SetOffset(int16_t x, int16_t y, int16_t z);
    
    private:
        uint8_t devAddr;
        uint8_t buffer[16];
        int16_t min_value;
        int16_t max_value;
        Position offset;
        Position pos;
        int sensitivity;

};

#endif