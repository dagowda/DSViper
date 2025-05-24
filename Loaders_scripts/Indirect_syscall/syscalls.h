

#pragma once
#define OBJ_CASE_INSENSITIVE 0x00000040L
#ifndef _SYSCALLS_H
#define _SYSCALLS_H

#include <windows.h> 



typedef struct _PROCESS_BASIC_INFORMATION {
    ULONG Reserved;
    ULONG PebBaseAddress;
    ULONG AffinityMask;
    ULONG BasePriority;
    ULONG UniqueProcessId;
    ULONG InheritedFromUniqueProcessId;
} PROCESS_BASIC_INFORMATION;


#define RtlInitUnicodeString(UNICODE_STRING, STRING) { \
    (UNICODE_STRING)->Buffer = (STRING);              \
    (UNICODE_STRING)->Length = wcslen(STRING) * sizeof(WCHAR); \
    (UNICODE_STRING)->MaximumLength = (UNICODE_STRING)->Length + sizeof(WCHAR); \
}

typedef struct _CLIENT_ID
{
    HANDLE UniqueProcess;
    HANDLE UniqueThread;
} CLIENT_ID, * PCLIENT_ID;

typedef enum _PROCESSINFOCLASS
{
    ProcessBasicInformation = 0,
    ProcessDebugPort = 7,
    ProcessWow64Information = 26,
    ProcessImageFileName = 27,
    ProcessBreakOnTermination = 29
} PROCESSINFOCLASS, * PPROCESSINFOCLASS;



typedef struct _UNICODE_STRING
{
    USHORT Length;
    USHORT MaximumLength;
    PWSTR  Buffer;
} UNICODE_STRING, * PUNICODE_STRING;

#ifndef InitializeObjectAttributes
#define InitializeObjectAttributes( p, n, a, r, s ) { \
	(p)->Length = sizeof( OBJECT_ATTRIBUTES );        \
	(p)->RootDirectory = r;                           \
	(p)->Attributes = a;                              \
	(p)->ObjectName = n;                              \
	(p)->SecurityDescriptor = s;                      \
	(p)->SecurityQualityOfService = NULL;             \
}
#endif
typedef struct _OBJECT_ATTRIBUTES
{
    ULONG           Length;
    HANDLE          RootDirectory;
    PUNICODE_STRING ObjectName;
    ULONG           Attributes;
    PVOID           SecurityDescriptor;
    PVOID           SecurityQualityOfService;
} OBJECT_ATTRIBUTES, * POBJECT_ATTRIBUTES;


#ifdef __cplusplus
extern "C" {
#endif

    typedef long NTSTATUS;  // Define NTSTATUS as a long
    typedef NTSTATUS* PNTSTATUS;  // Define a pointer to NTSTATUS

    extern NTSTATUS NtCreateProcess(
        OUT PHANDLE ProcessHandle,
        IN ACCESS_MASK DesiredAccess,
        IN POBJECT_ATTRIBUTES ObjectAttributes OPTIONAL,
        IN HANDLE ParentProcess,
        IN BOOLEAN InheritObjectTable,
        IN HANDLE SectionHandle OPTIONAL,
        IN HANDLE DebugPort OPTIONAL,
        IN HANDLE ExceptionPort OPTIONAL);

    // Declare the syscalls
    extern NTSTATUS NtAllocateVirtualMemory(
        HANDLE ProcessHandle,
        PVOID* BaseAddress,
        ULONG_PTR ZeroBits,
        PSIZE_T RegionSize,
        ULONG AllocationType,
        ULONG Protect
    );

    extern NTSTATUS NtWriteVirtualMemory(
        HANDLE ProcessHandle,
        PVOID BaseAddress,
        PVOID Buffer,
        SIZE_T NumberOfBytesToWrite,
        PULONG NumberOfBytesWritten
    );


    extern NTSTATUS NtSuspendThread(
        HANDLE ThreadHandle
    );

    extern NTSTATUS NtResumeThread(
        HANDLE ThreadHandle,
        PULONG PreviousSuspendCount
    );


    extern NTSTATUS NtQueryInformationProcess(
        IN HANDLE ProcessHandle,
        IN PROCESSINFOCLASS ProcessInformationClass,
        OUT PVOID ProcessInformation,
        IN ULONG ProcessInformationLength,
        OUT PULONG ReturnLength OPTIONAL);


    extern NTSTATUS NtQueueApcThread(
        HANDLE ThreadHandle,
        PVOID ApcRoutine,
        PVOID ApcRoutineContext,
        PVOID ApcStatusBlock,
        PVOID ApcReserved
    );

    extern NTSTATUS NtProtectVirtualMemory(
        HANDLE ProcessHandle,
        PVOID* BaseAddress,
        PSIZE_T RegionSize,
        ULONG NewProtect,
        PULONG OldProtect
    );

    //extern NTSTATUS NtWaitForSingleObject(
       // HANDLE Handle,
        //BOOLEAN Alertable,
        //PLARGE_INTEGER Timeout
    //);

#ifdef __cplusplus
}
#endif

#endif
