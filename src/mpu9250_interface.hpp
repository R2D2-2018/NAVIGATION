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
    float mRes = 10. * 4912. / 32760.0;
    hwlib::pin_oc &scl;
    hwlib::pin_oc &sda;
    const int8_t MPUAddr;
    // uint8_t Mscale = MFS_16BITS; // Choose either 14-bit or 16-bit magnetometer resolution
    uint8_t Mmode = 0x06;

    hwlib::i2c_bus_bit_banged_scl_sda i2c;

    Coordinate3D<float> accelerationCalibrateValues;
    Coordinate3D<float> gyroscopeCalibrateValues;
    Coordinate3D<float> magnetometerCalibrateValues;

    Coordinate3D<float> accelerationValues;
    Coordinate3D<float> gyroscopeValues;
    Coordinate3D<float> magnetometerValues;

  public:
    MPU9250Interface(hwlib::pin_oc &scl, hwlib::pin_oc &sda, const int8_t MPUAddr);

    void initializeAK8963(Coordinate3D<float> *destination);
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
    Coordinate3D<float> getAccelerationCalibrateValues();

    /**
     * @brief Get the calibrated Coordinate3D value for the gyroscope
     *
     * Returns values as Coordinate3D {x,y,z}
     *
     * @return Coordinate3D gyroscope calibrated values
     */
    Coordinate3D<float> getGyroscopeCalibrateValues();

    /**
     * @brief Get the calibrated Coordinate3D for the Magnetometer sensor
     *
     * Returns values as Coordinate3D {x,y,z}
     *
     * @return Coordinate3D Magnetometer calibrated values
     */
    Coordinate3D<float> getMagnetometerCalibrateValues();

    /**
     * @brief Get the Accelerator values
     *
     * Returns values as Coordinate3D {x,y,z}
     *
     * @return Coordinate3D Gyroscope values
     */
    Coordinate3D<float> getAccelerationValues();

    /**
     * @brief Get the Gyroscope values
     *
     * Returns values as Coordinate3D {x,y,z}
     *
     * @return Coordinate3D Gyroscope values
     */
    Coordinate3D<float> getGyroscopeValues();

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
    Coordinate3D<float> getMagnetometerValues();
    /**
     * @brief Prints values of the given Coordinate3D object in the format "X:% Y:% Z:%"
     *
     * @param Coordinate3D object
     */
    void printValuesX_Y_Z(Coordinate3D<float> values);
};

#endif // COORDINATE3D_HPP