#include "Exporter.h"
#include <fstream>

Exporter::Exporter(std::string& filename, std::vector<std::tuple<std::string, uintptr_t, std::string>>& resultInfo)
:filename(filename), resultInfo(resultInfo)
{}

void Exporter::WriteDown() {
    std::ofstream file(filename);
    file << "namespace MiraDump {" << std::endl;
    for (auto& result : resultInfo) {
        file << "    constexpr uintptr_t " << std::get<0>(result) << " = " << "0x" << std::hex << std::get<1>(result) << " //" << std::get<2>(result) << std::endl;
    }
    file << "}";
    file.close();
}
