#include "Accelerometer.hpp"

/*
    Accelerometer constructor, sets private variables to be accessed through getters
*/
Accelerometer::Accelerometer(uint8_t devAddr, int16_t min_value, int16_t max_value)
:devAddr(devAddr)
,min_value(min_value)
,max_value(max_value)
{
    offset = {0,0,0};
    pos = {0,0,0};
}

/*
    Sets settings for the accelerometer, configurable in Sensor_Settings.h
*/
void Accelerometer::Setup()
{
    uint8_t data = 0;
    if (accelEnabled == 1) {
        if (accelSampleRate >= 1660) {
            data |= 0x01;
        }

        switch (accelRange) {
            case 2:
                data |= LSM6DSL_ACC_GYRO_FS_XL_2g;
                break;
            case 4:
                data |= LSM6DSL_ACC_GYRO_FS_XL_4g;
                break;
            case 8:
                data |= LSM6DSL_ACC_GYRO_FS_XL_8g;
                break;
            default:  //set default case to 16(max)
            case 16:
                data |= LSM6DSL_ACC_GYRO_FS_XL_16g;
                break;
        }

        switch (accelSampleRate) {
            case 13:
                data |= LSM6DSL_ACC_GYRO_ODR_XL_13Hz;
                break;
            case 26:
                data |= LSM6DSL_ACC_GYRO_ODR_XL_26Hz;
                break;
            case 52:
                data |= LSM6DSL_ACC_GYRO_ODR_XL_52Hz;
                break;
            default:  //Set default to 104
            case 104:
                data |= LSM6DSL_ACC_GYRO_ODR_XL_104Hz;
                break;
            case 208:
                data |= LSM6DSL_ACC_GYRO_ODR_XL_208Hz;
                break;
            case 416:
                data |= LSM6DSL_ACC_GYRO_ODR_XL_416Hz;
                break;
            case 833:
                data |= LSM6DSL_ACC_GYRO_ODR_XL_833Hz;
                break;
            case 1660:
                data |= LSM6DSL_ACC_GYRO_ODR_XL_1660Hz;
                break;
            case 3330:
                data |= LSM6DSL_ACC_GYRO_ODR_XL_3330Hz;
                break;
            case 6660:
                data |= LSM6DSL_ACC_GYRO_ODR_XL_6660Hz;
                break;;
        }
    }
    //Writes the settings to the registers
    I2Cdev::writeByte(LSM6DSL_DEFAULT_ADDRESS, LSM6DSL_ACC_GYRO_CTRL1_XL_REG, data);

    //Reads the config register and sets the sensitivity variable
    //See LSM6DSL Datasheet for interpretation of sensitivity values
    //https://www.st.com/resource/en/datasheet/lsm6dsl.pdf
    uint8_t buffer[1];
    I2Cdev::readByte(LSM6DSL_DEFAULT_ADDRESS, LSM6DSL_ACC_GYRO_CTRL1_XL_REG, buffer);
    int reg_sens = (buffer[0] & 12) >> 2;

    switch(reg_sens)
    {
        case 0:
            sensitivity = LSM6DSL_ACCEL_SENS_2G;
            break;
        default:
        case 1:
            sensitivity = LSM6DSL_ACCEL_SENS_16G;
            break;
        case 2:
            sensitivity = LSM6DSL_ACCEL_SENS_4G;
            break;
        case 3:
            sensitivity = LSM6DSL_ACCEL_SENS_8G;
            break;
    }
}


/*
    Reads the accelerometer raw data and stores them into a predefined Position {x,y,z} structure
*/
Position Accelerometer::Read()
{
    Position pos = {0,0,0};
    I2Cdev::readBytes(devAddr, LSM6DSL_ACC_GYRO_OUTX_L_XL_REG, LSM6DSL_ACCEL_SIGNAL_LENGTH, buffer);
    pos.x = (((int16_t)buffer[LSM6DSL_ACC_X_HIGH_VALUE])) << BYTE | buffer[LSM6DSL_ACC_X_LOW_VALUE];
    pos.y = (((int16_t)buffer[LSM6DSL_ACC_Y_HIGH_VALUE])) << BYTE | buffer[LSM6DSL_ACC_Y_LOW_VALUE];
    pos.z = (((int16_t)buffer[LSM6DSL_ACC_Z_HIGH_VALUE])) << BYTE | buffer[LSM6DSL_ACC_Z_LOW_VALUE];

    return pos;
}

/*
    Reads the raw X value of the accelerometer
*/
int16_t Accelerometer::GetAccelerationX()
{
    I2Cdev::readBytes(devAddr, LSM6DSL_ACC_GYRO_OUTX_L_XL_REG, LSM6DSL_ACC_OUT_LENGTH, buffer);
    return (int16_t)buffer[0] | (int16_t)buffer[1] << BYTE;
}

/*
    Reads the raw Y value of the accelerometer
*/
int16_t Accelerometer::GetAccelerationY()
{
    I2Cdev::readBytes(devAddr, LSM6DSL_ACC_GYRO_OUTY_L_XL_REG, LSM6DSL_ACC_OUT_LENGTH, buffer);
    return (int16_t)buffer[0] | (int16_t)buffer[1] << BYTE;
}

/*
    Reads the raw Z value of the accelerometer
*/
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


float Accelerometer::GetSensitivity() const
{
    return sensitivity;
}


/*
    Used to set the offset (calibration) of the accelerometer
*/
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

