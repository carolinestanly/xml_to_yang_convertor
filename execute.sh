#!/bin/bash

# Define macro for input file path
INPUT_FILE="assets/samples/input.xml"

# Define macro for output file path and create output directory if it doesn't exist
OUTPUT_DIR="assets/output"
mkdir -p $OUTPUT_DIR
OUTPUT_FILE="$OUTPUT_DIR/output.yang"

# Execute the command with the input and output file arguments
./bin/main $INPUT_FILE $OUTPUT_FILE