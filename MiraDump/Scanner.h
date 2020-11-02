#pragma once
#include <vector>
#include "Process.h"
#include "SigProfile.h"

class Scanner {
    static std::optional<uintptr_t> FindPattern(std::vector<int>& signature, Process& process, std::vector<std::byte> moduleByte);
public:
    static std::optional<uintptr_t> Scan(Process& process, SigProfile& sigInfo, std::vector<std::byte> moduleByte);
};