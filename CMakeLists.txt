cmake_minimum_required(VERSION 4.1)
project(FIX)

find_package(quickfix REQUIRED)

add_executable(
    fix_engine
    src/main.cpp
)

target_link_libraries(
    fix_engine
    PRIVATE
        quickfix::quickfix
)