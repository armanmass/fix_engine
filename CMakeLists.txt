cmake_minimum_required(VERSION 3.30) 
project(FIXApplication)

list(
    APPEND CMAKE_PREFIX_PATH 
    "$ENV{HOME}/.local"
    "/usr/local"
)

find_package(quickfix REQUIRED)
find_package(gRPC REQUIRED)
find_package(protobuf REQUIRED)


add_subdirectory(common)
add_subdirectory(fix_engine)
add_subdirectory(client_simulator)
add_subdirectory(matching_engine)