#!/bin/bash

# This script compiles and runs the logger test.

# Exit immediately if a command exits with a non-zero status.
set -e

# Compile the C++ source files
echo "Compiling the logger..."
g++ -std=c++11 -g test.cpp Logger.cpp -o test -pthread

# Run the compiled test executable
echo "Running the test..."
./test

echo "Test finished. Check app.log for file logging output."
