#include "../hal/Gyroscope.hpp"

Gyroscope::Gyroscope(uint8_t devAddr, int16_t min_value, int16_t max_value)
: devAddr(devAddr)
, min_value(min_value)
, max_value(max_value)
{ 
  offset = {0,0,0};
  pos = {0,0,0}; 
}


//Reads out 16 bits of each Gyroscope OUT register (x,y,z) and returns it in a user defined Position struct.
Position Gyroscope::Read()
{
    Position pos = {0,0,0};
    I2Cdev::readBytes(devAddr, LSM6DSL_ACC_GYRO_OUTX_L_G_REG, LSM6DSL_GYRO_SIGNAL_LENGTH, buffer);
    pos.x = (((int16_t)buffer[LSM6DSL_GYRO_X_HIGH_VALUE])) << BYTE | buffer[LSM6DSL_GYRO_X_LOW_VALUE];
    pos.y = (((int16_t)buffer[LSM6DSL_GYRO_Y_HIGH_VALUE])) << BYTE | buffer[LSM6DSL_GYRO_Y_LOW_VALUE];
    pos.z = (((int16_t)buffer[LSM6DSL_GYRO_Z_HIGH_VALUE])) << BYTE | buffer[LSM6DSL_GYRO_Z_LOW_VALUE];

    return pos;
}

//Returns x-axis value of the gyroscope
int16_t Gyroscope::GetRotationX()
{
    I2Cdev::readBytes(devAddr, LSM6DSL_ACC_GYRO_OUTX_L_G_REG, LSM6DSL_GYRO_OUT_LENGTH, buffer);
    return (((int16_t)buffer[1]) << BYTE) | buffer[0];
}

//Returns y-axis value of the gyroscope
int16_t Gyroscope::GetRotationY()
{
    I2Cdev::readBytes(devAddr, LSM6DSL_ACC_GYRO_OUTY_L_G_REG, LSM6DSL_GYRO_OUT_LENGTH, buffer);
    return (((int16_t)buffer[1]) << BYTE) | buffer[0];
}

//Returns z-axis of the gyroscope
int16_t Gyroscope::GetRotationZ()
{
    I2Cdev::readBytes(devAddr, LSM6DSL_ACC_GYRO_OUTZ_L_G_REG, LSM6DSL_GYRO_OUT_LENGTH, buffer);
    return (((int16_t)buffer[1]) << BYTE) | buffer[0];
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