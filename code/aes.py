import sys
from Crypto.Cipher import AES
from Crypto.Util.Padding import pad
from os import urandom
import hashlib

# Function to encrypt the payload using AES encryption
def AESencrypt(plaintext, key):
    k = hashlib.sha256(key).digest()  # Derive the AES key using SHA-256
    iv = 16 * b'\x00'  # Initialization vector (16 bytes, zeroed)
    plaintext = pad(plaintext, AES.block_size)  # Pad the plaintext
    cipher = AES.new(k, AES.MODE_CBC, iv)  # Create AES cipher in CBC mode
    ciphertext = cipher.encrypt(plaintext)  # Encrypt the padded plaintext
    return ciphertext, key

def main():
    # Check for input file
    if len(sys.argv) != 2:
        print("Usage: python AES_cryptor.py PAYLOAD_FILE")
        sys.exit(1)

    # Read payload content from the specified file
    payload_file = sys.argv[1]
    try:
        with open(payload_file, "rb") as file:
            content = file.read()
    except FileNotFoundError:
        print(f"Error: File {payload_file} not found!")
        sys.exit(1)

    # Generate a random 16-byte AES key (128-bit key)
    KEY = urandom(16)

    # Encrypt the payload using the generated AES key
    ciphertext, key = AESencrypt(content, KEY)

    # Save the AES key to a binary file (AESkey.bin)
    with open("AESkey.bin", "wb") as key_file:
        key_file.write(KEY)

    # Save the encrypted payload to a binary file (AEScode.bin)
    with open("AEScode.bin", "wb") as code_file:
        code_file.write(ciphertext)

    print("AES key and encrypted payload successfully saved as AESkey.bin and AEScode.bin.")

if __name__ == "__main__":
    main()
