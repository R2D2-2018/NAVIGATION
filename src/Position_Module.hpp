#ifndef POSITION_MODULE_HPP
#define POSITION_MODULE_HPP

#include "MPU9250_Interface.hpp"
#include "Vector.hpp"

class PositionModule {
  public:
    PositionModule() {
    }

  private:
    MPU9250Interface MPU;
};

#endif