#!/bin/bash
#
# This script installs the dependencies, builds the project and runs the tests.

set -e -u

mkdir -p build

cd build

conan install .. --build=missing
cmake .. -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
cmake --build .
ctest -V

