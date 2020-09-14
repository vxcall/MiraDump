#include <string>
#include <vector>

class SignatureInfo {
private:
    std::vector<int> SigParserXX();
    std::vector<int> SigParserQuestion();
public:
    std::string name;
    std::string signatureString;
    std::vector<int> signature;
    std::string module;
    const int offset;
    const int extra;
    SignatureInfo(std::string& name, std::string& signatureString, std::string& module, const int& offset, const int& extra);
};