#include "Process.h"
#include <Windows.h>
#include <TlHelp32.h>
#include <optional>
#include <string>

DWORD Process::GetProcId(const char* procName)
{
    DWORD procId = 0;
    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnap != INVALID_HANDLE_VALUE) {
        PROCESSENTRY32 procEntry;
        procEntry.dwSize = sizeof(procEntry);
        if (Process32First(hSnap, &procEntry) == 1) {
            do {
                if (strcmp(procEntry.szExeFile, procName) == 0) {

                    procId = procEntry.th32ProcessID;
                    break;
                }
            } while (Process32Next(hSnap, &procEntry) == 1);
        }
    }
    CloseHandle(hSnap);
    return procId;
}

std::optional<MODULEENTRY32> Process::GetModuleInfo(DWORD processID, const std::string& moduleName)
{
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, processID);
    if (hSnapshot == INVALID_HANDLE_VALUE) {
        return std::optional<MODULEENTRY32>{};
    }
    MODULEENTRY32 moduleEntry;
    moduleEntry.dwSize = sizeof(MODULEENTRY32);
    if (Module32First(hSnapshot, &moduleEntry)) {
        while (true) {
            BOOL ok = Module32Next(hSnapshot, &moduleEntry);
            if (ok == ERROR_NO_MORE_FILES)
                break;
            if (moduleEntry.szModule == moduleName) {
                CloseHandle(hSnapshot);
                return std::optional<MODULEENTRY32>(moduleEntry);
            }
        }
    }
    CloseHandle(hSnapshot);
    return std::optional<MODULEENTRY32>{};
}