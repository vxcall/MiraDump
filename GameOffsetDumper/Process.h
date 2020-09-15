#pragma once
#include <Windows.h>
#include <TlHelp32.h>
#include <optional>
#include <string>

class Process {
public:
    HANDLE GetProcessHandle(DWORD processID);
    static DWORD GetProcId(const char* procName);
    static std::optional<MODULEENTRY32> GetModuleInfo(DWORD processID, const std::string& moduleName);
};