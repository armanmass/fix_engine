cmake_minimum_required(VERSION 4.1)
project(FIXApplication)

find_package(quickfix REQUIRED)

add_subdirectory(include)
add_subdirectory(src)
add_subdirectory(simulator)