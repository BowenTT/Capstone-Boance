#include "Accelerometer.hpp"

Accelerometer::Accelerometer(int16_t min_value, int16_t max_value)
:min_value(min_value)
,max_value(max_value)
{
    offset = {0,0,0};
    pos = {0,0,0};
}

Position Accelerometer::Read()
{
    Position pos;
    pos.x = LSM6DSL::readRawAccelX();
    pos.y = LSM6DSL::readRawAccelY();
    pos.z = LSM6DSL::readRawAccelZ();

    return pos;
}

int16_t Accelerometer::GetAccelerationX()
{
    return LSM6DSL::readRawAccelX();
}

int16_t Accelerometer::GetAccelerationY()
{
    return LSM6DSL::readRawAccelY();
}

int16_t Accelerometer::GetAccelerationZ()
{
    return LSM6DSL::readRawAccelZ();
}

const Position& Accelerometer::GetOffset() const
{
    return offset;
}

const Position Accelerometer::GetPos(const Position& rawData) const
{
    return (rawData + offset);
}

int16_t Accelerometer::GetMinValue() const
{
    return min_value;
}

int16_t Accelerometer::GetMaxValue() const
{
    return max_value;
}

int Accelerometer::GetSensitivity() const
{
    return sensitivity;
}

int Accelerometer::SetOffset(int16_t x, int16_t y, int16_t z)
{
    if(x >= min_value && x <= max_value 
    && y >= min_value && y <= max_value
    && z >= min_value && z <= max_value)
    {
        offset.x = x;
        offset.y = y;
        offset.z = z;
        return 0;
    }

    return -1;
}

