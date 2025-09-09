#!/bin/bash
set -e  # Exit immediately if any command fails

ceedling clean
ceedling test:all