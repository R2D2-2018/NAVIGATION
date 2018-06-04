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
    /**
     * @brief creates a Vector2f object
     *
     * Constructor for a Vector2f object with no arguments.
     *
     * @return a Vector2f object
     */
    Vector2f() {
    }

    /**
     * @brief creates a Vector2f object
     *
     * Constructor for a Vector2f object with two arguments.
     *
     * @param[in]    x    A float representing the x position
     * @param[in]    y    A float representing the y position
     *
     * @return a Vector2f object
     */
    Vector2f(float x, float y) : x(x), y(y) {
    }
    float x;
    float y;
};

#endif
