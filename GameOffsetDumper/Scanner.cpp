#include "Scanner.h"
#include <vector>
#include <optional>
#include "DebugMessage.h"

std::optional<uintptr_t> Scanner::FindPattern(std::vector<int>& signature, Process& process, std::vector<std::byte> moduleByte)
{
    int iStore = 0;
    for (int i = 0;i < moduleByte.size() - signature.size() + 1;++i) {
        for (int j = 0;j < signature.size();++j) {
            iStore = i;
            if (signature.at(j) == -1 || static_cast<std::byte>(signature.at(j)) == moduleByte.at(i)) {
                if (j + 1 == signature.size()) {
                    int position = i - static_cast<int>(signature.size()) + 1;
                    return position;
                }
                i++;
            } else {
                i = iStore;
                break;
            }
        }
    }
    return std::optional<uintptr_t>{};
}

std::optional<uintptr_t> Scanner::Scan(Process &process, SignatureInfo& sigInfo, std::vector<std::byte> moduleByte) {
    std::optional<uintptr_t> result = Scanner::FindPattern(sigInfo.signature, process, moduleByte);
    if (!result)
        return std::optional<uintptr_t> {};

    if (sigInfo.x64relative)
    {
        DWORD buffer1;
        ReadProcessMemory(
                process.hProcess,
                static_cast<LPCVOID>(process.moduleBaseAddress + *result + 0x3),
                &buffer1, sizeof(buffer1),
                NULL
                );
        LOGHEX("rip", ((uintptr_t)process.moduleBaseAddress + *result + sigInfo.offset))
        LOGHEX("offset", buffer1)
        uintptr_t dynamic = ((uintptr_t)process.moduleBaseAddress + *result + 0x7) + buffer1;
        LOGHEX("baseWeaponAddress", dynamic)

        return dynamic - (uintptr_t)process.moduleBaseAddress + sigInfo.extra;
    } else {
        DWORD buffer;
        ReadProcessMemory(process.hProcess, static_cast<LPCVOID>(process.moduleBaseAddress + *result + sigInfo.offset), &buffer, sizeof(buffer), NULL);
        return buffer - (uintptr_t)process.moduleBaseAddress + sigInfo.extra;
    }
}