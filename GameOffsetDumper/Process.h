#pragma once
#include <Windows.h>
#include <TlHelp32.h>
#include <optional>
#include <string>

class Process {
    DWORD processID;
    BYTE* moduleBaseAddress;
    DWORD moduleBaseSize;
    Process(const std::string& processName, const std::string& moduleName);
    void GetProcID(const std::string& processName);
    void GetModuleInfo(const std::string& moduleName);
public:
    static Process GetProcess(const std::string& processName, const std::string& moduleName);

};