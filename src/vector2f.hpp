/**
 * @file
 * @brief     Vector2f Class
 * @author    Quinten Perquin
 * @license   See LICENSE
 */

#ifndef VECTOR2F_HPP
#define VECTOR2F_HPP

class Vector2f {
  private:
    float x;
    float y;

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

    /**
     * @brief Return X value.
     *
     * This function returns the X value
     *
     * @return float
     */
    float getX();

    /**
     * @brief Return Y value.
     *
     * This function returns the Y value
     *
     * @return float
     */
    float getY();
    /**
     * @brief Set the X value
     *
     * Set the X value to something different.
     *
     * @param value
     */
    void setX(float value);
    /**
     * @brief Set the Y value
     *
     * Set the Y value to something different.
     *
     * @param value : float
     *
     */
    void setY(float value);
};

#endif
