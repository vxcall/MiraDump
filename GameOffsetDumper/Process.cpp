#include "Process.h"
#include <Windows.h>
#include <TlHelp32.h>
#include <iostream>

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

uintptr_t Process::GetModuleBaseAddress(DWORD processID, const char* moduleName)
{
    uintptr_t modBaseAddr = 0;
    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, processID);
    if (hSnap != INVALID_HANDLE_VALUE) {
        MODULEENTRY32 modEntry;
        modEntry.dwSize = sizeof(modEntry);
        if (Module32First(hSnap, &modEntry)) {
            do {
                if (!strcmp(modEntry.szModule, moduleName)) {
                    modBaseAddr = (uintptr_t)modEntry.modBaseAddr;
                    break;
                }
            } while (Module32Next(hSnap, &modEntry));
        }
    }
    CloseHandle(hSnap);
    return modBaseAddr;
}

HANDLE Process::GetProcessHandle(DWORD processID) {
    HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, NULL, processID);
    return hProcess;
}