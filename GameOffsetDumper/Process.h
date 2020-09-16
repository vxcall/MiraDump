#pragma once
#include <Windows.h>
#include <TlHelp32.h>
#include <optional>
#include <string>

class Process {
public:
    static std::optional<DWORD> GetProcID(const char* procName);
    static std::optional<std::pair<BYTE*, DWORD>> GetModuleInfo(DWORD processID, const std::string& moduleName);
};