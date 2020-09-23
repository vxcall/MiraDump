#include "ConfigReader.h"
#include "toml.hpp"
#include <optional>
#include <filesystem>

std::vector<SignatureInfo> ConfigReader::ReadSigs(const std::string& filename)
{
    auto config = toml::parse(filename);
    std::vector<SignatureInfo> result = {};
    for (auto& target : config.at("targets").as_array()) {
        SignatureInfo si(target.at("name").as_string(), target.at("signature").as_string(), target.at("module").as_string(), target.at("offset").as_integer(), target.at("extra").as_integer());
        result.push_back(si);
    }
    return result;
}

std::string ConfigReader::ReadExportDir(const std::string &filename) {
    auto config = toml::parse(filename);
    static auto dir = toml::find_or(config, "export_dir", "");
    if (dir.c_str()[dir.size()-1] != '/' && dir.c_str()[dir.size()-1] != '\\') {
        dir += "/";
    }
    if (!std::filesystem::exists(dir)) {
        dir = "";
    }
    return dir;
}

std::optional<std::string> ConfigReader::ReadGameName(const std::string &filename)
{
    std::ifstream ifs(filename);
    if (!ifs.is_open()) {
        return std::optional<std::string> {};
    }
    auto config = toml::parse(filename);
    auto result = toml::find_or(config, "game", "");
    if (!result.empty()) {
        return result;
    } else {
        return std::optional<std::string> {};
    }
}