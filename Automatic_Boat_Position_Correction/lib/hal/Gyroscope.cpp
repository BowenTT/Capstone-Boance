#include "../hal/Gyroscope.hpp"

/*
    Constructor for the gyroscope, sets private variables to be accessed later
*/
Gyroscope::Gyroscope(uint8_t devAddr, int16_t min_value, int16_t max_value)
: devAddr(devAddr)
, min_value(min_value)
, max_value(max_value)
{ 
  offset = {0,0,0};
  pos = {0,0,0}; 
}


/*
    Sets settings for the gyroscope, configurable in Sensor_Settings.h
*/
void Gyroscope::Setup()
{
    uint8_t data = 0;
    if (gyroEnabled == 1) {
        switch (gyroRange) {
        case 125:
            data |= LSM6DSL_ACC_GYRO_FS_G_125dps;
            break;
        case 245:
            data |= LSM6DSL_ACC_GYRO_FS_G_245dps;
            break;
        case 500:
            data |= LSM6DSL_ACC_GYRO_FS_G_500dps;
            break;
        case 1000:
            data |= LSM6DSL_ACC_GYRO_FS_G_1000dps;
            break;
        default:  //Default to full 2000DPS range
        case 2000:
            data |= LSM6DSL_ACC_GYRO_FS_G_2000dps;
            break;
        }

        switch (gyroSampleRate) {
        case 13:
            data |= LSM6DSL_ACC_GYRO_ODR_G_13Hz;
            break;
        case 26:
            data |= LSM6DSL_ACC_GYRO_ODR_G_26Hz;
            break;
        case 52:
            data |= LSM6DSL_ACC_GYRO_ODR_G_52Hz;
            break;
        default:  //Set default to 104
        case 104:
            data |= LSM6DSL_ACC_GYRO_ODR_G_104Hz;
            break;
        case 208:
            data |= LSM6DSL_ACC_GYRO_ODR_G_208Hz;
            break;
        case 416:
            data |= LSM6DSL_ACC_GYRO_ODR_G_416Hz;
            break;
        case 833:
            data |= LSM6DSL_ACC_GYRO_ODR_G_833Hz;
            break;
        case 1660:
            data |= LSM6DSL_ACC_GYRO_ODR_G_1660Hz;
            break;
        }
    }

    //Writes the settings to the register
    I2Cdev::writeByte(LSM6DSL_DEFAULT_ADDRESS,LSM6DSL_ACC_GYRO_CTRL2_G_REG, data);

    //Reads the config register and sets the sensitivity variable (page 61)
    //See LSM6DSL Datasheet for interpretation of sensitivity values
    //https://www.st.com/resource/en/datasheet/lsm6dsl.pdf 
    // TODO: Currently there is no support for the 125 DPS setting
    uint8_t buffer[1];
    I2Cdev::readByte(LSM6DSL_DEFAULT_ADDRESS, LSM6DSL_ACC_GYRO_CTRL2_G_REG, buffer);
    int reg_sens = (buffer[0] & 12) >> 2;

    switch(reg_sens)
    {
        case 0:
            sensitivity = LSM6DSL_GYRO_SENS_250;
            break;
        case 1:
            sensitivity = LSM6DSL_GYRO_SENS_500;
            break;
        case 2:
            sensitivity = LSM6DSL_GYRO_SENS_1000;
            break;
        default:
        case 3:
            sensitivity = LSM6DSL_GYRO_SENS_2000;
            break;
    }
}


/*
    Reads the gyroscope raw data and stores them into a predefined Position {x,y,z} structure
*/
Position Gyroscope::Read()
{
    Position pos = {0,0,0};
    I2Cdev::readBytes(devAddr, LSM6DSL_ACC_GYRO_OUTX_L_G_REG, LSM6DSL_GYRO_SIGNAL_LENGTH, buffer);
    pos.x = (((int16_t)buffer[LSM6DSL_GYRO_X_HIGH_VALUE])) << BYTE | buffer[LSM6DSL_GYRO_X_LOW_VALUE];
    pos.y = (((int16_t)buffer[LSM6DSL_GYRO_Y_HIGH_VALUE])) << BYTE | buffer[LSM6DSL_GYRO_Y_LOW_VALUE];
    pos.z = (((int16_t)buffer[LSM6DSL_GYRO_Z_HIGH_VALUE])) << BYTE | buffer[LSM6DSL_GYRO_Z_LOW_VALUE];

    return pos;
}

/*
    Reads the raw X-axis value of the gyroscope
*/
int16_t Gyroscope::GetRotationX()
{
    I2Cdev::readBytes(devAddr, LSM6DSL_ACC_GYRO_OUTX_L_G_REG, LSM6DSL_GYRO_OUT_LENGTH, buffer);
    return (((int16_t)buffer[1]) << BYTE) | buffer[0];
}

/*
    Reads the raw Y-axis value of the gyroscope
*/
int16_t Gyroscope::GetRotationY()
{
    I2Cdev::readBytes(devAddr, LSM6DSL_ACC_GYRO_OUTY_L_G_REG, LSM6DSL_GYRO_OUT_LENGTH, buffer);
    return (((int16_t)buffer[1]) << BYTE) | buffer[0];
}

/*
    Reads the raw Z-axis value of the gyroscope
*/
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

float Gyroscope::GetSensitivity() const
{
    return sensitivity;
}

/*
    Used to set the offset (calibration) of the gyroscope
*/
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