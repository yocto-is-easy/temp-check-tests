project(temp-check-tests)

cmake_minimum_required(VERSION 3.12)

add_executable(${CMAKE_PROJECT_NAME}
    src/test_base.cpp
)

find_package(Threads REQUIRED)

target_link_libraries(${CMAKE_PROJECT_NAME}
    gtest_main
    gtest
    Threads::Threads
)
