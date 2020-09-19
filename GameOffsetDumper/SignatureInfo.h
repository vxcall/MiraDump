#pragma once
#include <string>
#include <vector>

class SignatureInfo {
private:
    [[nodiscard]] std::vector<int> SigParserXX() const;
    [[nodiscard]] std::vector<int> SigParserQuestion() const;

    std::string signatureString;
public:
    std::string name;
    std::vector<int> signature;
    std::string module;
    const int offset;
    const int extra;
    SignatureInfo(std::string& name, std::string& signatureString, std::string& module, const int& offset, const int& extra);
};