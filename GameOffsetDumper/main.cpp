#include <iostream>
#include <optional>
#include <tuple>
#include <string>
#include "ConfigReader.h"
#include "Process.h"
#include "Scanner.h"
#include "Exporter.h"

void Terminate() {
    std::cout << "\n\nPress any key to finish..." << std::endl;
    std::cin.get();
    fclose(stdout);
    fclose(stderr);
    fclose(stdin);
    FreeConsole();
}
int main()
{
    AllocConsole();
    FILE* fp = NULL;
    freopen_s(&fp, "CONOUT$", "w", stdout);
    freopen_s(&fp, "CONOUT$", "w", stderr);
    freopen_s(&fp, "CONIN$", "r", stdin);
    std::string configFileName = "config.toml";
    std::optional<std::string> gameName = ConfigReader::ReadGameName(configFileName);
    if (!gameName) {
        std::cerr << "Something went wrong. Make sure if you have config.toml and specified the name of a game" << std::endl;
        Terminate();
        return 1;
    }
    std::string dir = ConfigReader::ReadExportDir(configFileName);
    
    std::vector<SignatureInfo> configs = ConfigReader::ReadSigs(configFileName);
    std::vector<std::tuple<std::string, uintptr_t, std::string>> offsetInfo {};
    for (SignatureInfo& config : configs)
    {
        Process prc = Process::GetProcess(*gameName, config.module);
        if (auto e = prc.GetError(); e) {
            std::cerr << *e;
            Terminate();
            return 1;
        }
        auto result = Scanner::Scan(config.signature, prc, config);
        if (!result) {
            std::cerr << "Couldn't find signature. Check if you filled config.toml properly." << std::endl;
            Terminate();
            return 1;
        }
        std::cout << "<" << config.module << ">" << " + 0x" << std::hex << *result << std::endl;
        offsetInfo.emplace_back(std::make_tuple(config.name, *result, config.module));
    }

    std::string exptDir = dir + "GameOffsets.hpp";
    Exporter exp(exptDir, offsetInfo);
    exp.WriteDown();
    std::cout << "\nGameOffsetDumper.exe has successfully finished its work:)" << std::endl;
    Terminate();
    return 0;
}