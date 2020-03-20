cmake_minimum_required(VERSION 3.13)
project(ch7)

set(CMAKE_CXX_STANDARD 14)


include_directories(
        ${PROJECT_SOURCE_DIR}/include
)
add_executable(ch7 practice_7_11.cpp)