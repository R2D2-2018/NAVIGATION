/**
 * @file
 * @brief     Coordinate3D Class
 * @author    Jeroen van Hattem
 * @license   See LICENSE
 */
#ifndef COORDINATE3D_HPP
#define COORDINATE3D_HPP

#include "wrap-hwlib.hpp"

template <typename T>
struct Coordinate3D {
  private:
    T x;
    T y;
    T z;

  public:
    /**
     * @brief Construct a new Coordinate3D object
     *
     * The default constructor to create a new Coordinate3D object.
     *
     */
    Coordinate3D();

    /**
     * @brief Construct a new Coordinate3D object
     *
     * The default constructor to create a new Coordinate3D object.
     *
     * @param x : T
     * @param y : T
     * @param z : T
     *
     */
    Coordinate3D(T x, T y, T z);

    /**
     * @brief Set X value
     *
     * Change the X value of the object.
     *
     * @param value : T
     */
    void setX(T value);

    /**
     * @brief Set Y value
     *
     * Change the Y value of the object.
     *
     * @param value : T
     */
    void setY(T value);

    /**
     * @brief Set Z value
     *
     * Change the Z value of the object.
     *
     * @param value : T
     */
    void setZ(T value);

    /**
     * @brief Return the X value
     *
     * Return the X value of this object.
     *
     * @return T
     */
    T getX();

    /**
     * @brief Return the Y value
     *
     * Return the Y value of this object.
     *
     * @return T
     */
    T getY();

    /**
     * @brief Return the Z value
     *
     * Return the Z value of this object.
     *
     * @return T
     */
    T getZ();
};

#endif // COORDINATE3D_HPP