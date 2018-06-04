#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"

#include "wrap-hwlib.hpp"

#include "some-controller.hpp"

TEST_CASE("Virtual hwlib uart") {
    hwlib::cout << "Hello world!" << hwlib::endl;
}

TEST_CASE("Virtual controller test demo") {
    hwlib::test::pin_in<14 * 8> test_pin_in{// some input data
                                            0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 1, 0, 1, 1, 0, 1, 1, 0, 0, 0, 1,
                                            1, 0, 1, 1, 0, 0, 0, 1, 1, 0, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1,
                                            0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 0, 0, 1, 0, 0, 1, 1, 0, 1, 1,
                                            0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0};

    SomeController controller;

    char buffer[256];

    controller.read_string_from_pin_in(test_pin_in, buffer);

    REQUIRE(strcmp(buffer, "Hello world!") == 0);
}

TEST_CASE("Virtualized hwlib::pin_in") {
    hwlib::test::pin_in<8> test_pin_in{1, 0, 1, 0, 1, 0, 1, 1};

    REQUIRE(test_pin_in.get() == 1);
    REQUIRE(test_pin_in.get() == 0);
    REQUIRE(test_pin_in.get() == 1);
    REQUIRE(test_pin_in.get() == 0);
    REQUIRE(test_pin_in.get() == 1);
    REQUIRE(test_pin_in.get() == 0);
    REQUIRE(test_pin_in.get() == 1);
    REQUIRE(test_pin_in.get() == 1);
}

TEST_CASE("Virtualized hwlib::pin_out") {
    hwlib::test::pin_out<8> test_pin_out{};

    test_pin_out.set(1);
    test_pin_out.set(0);
    test_pin_out.set(1);
    test_pin_out.set(1);
    test_pin_out.set(0);
    test_pin_out.set(0);
    test_pin_out.set(0);
    test_pin_out.set(1);

    uint8_t *data = test_pin_out.get_data();

    REQUIRE(data[0] == 1);
    REQUIRE(data[1] == 0);
    REQUIRE(data[2] == 1);
    REQUIRE(data[3] == 1);
    REQUIRE(data[4] == 0);
    REQUIRE(data[5] == 0);
    REQUIRE(data[6] == 0);
    REQUIRE(data[7] == 1);
}
