cmake_minimum_required(VERSION 3.13)
project(ch12)

set(CMAKE_CXX_STANDARD 14)

include_directories(
        ${PROJECT_SOURCE_DIR}/include
)

add_executable(ch12 cpp_practice_12.cpp cpp_practice_12.cpp StrBlob.cpp StrBlob.h StrBlobPtr.cpp StrBlobPtr.h)

