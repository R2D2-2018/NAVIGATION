/**
 * @file
 * @brief     MPU9250Interface Class
 * @author    Renske Kuip
 * @license   See LICENSE
 */

#include "src/MPU9250_Interface.hpp"

void MPU9250Interface::init(){
    uint8_t data[12] = {0x3B};

    int16_t accel_temp[3] = {0, 0, 0}, gyro_temp[3] = {0, 0, 0};

    i2c.write(MPU_addr, data, 1);
	i2c.read(MPU_addr, data, 12);

    accel_temp[0] = (((int16_t)data[0] << 8) | (int16_t)data[1]);
	accel_temp[1] = (((int16_t)data[2] << 8) | (int16_t)data[3]);
	accel_temp[2] = (((int16_t)data[4] << 8) | (int16_t)data[5]);
	gyro_temp[0] = (((int16_t)data[6] << 8) | (int16_t)data[7]);
	gyro_temp[1] = (((int16_t)data[8] << 8) | (int16_t)data[9]);
	gyro_temp[2] = (((int16_t)data[10] << 8) | (int16_t)data[11]);
    print(accel_temp, gyro_temp);
}

void MPU9250Interface::print(int16_t accel_temp, int16_t gyro_temp){
    hwlib::cout 
		<< "accel_x: "<< accel_temp[0] << '\t' 
		<< "accel_y: "<< accel_temp[1] << '\t' 
		<< "accel_x: "<< accel_temp[2] << '\t'  
		<< "gyro_x: " << gyro_temp[0]  << '\t' 
		<< "gyro_y: " << gyro_temp[1]  << '\t' 
		<< "gyro_z: " << gyro_temp[2]  << '\n';
}