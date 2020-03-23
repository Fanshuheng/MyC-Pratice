cmake_minimum_required(VERSION 3.13)
project(ch9)

set(CMAKE_CXX_STANDARD 14)

include_directories(
        ${PROJECT_SOURCE_DIR}/include
)

add_executable(ch9 cpp_practice_9_51.cpp)

