#include "ConfigReader.h"
#include "toml.hpp"

std::vector<SignatureInfo> ConfigReader::Read(const std::string& filename) {
    auto config = toml::parse(filename);
    auto targets = toml::find<std::vector<toml::table>>(config, "targets");
    std::vector<SignatureInfo> result = {};
    for (toml::table& target : targets) {
        SignatureInfo si;
        si.module = target["module"].as_string();
        si.signature = target["signature"].as_string();
        si.offset = target["offset"].as_integer();
        si.extra = target["extra"].as_integer();
        si.name = target["name"].as_string();
        result.push_back(si);
    }
    return result;
}