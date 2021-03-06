#include "io_interface.hpp"
#include "mpu9250_interface.hpp"
#include "navigation_engine.hpp"
#include "vector2f.hpp"
#include "wrap-hwlib.hpp"

int main() {
    WDT->WDT_MR = WDT_MR_WDDIS;
    auto scl = hwlib::target::pin_oc(hwlib::target::pins::scl);
    auto sda = hwlib::target::pin_oc(hwlib::target::pins::sda);
    const uint8_t address = 0x68;

    NavigationEngine engine;
    IOInterface interface(engine);
    MPU9250Interface sensor(scl, sda, address);
    sensor.calibrate();

    for (int i = 0; i < 20; i++) {
        hwlib::cout << "Accelerator: \n";
        sensor.printAccelerationGravity();

        hwlib::cout << "Gyroscope: \n";
        sensor.printGyroscopeDegreeSec();

        hwlib::cout << "\n";
        hwlib::wait_ms(1000);
    }
    return 0;
}
