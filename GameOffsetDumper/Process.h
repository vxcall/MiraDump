#pragma once
#include <Windows.h>
#include <TlHelp32.h>
#include <optional>
#include <string>

class Process {
    std::string processName;
    DWORD processID;
    std::string moduleName;
    Process(std::string& processName, const std::string& moduleName);
    void GetProcID();
    void GetModuleInfo(const std::string& moduleName);
    void GetProcessHandle(DWORD& processID);
public:
    HANDLE hProcess;
    BYTE* moduleBaseAddress;
    DWORD moduleBaseSize;
    static Process GetProcess(const std::string& processName, const std::string& moduleName);
    std::optional<std::string> GetError();
};