cmake_minimum_required(VERSION 4.1)
project(FIXApplication)

find_package(quickfix REQUIRED)

add_subdirectory(engine)
add_subdirectory(client_simulator)