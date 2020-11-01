#pragma once
#include "SigProfile.h"
#include <vector>
#include <string>
#include <optional>

class ConfigReader {
public:
    static std::vector<SigProfile> ReadProfile(const std::string& filename);
    static std::string ReadExportDir(const std::string& filename);
    static std::optional<std::string> ReadGameName(const std::string& filename);
};