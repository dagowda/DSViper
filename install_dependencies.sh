#!/bin/bash

# Install Python dependencies
pip3 install -r requirements.txt

# Install mingw-w64 for compiling C/C++ code on Windows
sudo apt-get update
sudo apt-get install -y mingw-w64
