#!/bin/bash

set -e

sanitizers=("asan")

   echo "Building Debug with asan..."
   conan install . --build=missing --settings=build_type=Debug --options=sanitizer="asan"
   cmake --preset conan-debug
   cmake --build --preset conan-debug
   
ls -la build/Debug/
