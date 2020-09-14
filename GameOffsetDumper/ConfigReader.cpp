#include "ConfigReader.h"
#include "toml.hpp"

std::vector<SignatureInfo> ConfigReader::Read(const std::string& filename) {
    auto config = toml::parse(filename);
    std::vector<SignatureInfo> result = {};
    for (auto& target : config.at("targets").as_array()) {
        SignatureInfo si(target.at("name").as_string(), target.at("signature").as_string(), target.at("module").as_string(), target.at("offset").as_integer(), target.at("extra").as_integer());
        result.push_back(si);
    }
    return result;
}