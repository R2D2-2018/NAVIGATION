/**
 * @file
 * @brief     MPU9250Interface Class
 * @author    Renske Kuip
 * @license   See LICENSE
 */

#include "MPU9250_Interface.hpp"
#include "memory_map.hpp"

/**
 * @brief
 *
 */
void MPU9250Interface::init() {
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

    int32_t accel_bias[3] = {0, 0, 0};
    int32_t gyro_bias[3] = {0, 0, 0};
    accel_bias[0] += (int32_t)accel_temp[0];
    accel_bias[1] += (int32_t)accel_temp[1];
    accel_bias[2] += (int32_t)accel_temp[2];
    gyro_bias[0] += (int32_t)gyro_temp[0];
    gyro_bias[1] += (int32_t)gyro_temp[1];
    gyro_bias[2] += (int32_t)gyro_temp[2];

    print(accel_temp, gyro_temp);
    for (;;) {
        hwlib::wait_ms(500);
        magnReadSlave();
    }
}

/**
 * @brief
 *
 */
void MPU9250Interface::magnRead() {
    uint8_t magn_addr = {0X0C};
    uint8_t bypass_addr = {0x37};
    uint8_t data[6] = {0x03};
    int16_t magn_read[3] = {0, 0, 0};

    uint8_t req[1] = {0x0A};
    i2c.write(magn_addr, req, 0x01);

    i2c.write(bypass_addr, data, 1); // enable bypass mode for magnetometer
    i2c.write(magn_addr, data, 1);
    i2c.read(magn_addr, data, 6);

    magn_read[0] = -(((int16_t)data[3] << 8) | (int16_t)data[2]);
    magn_read[1] = -(((int16_t)data[1] << 8) | (int16_t)data[0]);
    magn_read[2] = -(((int16_t)data[5] << 8) | (int16_t)data[4]);

    hwlib::cout << "magn_x " << magn_read[0] << " "
                << "magn_y " << magn_read[1] << " "
                << "magn_z " << magn_read[2] << "\n";
}

/**
 * @brief
 *
 */
void MPU9250Interface::magnReadSlave() {
    uint8_t AK8963_ST1[1] = {0x02};

    uint8_t data[7] = {0x03};
    int16_t bit_data[3] = {0, 0, 0};

    bool newMagData = false;
    i2c.read(AK8963_I2C_ADDR, AK8963_ST1, 1);
    newMagData = (AK8963_ST1[0] & 0x01);

    if (newMagData == true) {

        // i2c.write(MPU_addr, data, 1);
        i2c.read(AK8963_I2C_ADDR, data, 7);

        uint8_t c = data[6];
        // hwlib::cout << " c: " << (int)c;
        if (!(c & 0x08)) {
            bit_data[0] = (((int16_t)data[1] << 8) | (int16_t)data[0]);
            bit_data[1] = (((int16_t)data[3] << 8) | (int16_t)data[2]);
            bit_data[2] = (((int16_t)data[5] << 8) | (int16_t)data[4]);

            hwlib::cout << " data: " << bit_data[0] << " " << bit_data[1] << " " << bit_data[2] << " ";
        }
    }
}

int16_t MPU9250_Interface::getAccel() {
}

int16_t MPU9250_Interface::getGyro() {
}

int16_t MPU9250_Interface::getMagn() {
}

/**
 * @brief
 *
 * @param accel_temp
 * @param gyro_temp
 */
void MPU9250Interface::print(int16_t accel_temp[3], int16_t gyro_temp[3]) {
    hwlib::cout << "accel_x: " << accel_temp[0] << ' ' << "accel_y: " << accel_temp[1] << ' ' << "accel_x: " << accel_temp[2] << ' '
                << "gyro_x: " << gyro_temp[0] << ' ' << "gyro_y: " << gyro_temp[1] << ' ' << "gyro_z: " << gyro_temp[2] << '\n';
}