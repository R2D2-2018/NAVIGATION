/**
 * @file
 * @brief     Vector2f Class
 * @author    Quinten Perquin
 * @license   See LICENSE
 */

#ifndef VECTOR2F_HPP
#define VECTOR2F_HPP

class Vector2f {
  public:
    Vector2f() {
    }
    Vector2f(float x, float y) : x(x), y(y) {
    }
    float x;
    float y;
};

#endif