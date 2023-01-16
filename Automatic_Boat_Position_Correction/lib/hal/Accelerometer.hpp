#ifndef ACCELEROMETER_H_
#define ACCELEROMETER_H_

#include "../interfaces/IAccelerometer.hpp"
#include "../LSM6DSL-Arduino/src/LSM6DSL.h"

class Accelerometer : public IAccelerometer
{
    public:
        Accelerometer(int16_t min_value, int16_t max_value);
        ~Accelerometer(){}

        Position Read();
        int16_t GetAccelerationX();
        int16_t GetAccelerationY();
        int16_t GetAccelerationZ();
        const Position& GetOffset() const;
        const Position GetPos(const Position& rawData) const;
        int16_t GetMinValue() const;
        int16_t GetMaxValue() const;
        int GetSensitivity() const;
        int SetOffset(int16_t x, int16_t y, int16_t z);
    
    private:
        uint8_t buffer[14];
        int16_t min_value;
        int16_t max_value;
        Position offset;
        Position pos;
        int sensitivity;

};

#endif