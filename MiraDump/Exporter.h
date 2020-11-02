#pragma once
#include <map>
#include <string>
#include <vector>
#include <tuple>

class Exporter {
    std::string filename;
    std::vector<std::tuple<std::string, uintptr_t, std::string>> resultInfo;
public:
    Exporter(std::string& filename, std::vector<std::tuple<std::string, uintptr_t, std::string>>& resultInfo);
    void WriteDown();
};