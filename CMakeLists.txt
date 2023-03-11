cmake_minimum_required(VERSION 3.22)
project(buaa_ase_WordList)

set(CMAKE_CXX_STANDARD 14)

add_library(buaa_ase_WordList SHARED src/core.cpp src/core.h)

add_subdirectory(lib)
include_directories(lib/googletest/include lib/googletest)
include_directories(lib/googlemock/include lib/googlemock)
include_directories(src)

set(LIBRARIES
        gtest
        pthread)

link_directories(./cmake-build-debug)
add_executable(src src/core.cpp test/gtest.cpp src/core.h)

target_link_libraries(src ${LIBRARIES})