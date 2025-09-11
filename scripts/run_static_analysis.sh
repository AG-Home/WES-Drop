#! /bin/bash

# Exit immediately if any command fails
set -e  

# Define the log file location
LOGFILE="build/cppcheck.log"
BUILD_DIR=build

# Redirect all output (stdout and stderr) to both terminal and log file
exec > >(tee "$LOGFILE") 2>&1

if [ ! -f "$BUILD_DIR/compile_commands.json" ]; then
  echo "Error: compile_commands.json not found in $BUILD_DIR"
  exit 1
fi

cppcheck \
  --project=$BUILD_DIR/compile_commands.json \
  --enable=all \
  --suppress=missingIncludeSystem \
  --force \
  --quiet \

