#pragma once
#include "SignatureInfo.h"
#include <vector>
#include <string>
#include <optional>

class ConfigReader {
public:
    static std::vector<SignatureInfo> ReadSigs(const std::string& filename);
    static std::string ReadExportDir(const std::string& filename);
    static std::optional<std::string> ReadGameName(const std::string& filename);
};