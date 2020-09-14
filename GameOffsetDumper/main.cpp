#include <iostream>
#include "ConfigReader.h"

int main() {
    std::vector configs = ConfigReader::Read(std::string("test.toml"));
    for (SignatureInfo& config : configs) {
        std::cout << config.module << std::endl;
        std::cout << config.signature << std::endl;
        std::cout << config.offset << std::endl;
        std::cout << config.extra << std::endl;
        std::cout << config.name << std::endl;
    }
}