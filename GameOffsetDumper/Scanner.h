#pragma once
#include <vector>
#include "Process.h"

class Scanner {
public:
    static void FindPattern(std::vector<int>& signature, Process& process);
};