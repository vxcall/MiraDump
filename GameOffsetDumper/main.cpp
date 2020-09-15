#include <iostream>
#include "ConfigReader.h"
#include "Process.h"
#include <optional>

#define PROCESS_NAME "csgo.exe"

int main() {
    std::vector<SignatureInfo> configs = ConfigReader::Read(std::string("test.toml"));
    for (SignatureInfo& config : configs) {
        std::optional<MODULEENTRY32> modInfo = Process::GetModuleInfo(Process::GetProcId(PROCESS_NAME), config.module);
        if (modInfo) {
            std::cout << modInfo->modBaseSize << std::endl;
        } else {
            std::cerr << "No such module \"" << config.module << "\" in this game." << std::endl;
        }
    }
}