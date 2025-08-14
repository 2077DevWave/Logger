#!/bin/bash

# Exit immediately if a command exits with a non-zero status.
set -e

# Compile the C++ source files
echo "Compiling the logger test..."
g++ -std=c++11 -g tests/main_test.cpp Logger.cpp -o tests/test_runner

# Run the compiled test executable
echo "Running the test..."
./tests/test_runner

echo "Test finished. Verifying output..."

# Verify the output
# The expected output is stored in a separate file
expected_output_file="tests/expected_output.txt"
actual_output_file="test_app.log"

# Extract only the log messages from the actual output
# This will remove timestamps and log level prefixes
grep -oP '(?<=\] ).*' "$actual_output_file" > "tests/actual_messages.txt"

# Compare the actual messages with the expected messages
if diff -q "$expected_output_file" "tests/actual_messages.txt"; then
    echo "Test passed!"
    exit 0
else
    echo "Test failed! Output does not match expected output."
    diff "$expected_output_file" "tests/actual_messages.txt"
    exit 1
fi
