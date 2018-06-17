/**
 * @file
 * @brief     Coordinate3D Class
 * @author    Jeroen van Hattem
 * @license   See LICENSE
 */
#ifndef COORDINATE3D_HPP
#define COORDINATE3D_HPP

#include "wrap-hwlib.hpp"

struct Coordinate3D {
  private:
    int16_t x;
    int16_t y;
    int16_t z;

  public:
    Coordinate3D();
    Coordinate3D(int16_t x, int16_t y, int16_t z);
    void setX(int16_t value);
    void setY(int16_t value);
    void setZ(int16_t value);

    int16_t getX();
    int16_t getY();
    int16_t getZ();
};

#endif // COORDINATE3D_HPP