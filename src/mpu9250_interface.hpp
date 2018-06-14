/**
 * @file
 * @brief     MPU9250Interface Class
 * @author    Quinten Perquin
 * @license   See LICENSE
 */

#ifndef MPU9250_INTERFACE_HPP
#define MPU9250_INTERFACE_HPP

#include "coordinate3d.hpp"
#include "wrap-hwlib.hpp"

class MPU9250Interface {
  private:
    hwlib::pin_oc &scl;
    hwlib::pin_oc &sda;
    const int8_t MPUAddr;
    hwlib::i2c_bus_bit_banged_scl_sda i2c;

    Coordinate3D accelerationCalibrateValues;
    Coordinate3D gyroscopeCalibrateValues;
    Coordinate3D magneticCalibrateValues;

    Coordinate3D accelerationValues;
    Coordinate3D gyroscopeValues;
    Coordinate3D magneticValues;

  public:
    MPU9250Interface(hwlib::pin_oc &scl, hwlib::pin_oc &sda, const int8_t MPUAddr);

    /**
     * @brief Calibrate the sensor
     *
     * Calibrate the sensor by saving the initial values.
     *
     */
    void calibrate();

    /**
     * @brief Get the Accelerator values
     *
     * Returns values as Coordinate3D {x,y,z}
     *
     * @return Coordinate3D Gyroscope values
     */
    Coordinate3D getAccelerationValues();

    /**
     * @brief Get the Gyroscope values
     *
     * Returns values as Coordinate3D {x,y,z}
     *
     * @return Coordinate3D Gyroscope values
     */
    Coordinate3D getGyroscopeValues();

    /**
     * @brief Get the Accelerator values
     *
     * Returns values as Coordinate3D {x,y,z}
     *
     * @return Coordinate3D Gyroscope values
     */
    Coordinate3D saveAccelerationValues();

    /**
     * @brief Get the Gyroscope values
     *
     * Returns values as Coordinate3D {x,y,z}
     *
     * @return Coordinate3D Gyroscope values
     */
    Coordinate3D saveGyroscopeValues();

    /**
     * @brief Get the Magnetometer values
     *
     * Returns values as Coordinate3D {x,y,z}
     *
     * @return Coordinate3D Magnetometer values
     */
    Coordinate3D getMagneticValues();

    /**
     * @brief Prints values of the given Coordinate3D object in the format "X:% Y:% Z:%"
     *
     * @param Coordinate3D object
     */
    void printValuesX_Y_Z(Coordinate3D values);
};

#endif // COORDINATE3D_HPP