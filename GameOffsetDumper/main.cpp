#include <iostream>
#include "ConfigReader.h"

int main() {
    std::vector<SignatureInfo> configs = ConfigReader::Read(std::string("test.toml"));
    for (SignatureInfo& config : configs) {
        std::cout << config.name << std::endl;
        std::cout << config.module << std::endl;
        std::cout << config.offset << std::endl;
        std::cout << config.extra << std::endl;
        for (auto& sig : config.signature) {
            std::cout << sig << " ";
        }
        std::cout << std::endl;
    }

}