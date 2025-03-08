#!/bin/bash

# Install Python dependencies
pip3 install -r requirements.txt

# Install mingw-w64 for compiling C/C++ code on Windows
chmod +x DSViper
sudo apt-get update
sudo apt-get install -y mingw-w64
sudo apt install mono-complete
mkdir masm
wget -O masm/uasm_linux64.zip https://www.terraspace.co.uk/uasm257_linux64.zip
unzip masm/uasm_linux64.zip -d masm
chmod +x masm/uasm*
sudo cp masm/uasm /usr/bin/uasm

