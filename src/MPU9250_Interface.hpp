/**
 * @file
 * @brief     MPU9250Interface Class
 * @author    Quinten Perquin
 * @license   See LICENSE
 */

#ifndef MPU9250_INTERFACE_HPP
#define MPU9250_INTERFACE_HPP

#include "wrap-hwlib.hpp"

class MPU9250Interface
{
public:
    MPU9250Interface(  hwlib::target::pin_oc & scl, hwlib::target::pin_oc & sda ):
        scl ( scl ),
        sda ( sda ),
		MPU_addr ( 0x68 ),
		i2c ( hwlib::i2c_bus_bit_banged_scl_sda( scl, sda ) )
    {}

    void init();
    void magn_read();
    void print(int16_t  accel_temp[3], int16_t gyro_temp[3]);

private:
    hwlib::target::pin_oc & scl;
    hwlib::target::pin_oc & sda;
    const int8_t MPU_addr;
    hwlib::i2c_bus_bit_banged_scl_sda i2c;

};

#endif