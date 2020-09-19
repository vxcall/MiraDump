#include "Scanner.h"
#include <vector>
#include <iostream>

void Scanner::FindPattern(std::vector<int>& signature, Process& process)
{
    std::vector<std::byte> buffer(process.moduleBaseSize);
    std::cout << signature.size() << std::endl;
    ReadProcessMemory(process.hProcess, static_cast<LPCVOID>(process.moduleBaseAddress), buffer.data(), buffer.size(), NULL);
    for (int i = 0;i < buffer.size();++i) {
        for (int j = 0;j < signature.size();++j) {
            if (signature.at(j) == -1 || static_cast<std::byte>(signature.at(j)) == buffer.at(i)) {
                if (j == signature.size()) {
                    std::cout << "FOUND" << std::endl;
                }
                continue;
            } else { //static_cast<std::byte>(signature.at(j)) != buffer.at(i)
                break;
            }
        }
    }
}