#include "Accelerometer.hpp"

Accelerometer::Accelerometer(uint8_t devAddr, int16_t min_value, int16_t max_value)
:devAddr(devAddr)
,min_value(min_value)
,max_value(max_value)
{
    offset = {0,0,0};
    pos = {0,0,0};
}

Position Accelerometer::Read()
{
    Position pos = {0,0,0};
    I2Cdev::readBytes(devAddr, LSM6DSL_ACC_GYRO_OUTX_L_XL_REG, LSM6DSL_ACCEL_SIGNAL_LENGTH, buffer);
    pos.x = (((int16_t)buffer[LSM6DSL_ACC_X_HIGH_VALUE])) << BYTE | buffer[LSM6DSL_ACC_X_LOW_VALUE];
    pos.y = (((int16_t)buffer[LSM6DSL_ACC_Y_HIGH_VALUE])) << BYTE | buffer[LSM6DSL_ACC_Y_LOW_VALUE];
    pos.z = (((int16_t)buffer[LSM6DSL_ACC_Z_HIGH_VALUE])) << BYTE | buffer[LSM6DSL_ACC_Z_LOW_VALUE];

    return pos;
}

int16_t Accelerometer::GetAccelerationX()
{
    I2Cdev::readBytes(devAddr, LSM6DSL_ACC_GYRO_OUTX_L_XL_REG, LSM6DSL_ACC_OUT_LENGTH, buffer);
    return (int16_t)buffer[0] | (int16_t)buffer[1] << BYTE;
}

int16_t Accelerometer::GetAccelerationY()
{
    I2Cdev::readBytes(devAddr, LSM6DSL_ACC_GYRO_OUTY_L_XL_REG, LSM6DSL_ACC_OUT_LENGTH, buffer);
    return (int16_t)buffer[0] | (int16_t)buffer[1] << BYTE;
}

int16_t Accelerometer::GetAccelerationZ()
{
    I2Cdev::readBytes(devAddr, LSM6DSL_ACC_GYRO_OUTZ_L_XL_REG, LSM6DSL_ACC_OUT_LENGTH, buffer);
    return (int16_t)buffer[0] | (int16_t)buffer[1] << BYTE;
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

uint8_t Accelerometer::GetDevAddr() const
{
    return devAddr;
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

