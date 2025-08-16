#!/bin/bash

# Exit immediately if any command fails
set -e  

if [ -d "build/" ] 
then
    rm -r -v build/
else 
    echo No build directory found
fi    
