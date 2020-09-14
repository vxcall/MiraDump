#include "ConfigReader.h"
#include "toml.hpp"

std::vector<SignatureInfo> ConfigReader::Read(const std::string& filename) {
    auto config = toml::parse(filename);
    std::vector<SignatureInfo> result = {};
    for (auto& target : config.at("targets").as_array()) {
        SignatureInfo si;
        si.name = target.at("name").as_string();
        si.signature = target.at("signature").as_string();
        si.module = target.at("module").as_string();
        si.offset = target.at("offset").as_integer();
        si.extra = target.at("extra").as_integer();

        result.push_back(si);
    }
    return result;
}