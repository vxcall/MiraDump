#include <iostream>
#include <optional>
#include <tuple>
#include "ConfigReader.h"
#include "Process.h"
#include "Scanner.h"
#include "Exporter.h"

int main()
{
    std::optional<std::string> gameName = ConfigReader::ReadGameName("config.toml");
    if (!gameName) {
        std::cerr << "Specify the name of the target game" << std::endl;
        return 1;
    }
    
    std::vector<SignatureInfo> configs = ConfigReader::ReadSigs("config.toml");
    std::vector<std::tuple<std::string, uintptr_t, std::string>> offsetInfo {};
    for (SignatureInfo& config : configs)
    {
        Process prc = Process::GetProcess(*gameName, config.module);
        std::cerr << *prc.GetError();
        auto result = Scanner::Scan(config.signature, prc, config);
        if (!result) {
            std::cerr << "Couldn't find signature. Check if you filled config.toml properly." << std::endl;
            return 1;
        }
        std::cout << "<" << config.module << ">" << " + 0x" << std::hex << *result << std::endl;
        offsetInfo.emplace_back(std::make_tuple(config.name, *result, config.module));
    }
    Exporter exp("GameOffsets.hpp", offsetInfo);
    exp.WriteDown();
}