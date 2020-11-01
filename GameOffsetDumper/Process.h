#pragma once
#include <Windows.h>
#include <TlHelp32.h>
#include <optional>
#include <string>

class Process {
    std::string processName;
    DWORD processID;
    Process(std::string& processName, const std::string& moduleName);
    void GetProcID();
    void GetModuleInfo(const std::string& moduleName);
    void GetProcessHandle(DWORD& processID);
public:
    std::string moduleName;
    HANDLE hProcess;
    BYTE* moduleBaseAddress;
    DWORD moduleBaseSize;
    static Process GetProcess(std::string& processName, const std::string& moduleName);
    std::optional<std::string> GetError();
};