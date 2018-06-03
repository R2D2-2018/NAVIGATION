/**
 * @file
 * @brief     MPU9250Interface Class
 * @author    Quinten Perquin
 * @license   See LICENSE
 */

#ifndef MPU9250_INTERFACE_HPP
#define MPU9250_INTERFACE_HPP

#include "wrap-hwlib.hpp"

class MPU9250Interface {
  public:
    MPU9250Interface(hwlib::pin_oc &scl, hwlib::pin_oc &sda, const int8_t MPUAddr)
        : scl(scl), sda(sda), MPUAddr(MPUAddr), i2c(hwlib::i2c_bus_bit_banged_scl_sda(scl, sda)) {
    }

    /**
     * @brief Initializes MPU object
     *
     * Function to inizialize the i2c bus for the MPU
     * and reading/printing values from the MPU
     *
     */
    void init();

    /**
     * @brief Get the Accelerator values
     *
     * Sets accelValue on current values as {x,y,z}
     */
    void getAccel();
    /**
     * @brief Get the Gyroscope values
     *
     * Sets gyrolValue on current values as {x,y,z}
     */
    void getGyro();
    /**
     * @brief Get the Magnetometer values
     *
     * Sets magnValue on current values as {x,y,z}
     */
    void getMagn();

    /**
     * @brief Converts raw accelerator data to m/s
     *
     * @param temp array of raw data (x,y,z)
     */
    int16_t *accelConvert(int16_t temp[3]);
    /**
     * @brief Converts raw gyroscope data to degrees/s of rotation speed
     *
     * @param temp array of raw data (x,y,z)
     */
    int16_t *gyroConvert(int16_t temp[3]);
    /**
     * @brief Converts raw magnetometer data to direction change in degrees
     *
     * @param temp array of raw data (x,y,z)
     */
    int16_t magnConvert(int16_t temp[3]);

    /**
     * @brief Prints values of the given int16_t array in the format "X:% Y:% Z:%"
     *
     * @param temp int16_t array with int16_t temp[3]3 values
     */
    void printValuesXYZ(int16_t temp[3]);

    void print(int16_t *temp);

  private:
    hwlib::pin_oc &scl;
    hwlib::pin_oc &sda;
    const int8_t MPUAddr;
    hwlib::i2c_bus_bit_banged_scl_sda i2c;

    int16_t *accelValue[3] = {0, 0, 0};
    int16_t *gyroValue[3] = {0, 0, 0};
    int16_t magnValue = 0;

    int accelGravitySettings = 2; ///< accelerator data is in 2G limit
    int16_t accelScaling = 16384; ///< default for 2G
    int16_t gyroScaling = 131;    ///< default is 131
};

#endif