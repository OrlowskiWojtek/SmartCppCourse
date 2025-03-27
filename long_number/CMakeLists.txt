cmake_minimum_required(VERSION 3.10)
project(long_number VERSION 1.0)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)


add_executable(long_number main.cpp long_number.hpp long_number.cpp)

target_include_directories(long_number PUBLIC "${PROJECT_BINARY_DIR}")

