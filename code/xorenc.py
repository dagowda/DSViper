import sys
import random
from os import urandom

def xorEncrypt(plaintext, key):
    print("The XOR key is:", key)
    print("\n")
    
    ciphertext = bytearray()
    for i in range(len(plaintext)):
        # XOR each byte with the key in a repeating pattern
        ciphertext.append(plaintext[i] ^ key[i % len(key)])
    
    print("Ciphertext after XOR encryption:", ciphertext)
    return bytes(ciphertext)

def printResult(key, ciphertext):
    print('char XORkey[] = { 0x' + ', 0x'.join(hex(x)[2:] for x in key) + ' };')
    print('unsigned char XORshellcode[] = { 0x' + ', 0x'.join(hex(x)[2:] for x in ciphertext) + ' };')

try:
    # Open the payload file and read its contents
    with open(sys.argv[1], "rb") as file:
        content = file.read()
    print("Original content:", content)
except:
    print("Usage: .\\XOR_cryptor.py PAYLOAD_FILE")
    sys.exit()

# Generate 3 random numbers as the key
key = [random.randint(0, 255) for _ in range(16)]
ciphertext = xorEncrypt(content, key)

# Print the result in the desired format
printResult(key, ciphertext)
