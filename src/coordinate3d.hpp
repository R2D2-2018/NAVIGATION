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
    /**
     * @brief Construct a new Coordinate3D object
     *
     * The default constructor to create a new Coordinate3D object.
     */
    Coordinate3D();

    /**
     * @brief Construct a new Coordinate3D object
     *
     * The default constructor to create a new Coordinate3D object.
     * @param x : int16_t
     * @param y : int16_t
     * @param z : int16_t
     */
    Coordinate3D(int16_t x, int16_t y, int16_t z);

    /**
     * @brief Set X value
     *
     * Change the X value of the object.
     *
     * @param value : int16_t
     */
    void setX(int16_t value);

    /**
     * @brief Set Y value
     *
     * Change the Y value of the object.
     *
     * @param value : int16_t
     */
    void setY(int16_t value);

    /**
     * @brief Set Z value
     *
     * Change the Z value of the object.
     *
     * @param value : int16_t
     */
    void setZ(int16_t value);

    /**
     * @brief Return the X value
     *
     * Return the X value of this object.
     *
     * @return int16_t
     */
    int16_t getX();

    /**
     * @brief Return the Y value
     *
     * Return the Y value of this object.
     *
     * @return int16_t
     */
    int16_t getY();

    /**
     * @brief Return the Z value
     *
     * Return the Z value of this object.
     *
     * @return int16_t
     */
    int16_t getZ();

    /**
     * @brief coordinate3D += operator
     *
     * Returns a coordinate3D after adding another coordinate3D to it.
     *
     * @param rhs : const Coordinate3D &
     * @return Coordinate3D
     */
    Coordinate3D &operator+=(const Coordinate3D &rhs);

    /**
     * @brief coordinate3D -= operator
     *
     * Returns a coordinate3D after subtracting another coordinate3D to it.
     *
     * @param rhs : const Coordinate3D &
     * @return Coordinate3D
     */
    Coordinate3D &operator-=(const Coordinate3D &rhs);

    /**
     * @brief Coordinate3D *= operator
     *
     * Returns a coordinate3D after multiplying it with an intiger.
     *
     * @param multiplier : const int
     * @return Coordinate3D
     */
    Coordinate3D &operator*=(const int multiplier);

    /**
     * @brief Coordinate3D /= operator
     *
     * Returns a coordinate3D after dividing it with an intiger.
     *
     * @param divider : const int
     * @return Coordinate3D
     */
    Coordinate3D &operator/=(const int divider);

    /**
     * @brief coordinate3D + operator
     *
     * Returns a coordinate3D after adding another coordinate3D to it.
     *
     * @param rhs : const Coordinate3D &
     * @return Coordinate3D
     */
    Coordinate3D operator+(const Coordinate3D &rhs) const;

    /**
     * @brief coordinate3D - operator
     *
     * Returns a coordinate3D after subtracting another coordinate3D to it.
     *
     * @param rhs : const Coordinate3D &
     * @return Coordinate3D
     */
    Coordinate3D operator-(const Coordinate3D &rhs) const;
    /**
     * @brief Coordinate3D / operator
     *
     * Returns a coordinate3D after dividing it with an intiger.
     *
     * @param divider : const int
     * @return Coordinate3D
     */
    Coordinate3D operator/(const int divider) const;
    /**
     * @brief Coordinate3D * operator
     *
     * Returns a coordinate3D after multiplying it with an intiger.
     *
     * @param multiplier : const int
     * @return Coordinate3D
     */
    Coordinate3D operator*(const int multiplier) const;
};

#endif // COORDINATE3D_HPP
