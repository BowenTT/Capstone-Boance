#ifndef IACCELEROMETER_H_
#define IACCELEROMETER_H_

#include "../POSITION.hpp"

class IAccelerometer
{
public:
    virtual ~IAccelerometer(){};
    virtual Position Read() = 0;
    virtual const Position& GetOffset() const = 0;
    virtual float GetSensitivity() const = 0;
    virtual const Position GetPos(const Position& rawData) const = 0;
    virtual int SetOffset(int16_t x, int16_t y, int16_t z) = 0;
};

#endif