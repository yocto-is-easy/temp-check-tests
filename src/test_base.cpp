#include <chrono>
#include <functional>

#include <gtest/gtest.h>
#include <temp_check_interface.hpp>

// It is strongly recommended to use EXPECT to not fail all the test scope

size_t measure_ms(std::function<void()> f) {
    auto begin = std::chrono::steady_clock::now();
    f();
    auto end = std::chrono::steady_clock::now();

    return std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
}

TEST(TempCheckTest, ok_temperature_format)
{
    EXPECT_GE(temp_check::get_temperature(), -256.0);
    EXPECT_LE(temp_check::get_temperature(), 100.0);
}

TEST(TempCheckTest, get_temperature_time_1s)
{
    // remote call should take no more than 1s
    EXPECT_LE(measure_ms([](){ temp_check::get_temperature(); }), 1000);
}
