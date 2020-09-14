#include <string_view>
#include "SignatureInfo.h"
#include <vector>

class ConfigReader {
public:
    static std::vector<SignatureInfo> Read(const std::string& filename);
};