cmake_minimum_required(VERSION 3.22)
project(core)

set(CMAKE_CXX_STANDARD 14)

# create .dll

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
set(CMAKE_EXE_LINKER_FLAGS "-static")
add_library(core SHARED src/core.cpp src/core.h)


# run main and create .exe

link_directories(bin)
link_directories(./cmake-build-debug)
add_executable(src src/main.cpp)
target_link_libraries(src core.dll)


# test

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
#add_executable(src test/gtest.cpp src/core.h src/core.cpp src/main.h src/main.cpp)
#target_link_libraries(src ${LIBRARIES})

