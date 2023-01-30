#ifndef GYROSCOPE_H_
#define GYROSCOPE_H_


#include "../interfaces/IGyroscope.hpp"
#include "../libraries/LSM6DSL-Arduino/src/LSM6DSL.h"
#include "../libraries/I2Cdev.hpp"
#include "Sensor_Settings.h"


class Gyroscope : public IGyroscope
{
public:
    Gyroscope(uint8_t devAddr, int16_t min_value, int16_t max_value);
    ~Gyroscope(){}

    void Setup();

    Position Read();
    int16_t GetRotationX();
    int16_t GetRotationY();
    int16_t GetRotationZ();
    const Position& GetOffset() const;
    const Position GetPos(const Position& rawData) const;
    int16_t GetMinValue() const;
    int16_t GetMaxValue() const;
    uint8_t GetDevAddr() const;
    float GetSensitivity() const;
    int SetOffset(int16_t x, int16_t y, int16_t z);

private:
    uint8_t devAddr;
    uint8_t buffer[6];
    int min_value;
    int max_value;
    Position offset;
    Position pos;
    float sensitivity;

};

#endif