#pragma once
#include <string>
#include <vector>

class SigProfile {
private:
    [[nodiscard]] std::vector<int> SigParserXX() const;
    [[nodiscard]] std::vector<int> SigParserQuestion() const;
public:
    bool x64relative;
    std::string name;
    std::string signatureString;
    std::vector<int> signature;
    std::string module;
    const int offset;
    const int extra;
    SigProfile(std::string& name, const std::string& signatureString, std::string& module, const int& offset, const int& extra, const bool& x64relative);
};