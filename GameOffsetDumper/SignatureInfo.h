#include <string>
#include <vector>

class SignatureInfo {
private:
    static std::vector<int> SigParserXX(std::string& sig);
    static std::vector<int> SigParserQuestion(std::string& sig);
public:
    std::string name;
    std::vector<int> signature;
    std::string module;
    const int offset;
    const int extra;
    SignatureInfo(std::string& name, std::string signature, std::string& module, const int& offset, const int& extra);
};