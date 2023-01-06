#include <chrono>
#include <functional>
#include <iostream>

#include <gtest/gtest.h>
#include <temp_check_interface.hpp>

// It is strongly recommended to use EXPECT to not fail all the test scope

size_t measure_ms(std::function<void()> f) {
    auto begin = std::chrono::steady_clock::now();
    f();
    auto end = std::chrono::steady_clock::now();

    return std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
}

size_t measure_ns(std::function<void()> f) {
    auto begin = std::chrono::steady_clock::now();
    f();
    auto end = std::chrono::steady_clock::now();

    return std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();
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

TEST(TestServiceTest, ping_ns_100_avg)
{
    size_t sum = 0;
    for(int i = 0; i < 100; i++) {
        size_t delta = measure_ns([](){ test_service::ping(); });
        std::cout << "ping (" << i << "): " << (float)delta/1000000.0f << "ms" << std::endl;
        sum += delta;
    }
    float avg_ping = (float)sum / 100.0;
    std::cout << "avg ping: " << (float)avg_ping/1000000.0f << "ms" << std::endl;
}

TEST(TestServiceTest, get_1mb_10_avg)
{
    size_t sum = 0;
    for(int i = 0; i < 10; i++) {
        size_t delta = measure_ns([](){ test_service::get_1mb(); });
        std::cout << "get_1mb (" << i << "): " << (float)delta/1000000.0f << "ms" << std::endl;
        sum += delta;
    }
    float avg_ping = (float)sum / 10.0;
    std::cout << "avg get_1mb: " << (float)avg_ping/1000000.0f << "ms" << std::endl;
}
