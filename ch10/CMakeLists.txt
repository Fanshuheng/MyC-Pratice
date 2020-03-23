cmake_minimum_required(VERSION 3.13)
project(ch10)

set(CMAKE_CXX_STANDARD 14)

include_directories(
        ${PROJECT_SOURCE_DIR}/include
)

add_executable(ch10 cpp_practice_10_1.cpp)

