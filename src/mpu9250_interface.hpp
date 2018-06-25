/**
 * @file
 * @brief     MPU9250Interface Class
 * @author    Quinten Perquin and Jeroen van Hattem
 * @license   See LICENSE
 */

// REGISTER MAP:  https://cdn.sparkfun.com/assets/learn_tutorials/5/5/0/MPU-9250-Register-Map.pdf
// COMPASS:       https://devzone.nordicsemi.com/f/nordic-q-a/28414/read-mpu-9250-magnetometer/112145#112145
// GYROSCOPE:     https://www.hackster.io/30503/using-the-mpu9250-to-get-real-time-motion-data-08f011

#ifndef MPU9250_INTERFACE_HPP
#define MPU9250_INTERFACE_HPP

#include "coordinate3d.hpp"
#include "wrap-hwlib.hpp"

// Set initial input parameters
enum Ascale { AFS_2G = 0, AFS_4G, AFS_8G, AFS_16G };

enum Gscale { GFS_250DPS = 0, GFS_500DPS, GFS_1000DPS, GFS_2000DPS };
enum Mscale {
    MFS_14BITS = 0, // 0.6 mG per LSB
    MFS_16BITS      // 0.15 mG per LSB
};

class MPU9250Interface {
  private:
    hwlib::pin_oc &scl;
    hwlib::pin_oc &sda;
    const int8_t MPUAddr;

    float aRes, gRes; // scale resolutions per LSB for the sensors

    float _aRes;
    float _gRes;
    float _mRes;
    uint8_t _Mmode;

    // Specify sensor full scale
    uint8_t Gscale = GFS_250DPS;
    uint8_t Ascale = AFS_2G;
    uint8_t Mscale = MFS_16BITS; // Choose either 14-bit or 16-bit magnetometer resolution
    // uint8_t Mmode = 0x02;        // 2 for 8 Hz, 6 for 100 Hz continuous magnetometer data read

    float M_PI = 3.14159265358979323846;
    float mRes = 10. * 4912. / 32760.0;
    float pitch; // Gyroscope rotation over the lateral axis (X)
    float yaw;   // Gyroscope rotation over the vertical axis (Y)
    float roll;  // Gyroscope rotation over the longitudinal axis (Z)
    float magCalibration[3] = {0, 0, 0};

    // uint8_t Mscale = MFS_16BITS; // Choose either 14-bit or 16-bit magnetometer resolution
    uint8_t Mmode = 0x06;

    hwlib::i2c_bus_bit_banged_scl_sda i2c;

    Coordinate3D<float> accelerationCalibrateValues;
    Coordinate3D<float> gyroscopeCalibrateValues;
    Coordinate3D<float> magnetometerCalibrateValues;

    Coordinate3D<float> accelerationValues;
    Coordinate3D<float> gyroscopeValues;
    Coordinate3D<float> magnetometerValues;

  public:
    MPU9250Interface(hwlib::pin_oc &scl, hwlib::pin_oc &sda, const int8_t MPUAddr);

    void initializeAK8963(Coordinate3D<float> *destination);
    /**
     * @brief Calibrate the sensor
     *
     * Calibrate the sensor by saving the initial values. So it sets a zero.
     *
     */
    void calibrate();

    /**
     * @brief Get the Accelerator values
     *
     * Returns values as Coordinate3D {x,y,z}
     *
     * @return Coordinate3D Gyroscope values
     */
    Coordinate3D<float> getAccelerationValues();

    /**
     * @brief Get the Gyroscope values
     *
     * Returns values as Coordinate3D {x,y,z}
     *
     * @return Coordinate3D Gyroscope values
     */
    Coordinate3D<float> getGyroscopeValues();

    /**
     * @brief Get the Magnetometer values
     *
     * Returns values as Coordinate3D {x,y,z}
     *
     * @return Coordinate3D Magnetometer values
     */
    Coordinate3D<float> getMagnetometerValues();

    /**
     * @brief Get the calibrated Coordinate3D value for the acceleration
     *
     * Returns values as Coordinate3D {x,y,z}
     *
     * @return Coordinate3D acceleration calibrated values
     */
    Coordinate3D<float> getAccelerationCalibrateValues();

    /**
     * @brief Get the calibrated Coordinate3D value for the gyroscope
     *
     * Returns values as Coordinate3D {x,y,z}
     *
     * @return Coordinate3D gyroscope calibrated values
     */
    Coordinate3D<float> getGyroscopeCalibrateValues();

    /**
     * @brief Get the calibrated Magnetometer values
     *
     * Returns values as Coordinate3D {x,y,z}
     *
     * @return Coordinate3D calibrated Magnetometer values
     */
    Coordinate3D<float> getMagnetometerCalibrateValues();

    /**
     * @brief Get the Accelerator values
     *
     * Returns values as Coordinate3D {x,y,z}
     *
     * @return Coordinate3D Gyroscope values
     */
    void saveAccelerationValues();

    /**
     * @brief Get the Gyroscope values
     *
     * Returns values as Coordinate3D {x,y,z}
     *
     * @return Coordinate3D Gyroscope values
     */
    void saveGyroscopeValues();

    /**
     * @brief Get the calibrated Coordinate3D for the Magnetometer sensor
     *
     * Returns values as Coordinate3D {x,y,z}
     *
     * @return Coordinate3D Magnetometer calibrated values
     */
    void saveMagnetometerValues();

    /**
     * @brief Prints values of the given Coordinate3D object in the format "X:% Y:% Z:%"
     *
     * @param Coordinate3D object
     */
    void printValuesX_Y_Z(Coordinate3D<float> values);

    float getMres(uint8_t Mscale);

    bool checkNewMagData();
};

#endif // COORDINATE3D_HPP