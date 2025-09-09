#!/bin/bash

set -e

# Release build
echo "Building Release..."
conan install . --build=missing
cmake --preset conan-release
cmake --build --preset conan-release
