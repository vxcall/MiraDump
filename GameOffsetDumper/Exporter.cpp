#include "Exporter.h"
#include <fstream>

Exporter::Exporter(std::string& filename, std::vector<std::tuple<std::string, uintptr_t, std::string>>& offsetInfo)
:filename(filename), offsetInfo(offsetInfo)
{}

void Exporter::WriteDown() {
    std::ofstream file(filename);
    file << "namespace GameOffsetDumper {" << std::endl;
    for (auto& info : offsetInfo) {
        file << "    constexpr uintptr_t " << std::get<0>(info) << " = " << "0x" << std::hex << std::get<1>(info) << " //" << std::get<2>(info) << std::endl;
    }
    file << "}";
    file.close();
}
