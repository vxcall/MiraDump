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
        Scanner::FindPattern(config.signature, prc);
    }

}