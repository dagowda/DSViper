



EXTERN wNtAllocateVirtualMemory:DWORD               ; Extern keyword indicates that the symbol is defined in another module. Here it's the syscall number for NtAllocateVirtualMemory.
EXTERN sysAddrNtAllocateVirtualMemory:QWORD         ; The actual address of the NtAllocateVirtualMemory syscall in ntdll.dll.

EXTERN wNtWriteVirtualMemory:DWORD                  ; Syscall number for NtWriteVirtualMemory.
EXTERN sysAddrNtWriteVirtualMemory:QWORD            ; The actual address of the NtWriteVirtualMemory syscall in ntdll.dll.

EXTERN wNtCreateThreadEx:DWORD                      ; Syscall number for NtCreateThreadEx.
EXTERN sysAddrNtCreateThreadEx:QWORD                ; The actual address of the NtCreateThreadEx syscall in ntdll.dll.

              
EXTERN wNtResumeThread:DWORD                        ; Syscall number for NtResumeThread.
EXTERN sysAddrNtResumeThread:QWORD                  ; The actual address of the NtResumeThread syscall in ntdll.dll.


EXTERN wNtProtectVirtualMemory:DWORD                    ; Syscall number for NtSetContextThread.
EXTERN sysAddrNtProtectVirtualMemory:QWORD              ; The actual address of the NtSetContextThread syscall in ntdll.dll.

EXTERN wNtQueueApcThread:DWORD                    ; Syscall number for NtSetContextThread.
EXTERN sysAddrNtQueueApcThread:QWORD              ; The actual address of the NtSetContextThread syscall in ntdll.dll.

.CODE  ; Start the code section

; Procedure for the NtAllocateVirtualMemory syscall
NtAllocateVirtualMemory PROC
    mov r10, rcx                                    ; Move the contents of rcx to r10.
    mov eax, wNtAllocateVirtualMemory               ; Move the syscall number into the eax register.
    jmp QWORD PTR [sysAddrNtAllocateVirtualMemory]  ; Jump to the actual syscall.
NtAllocateVirtualMemory ENDP                        ; End of the procedure.

; Procedure for the NtWriteVirtualMemory syscall
NtWriteVirtualMemory PROC
    mov r10, rcx                                    ; Move the contents of rcx to r10.
    mov eax, 03ah                  ; Move the syscall number into the eax register.
    jmp QWORD PTR [sysAddrNtWriteVirtualMemory]     ; Jump to the actual syscall.
NtWriteVirtualMemory ENDP

; Procedure for the NtCreateThreadEx syscall

; Procedure for the NtResumeThread syscall
NtResumeThread PROC
    mov r10, rcx                                    ; Move the contents of rcx to r10.
    mov eax, 052h                        ; Move the syscall number into the eax register.
    jmp QWORD PTR [sysAddrNtResumeThread]           ; Jump to the actual syscall.
NtResumeThread ENDP

; Procedure for the NtSetContextThread syscall

NtProtectVirtualMemory PROC
    mov r10, rcx                                    ; Move the contents of rcx to r10.
    mov eax, 050h                                 ; Move the syscall number into the eax register.
    jmp QWORD PTR [sysAddrNtProtectVirtualMemory]       ; Jump to the actual syscall.
NtProtectVirtualMemory ENDP

NtQueueApcThread PROC
    mov r10, rcx                                    ; Move the contents of rcx to r10.
    mov eax, 045h                    ; Move the syscall number into the eax register.
    jmp QWORD PTR [sysAddrNtQueueApcThread]       ; Jump to the actual syscall.
NtQueueApcThread ENDP

END  
