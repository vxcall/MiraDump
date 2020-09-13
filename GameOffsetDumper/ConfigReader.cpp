#include "ConfigReader.h"
#include "toml.hpp"
#include <iostream>

void ConfigReader::Read(const std::string& filename) {
    auto config = toml::parse(filename);
    auto targets = toml::find<std::vector<toml::table>>(config, "targets");
    for (toml::table& target : targets) {
        auto name = target["name"];
        auto signature = target["signature"];
        std::cout << name << "  " << signature << std::endl;
    }
}