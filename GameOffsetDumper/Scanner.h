#pragma once
#include <vector>
#include "Process.h"

class Scanner {
    static std::optional<uintptr_t> FindPattern(std::vector<int>& signature, Process& process);
public:
    static std::optional<uintptr_t> Scan(std::vector<int>& signature, Process& process);
};