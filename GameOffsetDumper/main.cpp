#include <iostream>
#include <optional>
#include "ConfigReader.h"
#include "Process.h"
#include "Scanner.h"

int main()
{
    std::optional<std::string> gameName = ConfigReader::ReadGameName("config.toml");
    if (!gameName) {
        std::cerr << "Specify the name of the target game" << std::endl;
        return 1;
    }
    
    std::vector<SignatureInfo> configs = ConfigReader::ReadSigs("config.toml");
    for (SignatureInfo& config : configs)
    {
        Process prc = Process::GetProcess(*gameName, config.module);
        std::cerr << *prc.GetError();
        auto result = Scanner::Scan(config.signature, prc, config);
        if (!result) {
            std::cerr << "Couldn't find signature. Check if you filled config.toml properly" << std::endl;
            return 1;
        }
        std::cout << config.module << " + 0x" << std::hex << *result << std::endl;
    }
}