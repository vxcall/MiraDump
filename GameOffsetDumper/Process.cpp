#include "Process.h"
#include <Windows.h>
#include <TlHelp32.h>
#include <string>

Process::Process(const std::string& processName, const std::string& moduleName)
{
    this->processID = 0;
    this->moduleBaseAddress = nullptr;
    this->moduleBaseSize = 0;
    this->GetProcID(processName);
    this->GetModuleInfo(moduleName);
}

Process Process::GetProcess(const std::string &processName, const std::string &moduleName)
{
    return Process(processName, moduleName);
}

void Process::GetProcID(const std::string& processName)
{
    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnap != INVALID_HANDLE_VALUE) {
        PROCESSENTRY32 procEntry;
        procEntry.dwSize = sizeof(procEntry);
        if (Process32First(hSnap, &procEntry) == 1) {
            do {
                if (procEntry.szExeFile == processName) {
                    this->processID = procEntry.th32ProcessID;
                    break;
                }
            } while (Process32Next(hSnap, &procEntry) == 1);
        }
    }
    CloseHandle(hSnap);
}

void Process::GetModuleInfo(const std::string& moduleName)
{
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, this->processID);
    if (hSnapshot == INVALID_HANDLE_VALUE) {
        return;
    }
    MODULEENTRY32 moduleEntry;
    moduleEntry.dwSize = sizeof(moduleEntry);
    if (Module32First(hSnapshot, &moduleEntry)) {
        while (true) {
            BOOL ok = Module32Next(hSnapshot, &moduleEntry);
            if (ok == FALSE)
                break;
            if (moduleEntry.szModule == moduleName) {
                CloseHandle(hSnapshot);
                this->moduleBaseAddress = moduleEntry.modBaseAddr;
                this->moduleBaseSize = moduleEntry.modBaseSize;
            }
        }
    }
    CloseHandle(hSnapshot);
}
