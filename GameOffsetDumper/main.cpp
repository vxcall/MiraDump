#include <iostream>
#include "ConfigReader.h"

int main() {
    std::vector<SignatureInfo> configs = ConfigReader::Read(std::string("test.toml"));
    for (SignatureInfo& config : configs) {
        for (auto& sig : config.signature) {
            std::cout << std::hex << sig << " ";
        }
        std::cout << std::endl;
    }

}