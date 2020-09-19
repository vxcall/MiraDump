#include "Scanner.h"
#include <vector>
#include <iostream>

void Scanner::FindPattern(std::vector<int>& signature, Process& process)
{
    std::vector<std::byte> buffer(process.moduleBaseSize);
    ReadProcessMemory(process.hProcess, static_cast<LPCVOID>(process.moduleBaseAddress), buffer.data(), buffer.size(), NULL);
    int iStore = 0;
    for (int i = 0;i < buffer.size();++i) {
        for (int j = 0;j < signature.size();++j) {
            iStore = i;
            if (signature.at(j) == -1 || static_cast<std::byte>(signature.at(j)) == buffer.at(i)) {
                if (j + 1 == signature.size()) {
                    std::cout << "FOUND" << std::endl;
                    return;
                }
                //std::cout << signature.at(j) << " " << static_cast<int>(buffer.at(i)) << std::endl;
                i++;
            } else {
                i = iStore;
                break;
            }
        }
    }
}