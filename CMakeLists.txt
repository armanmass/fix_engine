cmake_minimum_required(VERSION 4.1)
project(FIXApplication)

find_package(quickfix REQUIRED)

add_subdirectory(common)
add_subdirectory(fix_engine)

add_subdirectory(client_simulator)