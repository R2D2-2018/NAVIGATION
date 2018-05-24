#ifndef SOME_CONTROLLER_HPP
#define SOME_CONTROLLER_HPP

#include "wrap-hwlib.hpp"

class SomeController {
  public:
    void read_string_from_pin_in(hwlib::pin_in &in, char *buffer) {
        while (true) {
            char c = 0;

            for (int i = 0; i < 8; i++) {
                c <<= 1;
                c |= in.get();
            }

            *buffer = c;

            if (c == 0) {
                break;
            }

            buffer++;
        }
    }
};

#endif // SOME_CONTROLLER_HPP
