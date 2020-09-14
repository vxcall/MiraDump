#include "SignatureInfo.h"

SignatureInfo::SignatureInfo(std::string& name, std::string signature, std::string& module, const int& offset, const int& extra)
        : name(name), module(module), offset(offset), extra(extra)
{
    if (signature.find("xx") != std::string::npos) {
        this->signature = SignatureInfo::SigParserXX(signature);
    } else if (signature.find('?') != std::string::npos) {
        this->signature = SignatureInfo::SigParserQuestion(signature);
    }
}

std::vector<int> SignatureInfo::SigParserXX(std::string& sig) {
    int i = 0;
    int sigSize = sig.size();
    std::vector<int> result;
    result.reserve(45);
    while (sigSize > i) {
        std::string byte = sig.substr(i, 2);
        if (byte == "xx") {
            result.push_back(-1);
        } else {
            result.push_back(std::stoi(byte, 0, 16));
        }
        i += 2;
    }
    return result;
}

std::vector<int> SignatureInfo::SigParserQuestion(std::string& sig) {
    return std::vector<int>{};
}
