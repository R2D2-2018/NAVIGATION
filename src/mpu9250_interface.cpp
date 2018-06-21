/**
 * @file
 * @brief     MPU9250Interface Class
 * @author    Renske Kuip and Jeroen van Hattem
 * @license   See LICENSE
 */

#include "mpu9250_interface.hpp"
#include "memory_map.hpp"

MPU9250Interface::MPU9250Interface(hwlib::pin_oc &scl, hwlib::pin_oc &sda, const int8_t MPUAddr)
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

    initializeAK8963(&magnetometerCalibrateValues);

    hwlib::wait_ms(10);

    hwlib::wait_us(10000);

    i2c.write(INT_PIN_CFG, bypass, 1); // set bypass mode
}

void MPU9250Interface::initializeAK8963(Coordinate3D<float> *destination) {
    // First extract the factory calibration for each magnetometer axis
    uint8_t rawData[3] = {AK8963_CNTL};       // x/y/z gyro calibration data stored here
    i2c.write(AK8963_ADDRESS, rawData, 0x00); // Power down magnetometer
    hwlib::wait_ms(10);
    i2c.write(AK8963_ADDRESS, rawData, 0x0F); // Enter Fuse ROM access mode
    hwlib::wait_ms(10);
    rawData[0] = {AK8963_ASAX};
    i2c.read(AK8963_ADDRESS, rawData, 3);                       // Read the x-, y-, and z - axis calibration values
    destination->setX((float)((rawData[0] - 128) / 256. + 1.)); // Return x-axis sensitivity adjustment values, etc.
    destination->setY((float)((rawData[1] - 128) / 256. + 1.));
    destination->setZ((float)((rawData[2] - 128) / 256. + 1.));
    rawData[0] = {AK8963_CNTL};
    i2c.write(AK8963_ADDRESS, rawData, 0x00); // Power down magnetometer
    hwlib::wait_ms(10);
    // Configure the magnetometer for continuous read and highest resolution
    // set Mscale bit 4 to 1 (0) to enable 16 (14) bit resolution in CNTL
    // register,
    // and enable continuous mode data acquisition Mmode (bits [3:0]), 0010 for
    // 8 Hz and 0110 for 100 Hz sample rates
    rawData[0] = {AK8963_CNTL};
    i2c.write(AK8963_ADDRESS, rawData, 0x10); // Set magnetometer data resolution and sample ODR delay(10);
}

void MPU9250Interface::calibrate() {
    accelerationCalibrateValues = getAccelerationValues();
    gyroscopeCalibrateValues = getGyroscopeValues();
    magnetometerCalibrateValues = getMagnetometerValues();
}

void MPU9250Interface::saveAccelerationValues() {
    uint8_t data[6] = {0x3B}; ///< address where MPU data starts

    i2c.write(MPUAddr, data, 1);
    i2c.read(MPUAddr, data, 6);

    // ACCEL_XOUT_H | WITH ACCEL_XOUT_L. 16bit ADC, so divided into 2 bytes. First shift the first one 8 places (1 byte) to the
    // left. Because you receive bit 15 to 8 first. Then you "OR" it with the second byte. "OR", because these places are all o.

    accelerationValues.setX(((data[0] << 8) | data[1]) / 16384);
    accelerationValues.setY(((data[2] << 8) | data[3]) / 16384);
    accelerationValues.setZ(((data[4] << 8) | data[5]) / 16384);
}

