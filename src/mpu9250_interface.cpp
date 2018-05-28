/**
 * @file
 * @brief     MPU9250Interface Class
 * @author    Renske Kuip
 * @license   See LICENSE
 */

#include "mpu9250_interface.hpp"
#include "memory_map.hpp"

void MPU9250Interface::init() {
    hwlib::cout << hwlib::right << "Initializing MPU9250..." << hwlib::endl;
    /*for (;;) {
        getAccel();
        getGyro();
        getMagn();
    }*/
    uint8_t data[7] = {0x03}; ///< I2C slave 0 register address for AK8963  data
    uint8_t magnReadFlag[1] = {0x0C | 0x80}, readData[1] = {0x87}, continious[1] = {0x06};

    i2c.write(AK8963_CNTL1, continious, 1);           // start continious mode AK8963
    i2c.write(MPUREG_I2C_SLV0_ADDR, magnReadFlag, 1); // Set the I2C slave addres of AK8963 and set for read.
    i2c.write(MPUREG_I2C_SLV0_REG, data, 1);          // I2C slave 0 register address from where to begin data transfe
    i2c.write(MPUREG_I2C_SLV0_CTRL, readData, 1);     // Read 6 bytes from the magnetometer

    hwlib::wait_us(10000);

    uint8_t bypass[1] = {0x22};
    i2c.write(INT_PIN_CFG, bypass, 1); // set bypass mode
}

void MPU9250Interface::getAccel() {
    uint8_t data[6] = {0x3B}; ///< address where MPU data starts

    i2c.write(MPUAddr, data, 1);
    i2c.read(MPUAddr, data, 6);

    accelValue[0] = (((int16_t)data[0] << 8) | (int16_t)data[1]);
    accelValue[1] = (((int16_t)data[2] << 8) | (int16_t)data[3]);
    accelValue[2] = (((int16_t)data[4] << 8) | (int16_t)data[5]);

    printValuesX_Y_Z(accelValue);
}

void MPU9250Interface::getGyro() {
    uint8_t data[12] = {0x3B}; ///< address where MPU data starts

    i2c.write(MPUAddr, data, 1);
    i2c.read(MPUAddr, data, 12);

    gyroValue[0] = (((int16_t)data[6] << 8) | (int16_t)data[7]);
    gyroValue[1] = (((int16_t)data[8] << 8) | (int16_t)data[9]);
    gyroValue[2] = (((int16_t)data[10] << 8) | (int16_t)data[11]);

    printValuesX_Y_Z(gyroValue);
}

void MPU9250Interface::getMagn() {
    uint8_t data[7] = {0x03}; ///< I2C slave 0 register address for AK8963  data

    while (magnValue[0] == 0 && magnValue[1] == 0 && magnValue[2] == 0) {
        i2c.read(MPUAddr, data, 7);
        // must start your read from AK8963A register 0x03 and read seven bytes so that upon read of ST2 register 0x09 the AK8963A
        // will unlatch the data registers for the next measurement
        uint8_t c = data[6]; // end data read by reading ST2

        if (!(c & 0x08)) { // Check if magnetic sensor overflow set, if not then report data
            magnValue[0] = ((int16_t)data[1] << 8) | (int16_t)data[0];
            magnValue[1] = ((int16_t)data[3] << 8) | (int16_t)data[2];
            magnValue[2] = ((int16_t)data[5] << 8) | (int16_t)data[4];
        }
    }
    printValuesX_Y_Z(magnValue);
}

void MPU9250Interface::printValuesX_Y_Z(int16_t temp[3]) {
    hwlib::cout << hwlib::right << "X: " << temp[0] << " Y: " << temp[1] << " Z: " << temp[2] << hwlib::endl;
}

void MPU9250Interface::printValuesX_Y_Z(int32_t temp[3]) {
    hwlib::cout << "X: " << temp[0] << " Y: " << temp[1] << " Z: " << temp[2] << hwlib::endl;
}