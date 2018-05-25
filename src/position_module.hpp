/**
 * @file
 * @brief     PositionModule Class
 * @author    Quinten Perquin
 * @license   See LICENSE
 */

#ifndef POSITION_MODULE_HPP
#define POSITION_MODULE_HPP

#include "mpu9250_interface.hpp"
#include "vector2f.hpp"

class PositionModule {
  public:
    /**
     * @brief creates a PositionModule object
     *
     * Constructor for a PositionModule object without arguments.
     *
     * @return a PositionModule object
     */
    PositionModule() {
    }

  private:
    MPU9250Interface MPU;
};

#endif