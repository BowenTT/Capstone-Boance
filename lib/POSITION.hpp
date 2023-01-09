#ifndef POSITION_H_
#define POSITION_H_
#include <stdint.h>
struct Position
{
    float x;
    float y;
    float z;

    Position operator+(const Position& a) const
    {
        Position result = {x + a.x,
                           y + a.y,
                           z + a.z};
        return result;
    }

    Position operator/(int divider) const
    {
        Position result = {x / divider,
                           y / divider,
                           z / divider};
        return result;
    }

    Position operator-(const Position& a) const
    {
        Position result = {x - a.x,
                           y - a.y,
                           z - a.z};
        
        return result;
    }
    
};

#endif