void MPU9250Interface::saveGyroscopeValues() {
    uint8_t data[6] = {0x43}; ///< address where MPU data starts

    i2c.write(MPUAddr, data, 1); // Write 1 byte to MPU
    i2c.read(MPUAddr, data, 6);  // Read 6

    // float q[4] = {1.0f, 0.0f, 0.0f, 0.0f};
    // float pitch; // Gyroscope rotation over the lateral axis (X)
    // float yaw;   // Gyroscope rotation over the vertical axis (Y)
    // float roll;  // Gyroscope rotation over the longitudinal axis (Z)
    float gRes = 250.0 / 32768.0;

    i2c.write(MPUAddr, data, 1);
    i2c.read(MPUAddr, data, 6);

    // yaw = atan2(2.0f * (q[1] * q[2] + q[0] * q[3]), q[0] * q[0] + q[1] * q[1] - q[2] * q[2] - q[3] * q[3]);
    // pitch = -asin(2.0f * (q[1] * q[3] - q[0] * q[2]));
    // roll = atan2(2.0f * (q[0] * q[1] + q[2] * q[3]), q[0] * q[0] - q[1] * q[1] - q[2] * q[2] + q[3] * q[3]);
    // pitch *= 180.0f / M_PI;
    // yaw *= 180.0f / M_PI;
    // yaw -= 13.8; // Declination at Danville, California is 13 degrees 48 minutes and 47 seconds on 2014-04-04
    // roll *= 180.0f / M_PI;

    // ACCEL_XOUT_H | WITH ACCEL_XOUT_L. 16bit ADC, so divided into 2 bytes. First shift the first one 8 places (1 byte) to the
    // left. Because you receive bit 15 to 8 first. Then you "OR" it with the second byte. "OR", because these places are all o.
    float x = ((data[0] << 8) | data[1]);
    float y = ((data[2] << 8) | data[3]);
    float z = ((data[4] << 8) | data[5]);

    float realValueX = (float)x * gRes; // get actual gyro value, this depends on scale being set
    float realValueY = (float)y * gRes;
    float realValueZ = (float)z * gRes;

    gyroscopeValues.setX(realValueX);
    gyroscopeValues.setY(realValueY);
    gyroscopeValues.setZ(realValueZ);
    // gyroscopeValues.setX(x);
    // gyroscopeValues.setY(y);
    // gyroscopeValues.setZ(z);
}

void MPU9250Interface::saveMagnetometerValues() {
    float rawX = 0.0;
    float rawY = 0.0;
    float rawZ = 0.0;

    float magCalibration[3] = {0, 0, 0};
    float magBias[3] = {0, 0, 0};
    float mRes = 10. * 4912. / 32760.0;

    magBias[0] = +470.; // User environmental x-axis correction in milliGauss, should be automatically calculated
    magBias[1] = +120.; // User environmental x-axis correction in milliGauss
    magBias[2] = +125.; // User environmental x-axis correction in milliGauss

    uint8_t startByte[1] = {AK8963_ST1};
    i2c.read(MPUAddr, startByte, 1);

    // must start your read from AK8963A register 0x03 and read seven bytes so that upon read of ST2 register 0x09 the AK8963A
    // will unlatch the data registers for the next measurement

    uint8_t data[7] = {AK8963_XOUT_L}; // I2C slave 0 register address for AK8963 data

    if (startByte[0] & 0x01) { // Startbyte
        i2c.read(MPUAddr, data, 7);
        uint8_t c = data[6];
        if (!(c & 0x08)) { // Check if magnetometer sensor overflow set, if not then report data
            rawX = ((int16_t)data[1] << 8) | data[0];
            rawY = ((int16_t)data[3] << 8) | data[2];
            rawZ = (int16_t)(data[5] << 8) | data[4];
        }
    }

    float correctedX = rawX; // * mRes * magCalibration[0] - magBias[0];
    float correctedY = rawY; // * mRes * magCalibration[1] - magBias[1];
    float correctedZ = rawZ; // * mRes * magCalibration[2] - magBias[2];

    magnetometerValues.setX(correctedX);
    magnetometerValues.setY(correctedY);
    magnetometerValues.setZ(correctedZ);
}

Coordinate3D<float> MPU9250Interface::getAccelerationValues() {
    saveAccelerationValues();
    return accelerationValues;
}

Coordinate3D<float> MPU9250Interface::getGyroscopeValues() {
    saveGyroscopeValues();
    return gyroscopeValues;
}

Coordinate3D<float> MPU9250Interface::getMagnetometerValues() {
    saveMagnetometerValues();
    return magnetometerValues;
}

Coordinate3D<float> MPU9250Interface::getAccelerationCalibrateValues() {
    return accelerationCalibrateValues;
}

Coordinate3D<float> MPU9250Interface::getGyroscopeCalibrateValues() {
    return gyroscopeCalibrateValues;
}

Coordinate3D<float> MPU9250Interface::getMagnetometerCalibrateValues() {
    return magnetometerCalibrateValues;
}

void MPU9250Interface::printValuesX_Y_Z(Coordinate3D<float> values) {
    // hwlib::cout << hwlib::right << "X: " << values.getX() << " Y: " << values.getY() << " Z: " << values.getZ() << hwlib::endl;
}