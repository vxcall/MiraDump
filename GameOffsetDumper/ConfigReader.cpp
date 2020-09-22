#include "ConfigReader.h"
#include "toml.hpp"
#include <optional>

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