#ifndef PATH_HPP
#define PATH_HPP

#include "math.h"
#include "mpu9250_interface.hpp"
#include "polar_vector2f.hpp"
#include "vector2f.hpp"
#include "wrap-hwlib.hpp"

/**
 * @brief The Path class calculates the difference between the current position of the robot and the next node. It will return a
 *
 */
class Path {
  private:
    double positionX;
    double positionY;
    double compassDegrees; // Value from 0 to 359, this resembles the degree value of a compass.
    double toGoDirection;  // Value from 0 to 359, this resembles the degree value of a compass.

  public:
    Path();
    PolarVector2f convertCartesianToPolar(Vector2f node);
    double calculateToGoDirection(Vector2f node);
};

#endif // PATH_HPP