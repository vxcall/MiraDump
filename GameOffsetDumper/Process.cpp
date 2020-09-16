#include "Process.h"
#include <Windows.h>
#include <TlHelp32.h>
#include <optional>
#include <string>

std::optional<DWORD> Process::GetProcID(const char* procName)
{
    std::optional<DWORD> processID {};
    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnap != INVALID_HANDLE_VALUE) {
        PROCESSENTRY32 procEntry;
        procEntry.dwSize = sizeof(procEntry);
        if (Process32First(hSnap, &procEntry) == 1) {
            do {
                if (strcmp(procEntry.szExeFile, procName) == 0) {

                    processID = procEntry.th32ProcessID;
                    break;
                }
            } while (Process32Next(hSnap, &procEntry) == 1);
        }
    }
    CloseHandle(hSnap);
    return processID;
}

std::optional<std::pair<BYTE*, DWORD>> Process::GetModuleInfo(DWORD processID, const std::string& moduleName)
{
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, processID);
    if (hSnapshot == INVALID_HANDLE_VALUE) {
        return std::optional<std::pair<BYTE*, DWORD>> {};
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
                return std::make_pair(moduleEntry.modBaseAddr, moduleEntry.modBaseSize);
            }
        }
    }
    CloseHandle(hSnapshot);
    return std::optional<std::pair<BYTE*, DWORD>> {};
}