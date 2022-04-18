cmake_minimum_required(VERSION 3.21)
project(Assign3)

set(CMAKE_CXX_STANDARD 14)

include_directories(Main)

add_executable(Assign3
        Main/bmplib.cpp
        Main/bmplib.h
        Main/Image-filters-20210430-20210413.cpp)
