#include "wrap-hwlib.hpp"

int main() {
    WDT->WDT_MR = WDT_MR_WDDIS;

    hwlib::wait_ms(1000);
    hwlib::cout << "Hello world!" << hwlib::endl;
    int i = 0;
    while (true) {
        i++;
        hwlib::cout << i << "<>";
    }
    return 0;
}
