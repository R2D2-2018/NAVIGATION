#ifndef PATH_HPP
#define PATH_HPP

#include "math.hpp"
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
    Math m;
    double positionX;
    double positionY;
    double compassDegrees; // Value from 0 to 359, this resembles the degree value of a compass.
    double toGoDirection;  // Value from 0 to 359, this resembles the degree value of a compass.
    MPU9250Interface mpu9250;

  public:
    /**
     * @brief Construct a new Path object
     *
     * @param mpu9250
     */
    Path(MPU9250Interface mpu9250);
    /**
     * @brief Convert a Cartesian coordinate to a polar coordinate
     *
     * This function converts a cartesian coordinate (a coordinate in the X, Y coordinate system) to a polar coordinate( a
     * coordinate in the angle, distance system)
     *
     * @param node
     * @return PolarVector2f
     */
    PolarVector2f convertCartesianToPolar(Vector2f node);
    /**
     * @brief Get direction to the next node
     *
     * This function calculates the difference between the current and the next node. This will be converted into a polar
     * coordinate. It returns an angle and a distance in a PolarVector2f object.
     *
     * @param currentPosition
     * @param nextPosition
     * @return PolarVector2f
     */
    PolarVector2f getDirections(Vector2f currentPosition, Vector2f nextPosition);
    /**
     * @brief Get the Rotation from MPU object
     *
     * This function gets the rotation from the MPU compass.
     *
     * @return float
     */
    float getRotationFromMPU();
};

#endif // PATH_HPP