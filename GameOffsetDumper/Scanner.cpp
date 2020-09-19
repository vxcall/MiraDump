#include "Scanner.h"
#include <vector>
#include <iostream>
#include <optional>

std::optional<uintptr_t> Scanner::FindPattern(std::vector<int>& signature, Process& process)
{
    std::vector<std::byte> buffer(process.moduleBaseSize);
    ReadProcessMemory(process.hProcess, static_cast<LPCVOID>(process.moduleBaseAddress), buffer.data(), buffer.size(), NULL);
    int iStore = 0;
    for (int i = 0;i < buffer.size();++i) {
        for (int j = 0;j < signature.size();++j) {
            iStore = i;
            if (signature.at(j) == -1 || static_cast<std::byte>(signature.at(j)) == buffer.at(i)) {
                if (j + 1 == signature.size()) {
                    int position = i - static_cast<int>(signature.size()) + 2;
                    return position;
                }
                i++;
            } else {
                i = iStore;
                break;
            }
        }
    }
    return std::optional<uintptr_t>{};
}

std::optional<uintptr_t> Scanner::Scan(std::vector<int> &signature, Process &process) {
    std::optional<uintptr_t> result = Scanner::FindPattern(signature, process);
    if (!result)
        return std::optional<uintptr_t> {};
    uintptr_t buffer;
    ReadProcessMemory(process.hProcess, static_cast<LPCVOID>(process.moduleBaseAddress + *result), &buffer, sizeof(buffer), NULL);
    return buffer - (uintptr_t)process.moduleBaseAddress;
}