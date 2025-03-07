#!/bin/bash

# Install Python dependencies
pip3 install -r requirements.txt

# Install mingw-w64 for compiling C/C++ code on Windows
chmod +x DSViper
sudo apt-get update
sudo apt-get install -y mingw-w64
sudo apt install mono-complete
chmod +x MASM-compatible/uasm
sudo cp MASM-compatible/uasm /usr/bin/uasm
