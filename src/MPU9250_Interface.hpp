/**
 * @file
 * @brief     MPU9250Interface Class
 * @author    Quinten Perquin
 * @license   See LICENSE
 */

#ifndef MPU9250_INTERFACE_HPP
#define MPU9250_INTERFACE_HPP

class MPU9250Interface
{
public:
    MPU9250Interface( hwlib::target::pin_oc & sda, hwlib::target::pin_oc & scl ):
        sda ( sda ),
		scl ( scl ),
		MPU_addr ( 0x68 ),
		i2c ( hwlib::i2c_bus_bit_banged_scl_sda( scl, sda ) )
    {}

    void init();
    void print();

private:
    hwlib::target::pin_oc & sda;
	hwlib::target::pin_oc & scl;
    const int8_t MPU_addr;
    hwlib::i2c_bus_bit_banged_scl_sda i2c;

};

#endif