#pragma once
#include <map>
#include <string>
#include <vector>
#include <tuple>

class Exporter {
    std::string filename;
    std::vector<std::tuple<std::string, uintptr_t, std::string>> offsetInfo;
public:
    Exporter(std::string& filename, std::vector<std::tuple<std::string, uintptr_t, std::string>>& offsetInfo);
    void WriteDown();
};