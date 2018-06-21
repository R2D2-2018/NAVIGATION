/**
 * @file
 * @brief     MPU9250Interface Class
 * @author    Renske Kuip and Jeroen van Hattem
 * @license   See LICENSE
 */

#include "mpu9250_interface.hpp"
#include "memory_map.hpp"

MPU9250Interface::MPU9250Interface(hwlib::pin_oc &scl, hwlib::pin_oc &sda, const uint8_t MPUAddr)
    : scl(scl), sda(sda), MPUAddr(MPUAddr), i2c(hwlib::i2c_bus_bit_banged_scl_sda(scl, sda)) {

    hwlib::cout << hwlib::right << "Initializing MPU9250..." << hwlib::endl;

    uint8_t data[7] = {0x03}; ///< I2C slave 0 register address for AK8963  data
    uint8_t magnReadFlag[1] = {0x0C | 0x80}, readData[1] = {0x87}, continious[1] = {0x06}, bypass[1] = {0x22};
    /// All the I2C data addresses are pointers, because HWLIB only accepts them as such

    i2c.write(AK8963_CNTL1, continious, 1);           // start continious mode AK8963
    i2c.write(MPUREG_I2C_SLV0_ADDR, magnReadFlag, 1); // Set the I2C slave addres of AK8963 and set for read.
    i2c.write(MPUREG_I2C_SLV0_REG, data, 1);          // I2C slave 0 register address from where to begin data transfe
    i2c.write(MPUREG_I2C_SLV0_CTRL, readData, 1);     // Read 6 bytes from the magnetometer

    // TODO
    //
    // Write 0x02 to address 0x37 to enable I2C bypass to read magnetometer.
    //
    // END

    hwlib::wait_us(10000);

    i2c.write(INT_PIN_CFG, bypass, 1); // set bypass mode
}

void MPU9250Interface::calibrate() {
    hwlib::cout << "Calibrating the Acceleration, gyro and magnetsensor" << hwlib::endl;
    for (int i = 0; i < 10; i++) {
        accelerationCalibrateValues = (accelerationCalibrateValues / 2) + (getAccelerationValues() / 2);
        gyroscopeCalibrateValues = (gyroscopeCalibrateValues / 2) + (getGyroscopeValues() / 2);
        magnetometerCalibrateValues = (magnetometerCalibrateValues / 2) + (getMagnetometerValues() / 2);
        hwlib::wait_ms(100);
    }
    accelerationCalibrateValues.setZ(accelerationCalibrateValues.getZ() + 16384);
}

Coordinate3D MPU9250Interface::getAccelerationCalibrateValues() {
    return accelerationCalibrateValues;
}

Coordinate3D MPU9250Interface::getGyroscopeCalibrateValues() {
    return gyroscopeCalibrateValues;
}

Coordinate3D MPU9250Interface::getMagnetometerCalibrateValues() {
    return magnetometerCalibrateValues;
}

Coordinate3D MPU9250Interface::getAccelerationValues() {
    uint8_t data[6] = {0x3B}; ///< address where MPU data starts
    Coordinate3D values;
    i2c.write(MPUAddr, data, 1);
    i2c.read(MPUAddr, data, 6);

    // ACCEL_XOUT_H | WITH ACCEL_XOUT_L. 16bit ADC, so divided into 2 bytes. First shift the first one 8 places (1 byte) to the
    // left. Because you receive bit 15 to 8 first. Then you "OR" it with the second byte. "OR", because these places are all o.
    values.setX((static_cast<int16_t>(data[0] << 8) | static_cast<int16_t>(data[1])));
    values.setY((static_cast<int16_t>(data[2] << 8) | static_cast<int16_t>(data[3])));
    values.setZ((static_cast<int16_t>(data[4] << 8) | static_cast<int16_t>(data[5])));

    return values;
}

Coordinate3D MPU9250Interface::getGyroscopeValues() {
    uint8_t data[6] = {0x43}; ///< address where MPU data starts
    Coordinate3D values;

    i2c.write(MPUAddr, data, 1);
    i2c.read(MPUAddr, data, 6);

    values.setX((static_cast<int16_t>(data[0] << 8) | static_cast<int16_t>(data[1])));
    values.setY((static_cast<int16_t>(data[2] << 8) | static_cast<int16_t>(data[3])));
    values.setZ((static_cast<int16_t>(data[4] << 8) | static_cast<int16_t>(data[5])));

    return values;
}

