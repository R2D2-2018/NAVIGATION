/**
 * @file
 * @brief     MPU9250Interface Class
 * @author    Renske Kuip
 * @license   See LICENSE
 */

#include "mpu9250_interface.hpp"
#include "memory_map.hpp"

void MPU9250Interface::init() {
    hwlib::cout << "Initializing MPU9250..." << hwlib::endl;

    uint8_t data[7] = {0x03}; ///< I2C slave 0 register address for AK8963  data
    uint8_t magnReadFlag[1] = {0x0C | 0x80}, readData[1] = {0x87}, continuous[1] = {0x06}, bypass[1] = {0x22};
    /// All the I2C data addresses are pointers, because HWLIB only accepts them as such
    i2c.write(INT_PIN_CFG, bypass, 1);                // set bypass mode
    i2c.write(AK8963_CNTL1, continuous, 1);           // start continious mode AK8963
    i2c.write(MPUREG_I2C_SLV0_ADDR, magnReadFlag, 1); // Set the I2C slave addres of AK8963 and set for read.
    i2c.write(MPUREG_I2C_SLV0_REG, data, 1);          // I2C slave 0 register address from where to begin data transfe
    i2c.write(MPUREG_I2C_SLV0_CTRL, readData, 1);     // Read 6 bytes from the magnetometer

    hwlib::wait_us(10000);
}

void MPU9250Interface::getAccel() {
    uint8_t data[6] = {0x3B}; ///< address where MPU data starts

    i2c.write(MPUAddr, data, 1);
    i2c.read(MPUAddr, data, 6);

    accelValue[0] = (((int16_t)data[0] << 8) | (int16_t)data[1]);
    accelValue[1] = (((int16_t)data[2] << 8) | (int16_t)data[3]);
    accelValue[2] = (((int16_t)data[4] << 8) | (int16_t)data[5]);
    accelValue[0] -= accelBias[0];
    accelValue[1] -= accelBias[1];
    accelValue[2] -= accelBias[2];
}

void MPU9250Interface::getGyro() {
    uint8_t data[12] = {0x3B}; ///< address where MPU data starts

    i2c.write(MPUAddr, data, 1); // Write 1 byte to MPU

    i2c.read(MPUAddr, data, 12); // Read 12

    gyroValue[0] = (((int16_t)data[6] << 8) | (int16_t)data[7]); // Convert uint8_t data (high and low) into int16_t
    gyroValue[1] = (((int16_t)data[8] << 8) | (int16_t)data[9]);
    gyroValue[2] = (((int16_t)data[10] << 8) | (int16_t)data[11]);
    gyroValue[0] -= gyroBias[0];
    gyroValue[1] -= gyroBias[1];
    gyroValue[2] -= gyroBias[2];
}

void MPU9250Interface::getMagn() {
    magnValue[0] = 0;
    magnValue[1] = 0;
    magnValue[2] = 0;
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
    // printValuesX_Y_Z(magnValue);
}

void MPU9250Interface::calibrateAccelerometer() {
    uint16_t accelSensitivity = 16384; // = 16384 LSB/g
    int sampleCount = 100;
    for (int i = 0; i < sampleCount; i++) {
        int16_t accelTemp[3] = {0, 0, 0};
        getAccel();
        accelTemp[0] = accelValue[0];
        accelTemp[1] = accelValue[1];
        accelTemp[2] = accelValue[2];

        accelBias[0] += (int32_t)accelTemp[0];
        accelBias[1] += (int32_t)accelTemp[1];
        accelBias[2] += (int32_t)accelTemp[2];
    }
    accelBias[0] /= (int32_t)sampleCount;
    accelBias[1] /= (int32_t)sampleCount;
    accelBias[2] /= (int32_t)sampleCount;

    if (accelBias[2] > 0L) {
        accelBias[2] -= (int32_t)accelSensitivity;
    } // Remove gravity from the z-axis accelerometer bias calculation
    else {
        accelBias[2] += (int32_t)accelSensitivity;
    }

    // accelBias[0] = accelBias[0] / accelSensitivity;
    // accelBias[1] = accelBias[1] / accelSensitivity;
    // accelBias[2] = accelBias[2] / accelSensitivity;
    printValuesX_Y_Z(accelBias);
}

void MPU9250Interface::calibrateGyroscope() {
    uint16_t gyroSensitivity = 131; // = 131 LSB/degrees/sec
    int sampleCount = 100;
    for (int i = 0; i < sampleCount; i++) {
        int16_t gyroTemp[3] = {0, 0, 0};
        getGyro();
        gyroTemp[0] = gyroValue[0];
        gyroTemp[1] = gyroValue[1];
        gyroTemp[2] = gyroValue[2];
        gyroBias[0] += (int32_t)gyroTemp[0];
        gyroBias[1] += (int32_t)gyroTemp[1];
        gyroBias[2] += (int32_t)gyroTemp[2];
    }
    gyroBias[0] /= (int32_t)sampleCount;
    gyroBias[1] /= (int32_t)sampleCount;
    gyroBias[2] /= (int32_t)sampleCount;

    // gyroBias[0] = (float)gyroBias[0] / (float)gyroSensitivity;
    // gyroBias[1] = (float)gyroBias[1] / (float)gyroSensitivity;
    // gyroBias[2] = (float)gyroBias[2] / (float)gyroSensitivity;
    printValuesX_Y_Z(gyroBias);
}

void MPU9250Interface::calibrateMagnetometer() {
    int16_t maxValues[3] = {-32767, -32767, -32767};
    int16_t minValues[3] = {32767, 32767, 32767};
    int16_t tempValues[3] = {0, 0, 0};
    for (int i = 0; i < 1500; i++) {
        getMagn();
        for (int j = 0; j < 3; j++) {
            tempValues[j] = magnValue[j];
        }
        for (int j = 0; j < 3; j++) {
            if (tempValues[j] < minValues[j]) {
                minValues[j] = tempValues[j];
            }
            if (tempValues[j] > maxValues[j]) {
                maxValues[j] = tempValues[j];
            }
        }
        hwlib::wait_us(12000);
    }
    for (int i = 0; i < 3; i++) {
        magnetBias[i] = (minValues[i] + maxValues[i]) / 2;
    }
    hwlib::cout << "Done calibrating." << hwlib::endl;
    printValuesX_Y_Z(magnetBias);
}

void MPU9250Interface::printValuesX_Y_Z(int16_t temp[3]) {
    hwlib::cout << "X: " << temp[0] << " Y: " << temp[1] << " Z: " << temp[2] << hwlib::endl;
}

void MPU9250Interface::printValuesX_Y_Z(int32_t temp[3]) {
    hwlib::cout << "X: " << temp[0] << " Y: " << temp[1] << " Z: " << temp[2] << hwlib::endl;
}

void MPU9250Interface::debug() {
    for (;;) {
        getAccel();
        printValuesX_Y_Z(accelValue);
        getGyro();
        printValuesX_Y_Z(gyroValue);
        getMagn();
        printValuesX_Y_Z(magnValue);
    }
}