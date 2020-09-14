#include <string>

class SignatureInfo {
public:
    std::string name;
    std::string signature;
    std::string module;
    int offset;
    int extra;
};