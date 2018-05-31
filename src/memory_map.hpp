#ifndef MEMORY_MAP_HPP
#define MEMORY_MAP_HPP

/**
 * @file        memory_map.hpp
 * @brief       This header will contain memory addresses for the MPU9250
 * @author      Renske Kuip
 * @license     MIT
 */

enum addresses : uint8_t {
    MPUREG_USER_CTRL = 0x6A,
    MPUREG_I2C_MST_CTRL = 0x24,

    AK8963_I2C_ADDR = 0x0c,
    AK8963_CNTL1 = 0x0A,
    AK8963_CNTL2 = 0x0B,

    MPUREG_I2C_SLV0_ADDR = 0x25,
    MPUREG_I2C_SLV0_CTRL = 0x27,
    MPUREG_I2C_SLV0_DO = 0x63,
    MPUREG_I2C_SLV0_REG = 0x26,
    MPUREG_EXT_SENS_DATA = 0x49,
    INT_PIN_CFG = 0x37,
    READ_FLAG = 0x80

};

#endif // MEMORY_MAP_HPP