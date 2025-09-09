#!/bin/bash
set -e
rm -r build

# Release build
echo "Building Release..."
conan install . --build=missing
cmake --preset conan-release
cmake --build --preset conan-release
