#pragma once
#include <Windows.h>
#include <TlHelp32.h>

namespace Process {
    HANDLE GetProcessHandle(DWORD processID);
    uintptr_t GetModuleBaseAddress(DWORD processID, const char* modName);
    DWORD GetProcId(const char* procName);
}
