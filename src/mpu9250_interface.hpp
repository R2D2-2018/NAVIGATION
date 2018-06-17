/**
 * @file
 * @brief     MPU9250Interface Class
 * @author    Quinten Perquin and Jeroen van Hattem
 * @license   See LICENSE
 */

// REGISTER MAP: https://cdn.sparkfun.com/assets/learn_tutorials/5/5/0/MPU-9250-Register-Map.pdf
// COMPASS: https://devzone.nordicsemi.com/f/nordic-q-a/28414/read-mpu-9250-magnetometer/112145#112145

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
    Coordinate3D magnetometerCalibrateValues;

    Coordinate3D accelerationValues;
    Coordinate3D gyroscopeValues;
    Coordinate3D magnetometerValues;

  public:
    MPU9250Interface(hwlib::pin_oc &scl, hwlib::pin_oc &sda, const int8_t MPUAddr);

    /**
     * @brief Calibrate the sensor
     *
     * Calibrate the sensor by saving the initial values. So it sets a zero.
     *
     */
    void calibrate();

    /**
     * @brief Get the calibrated Coordinate3D value for the acceleration
     *
     * Returns values as Coordinate3D {x,y,z}
     *
     * @return Coordinate3D acceleration calibrated values
     */
    Coordinate3D getAccelerationCalibrateValues();

    /**
     * @brief Get the calibrated Coordinate3D value for the gyroscope
     *
     * Returns values as Coordinate3D {x,y,z}
     *
     * @return Coordinate3D gyroscope calibrated values
     */
    Coordinate3D getGyroscopeCalibrateValues();

    /**
     * @brief Get the calibrated Coordinate3D for the Magnetometer sensor
     *
     * Returns values as Coordinate3D {x,y,z}
     *
     * @return Coordinate3D Magnetometer calibrated values
     */
    Coordinate3D getMagnetometerCalibrateValues();

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
    void saveAccelerationValues();

    /**
     * @brief Get the Gyroscope values
     *
     * Returns values as Coordinate3D {x,y,z}
     *
     * @return Coordinate3D Gyroscope values
     */
    void saveGyroscopeValues();

    /**
     * @brief Get the Magnetometer values
     *
     * Returns values as Coordinate3D {x,y,z}
     *
     * @return Coordinate3D Magnetometer values
     */
    Coordinate3D getMagnetometerValues();

    /**
     * @brief Prints values of the given Coordinate3D object in the format "X:% Y:% Z:%"
     *
     * @param Coordinate3D object
     */
    void printValuesX_Y_Z(Coordinate3D values);
};

#endif // COORDINATE3D_HPP