void MPU9250Interface::saveAccelerationValues() {
    uint8_t data[6] = {0x3B}; ///< address where MPU data starts (SHOULD BE 43)

    i2c.write(MPUAddr, data, 1);
    i2c.read(MPUAddr, data, 6);

    accelerationValues.setX((static_cast<int16_t>(data[0] << 8) | static_cast<int16_t>(data[1])));
    accelerationValues.setY((static_cast<int16_t>(data[2] << 8) | static_cast<int16_t>(data[3])));
    accelerationValues.setZ((static_cast<int16_t>(data[4] << 8) | static_cast<int16_t>(data[5])));
}

void MPU9250Interface::saveGyroscopeValues() {
    uint8_t data[6] = {0x43}; ///< address where MPU data starts

    i2c.write(MPUAddr, data, 1); // Write 1 byte to MPU
    i2c.read(MPUAddr, data, 6);  // Read 12

    gyroscopeValues.setX((static_cast<int16_t>(data[0] << 8) | static_cast<int16_t>(data[1])));
    gyroscopeValues.setY((static_cast<int16_t>(data[2] << 8) | static_cast<int16_t>(data[3])));
    gyroscopeValues.setZ((static_cast<int16_t>(data[4] << 8) | static_cast<int16_t>(data[5])));
}

Coordinate3D MPU9250Interface::getMagnetometerValues() {
    uint8_t data[7] = {0x03}; ///< I2C slave 0 register address for AK8963  data
    Coordinate3D values;

    while (magnetometerValues.getX() == 0 && magnetometerValues.getY() == 0 && magnetometerValues.getZ() == 0) {
        i2c.read(MPUAddr, data, 7);
        // must start your read from AK8963A register 0x03 and read seven bytes so that upon read of ST2 register 0x09 the AK8963A
        // will unlatch the data registers for the next measurement
        uint8_t c = data[6]; // end data read by reading ST2

        if (!(c & 0x08)) { // Check if magnetometer sensor overflow set, if not then report data
            values.setX((static_cast<int16_t>(data[1] << 8) | static_cast<int16_t>(data[0])));
            values.setY((static_cast<int16_t>(data[3] << 8) | static_cast<int16_t>(data[2])));
            values.setZ((static_cast<int16_t>(data[5] << 8) | static_cast<int16_t>(data[4])));
            magnetometerValues.setX((static_cast<int16_t>(data[1] << 8) | static_cast<int16_t>(data[0])));
            magnetometerValues.setY((static_cast<int16_t>(data[3] << 8) | static_cast<int16_t>(data[2])));
            magnetometerValues.setZ((static_cast<int16_t>(data[5] << 8) | static_cast<int16_t>(data[4])));
        }
    }
    return values;
}

void MPU9250Interface::printValuesX_Y_Z(Coordinate3D values) {
    hwlib::cout << " X: " << values.getX() << "\r\n"
                << " Y: " << values.getY() << "\r\n"
                << " Z: " << values.getZ() << hwlib::endl;
}

void MPU9250Interface::printAccelerationGravity() {
    saveAccelerationValues();
    Coordinate3D accelerationCalibrated = accelerationValues - accelerationCalibrateValues;
    printAccelerationGravity(accelerationCalibrated);
}

void MPU9250Interface::printAccelerationGravity(Coordinate3D acceleration) {
    int x = static_cast<int>((acceleration.getX() * 100) * accelRes);
    int y = static_cast<int>((acceleration.getY() * 100) * accelRes);
    int z = static_cast<int>((acceleration.getZ() * 100) * accelRes);
    hwlib::cout << " X: " << x << "/m/s/100\r\n"
                << " Y: " << y << "/m/s/100\r\n"
                << " Z: " << z << "/m/s/100\r\n";
}

void MPU9250Interface::printGyroscopeDegreeSec() {
    saveGyroscopeValues();
    Coordinate3D gyroscopeCalibrated = gyroscopeValues - gyroscopeCalibrateValues;
    printGyroscopeDegreeSec(gyroscopeCalibrated);
}

void MPU9250Interface::printGyroscopeDegreeSec(Coordinate3D gyroscope) {
    int x = static_cast<int>(gyroscope.getX() * gyroRes);
    int y = static_cast<int>(gyroscope.getY() * gyroRes);
    int z = static_cast<int>(gyroscope.getZ() * gyroRes);
    hwlib::cout << " X: " << x << "/degree/s\r\n"
                << " Y: " << y << "/degree/s\r\n"
                << " Z: " << z << "/degree/s\r\n";
}