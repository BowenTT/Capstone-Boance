#include "../hal/Gyroscope.hpp"

Gyroscope::Gyroscope(int16_t min_value, int16_t max_value)
: min_value(min_value)
, max_value(max_value)
{ 
  offset = {0,0,0};
  pos = {0,0,0}; 
}


//Reads out 16 bits of each Gyroscope OUT register (x,y,z) and returns it in a user defined Position struct.
Position Gyroscope::Read()
{
    Position pos = {0,0,0};
    pos.x = LSM6DSL::readRawGyroX();
    pos.y = LSM6DSL::readRawGyroY();
    pos.z = LSM6DSL::readRawGyroZ();

    return pos;
}

//Returns x-axis value of the gyroscope
int16_t Gyroscope::GetRotationX()
{
    return LSM6DSL::readRawGyroX();
}

//Returns y-axis value of the gyroscope
int16_t Gyroscope::GetRotationY()
{
    return LSM6DSL::readRawGyroY();
}

//Returns z-axis of the gyroscope
int16_t Gyroscope::GetRotationZ()
{
    return LSM6DSL::readRawGyroZ();
}

const Position& Gyroscope::GetOffset() const
{
    return offset;
}

const Position Gyroscope::GetPos(const Position& rawData) const
{
    return (rawData + offset);
}

int16_t Gyroscope::GetMinValue() const
{
    return min_value;
}

int16_t Gyroscope::GetMaxValue() const
{
    return max_value;
}

int Gyroscope::GetSensitivity() const
{
    return sensitivity;
}

int Gyroscope::SetOffset(int16_t x, int16_t y, int16_t z)
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