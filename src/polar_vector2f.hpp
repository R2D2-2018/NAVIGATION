#ifndef POLAR_VECTOR2F_HPP
#define POLAR_VECTOR2F_HPP

class PolarVector2f {
  private:
    float angle;
    float distance;

  public:
    /**
     * @brief creates a Vector2f object
     *
     * Constructor for a Vector2f object with no arguments.
     *
     * @return a Vector2f object
     */
    PolarVector2f() {
    }

    /**
     * @brief creates a Vector2f object
     *
     * Constructor for a Vector2f object with two arguments.
     *
     * @param[in]    angle      A float representing the angle
     * @param[in]    distance   A float representing the distance
     *
     * @return a Vector2f object
     */
    PolarVector2f(float angle, float distance) : angle(angle), distance(distance) {
    }

    /**
     * @brief Returns angle
     *
     * This function returns the angle.
     *
     * @return float
     */
    float getAngle();

    /**
     * @brief Return distance
     *
     * This function returns the distance.
     *
     * @return float
     */
    float getDistance();
    /**
     * @brief Set the angle
     *
     * Set the angle to something different.
     *
     * @param value
     */
    void setAngle(float value);
    /**
     * @brief Set the distance
     *
     * Set the distance to something different.
     *
     * @param value : float
     *
     */
    void setDistance(float value);
};

#endif // POLAR_VECTOR2F_HPP