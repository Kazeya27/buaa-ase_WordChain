cmake_minimum_required(VERSION 3.22)
project(buaa_ase_WordList)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
add_library(buaa_ase_WordList SHARED src/core.cpp src/core.h)

link_directories(bin)
#link_directories(./cmake-build-debug)
add_executable(src src/main.cpp)
target_link_libraries(src core.dll)

# test
#
#add_subdirectory(lib)
#include_directories(lib/googletest/include lib/googletest)
#include_directories(lib/googlemock/include lib/googlemock)
#include_directories(src)
#
#set(LIBRARIES
#        gtest
#        pthread)
#
#
#add_executable(src test/gtest.cpp src/core.h src/main.h src/main.cpp src/core.cpp)
#target_link_libraries(src ${LIBRARIES})

