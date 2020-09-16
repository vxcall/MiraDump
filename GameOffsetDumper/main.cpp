#include <iostream>
#include "ConfigReader.h"
#include "Process.h"

#define PROCESS_NAME "csgo.exe"

int main() {
    std::vector<SignatureInfo> configs = ConfigReader::Read(std::string("test.toml"));
    for (SignatureInfo& config : configs) {
        std::optional<DWORD> processID = Process::GetProcID(PROCESS_NAME);
        if (!processID) {
            std::cerr << "No such process \"" << PROCESS_NAME << "\"" << std::endl;
            return 0;
        }
        auto result = Process::GetModuleInfo(*processID, config.module);
        if (result) {
            std::cout << (uintptr_t)result->first << std::endl;
            std::cout << result->second << std::endl;
        } else {
            std::cerr << "No such module \"" << config.module << "\" in this game." << std::endl;
        }
    }
}