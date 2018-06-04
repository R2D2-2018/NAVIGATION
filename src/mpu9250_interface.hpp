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
     */
    void getAccel();
    /**
     * @brief Get the Gyroscope values
     *
     */
    void getGyro();
    /**
     * @brief Get the Magnetometer values
     *
     */
    void getMagn();

    /**
     * @brief Prints values of the given int16_t array in the format "X:% Y:% Z:%"
     *
     * @param temp int16_t array with 3 values
     */
    void printValuesX_Y_Z(int16_t temp[3]);
    /**
     * @brief Prints values of the given int32_t array in the format "X:% Y:% Z:%"
     *
     * @param temp int32_t array with 3 values
     */
    void printValuesX_Y_Z(int32_t temp[3]);

    /**
     * @brief Function to print the MPU9250 data for debug purposes
     *
     */
    void debug();

  private:
    hwlib::pin_oc &scl;
    hwlib::pin_oc &sda;
    const int8_t MPUAddr;
    hwlib::i2c_bus_bit_banged_scl_sda i2c;

    int16_t accelValue[3] = {0, 0, 0};
    int16_t gyroValue[3] = {0, 0, 0};
    int16_t magnValue[3] = {0, 0, 0};
};

#endif