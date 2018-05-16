/**
 * @file
 * @brief     PositionModule Class
 * @author    Quinten Perquin
 * @license   See LICENSE
 */

#ifndef POSITION_MODULE_HPP
#define POSITION_MODULE_HPP

#include "MPU9250_Interface.hpp"
#include "Vector2f.hpp"

class PositionModule {
  public:
    PositionModule() {
    }

  private:
    MPU9250Interface MPU;
};

#endif