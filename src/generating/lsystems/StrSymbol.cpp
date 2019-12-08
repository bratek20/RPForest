#include "StrSymbol.h"
#include "Symbols.h"
#include <unordered_map>

using namespace std;

StrSymbol::StrSymbol(std::string&& str, const LSysConfig& config) : str(str), config(config) {

}

vector<SymbolPtr> StrSymbol::produce() {
    vector<SymbolPtr> symbols;
    for(char c : str){
        symbols.push_back(createSymbol(c));
    }
    return symbols;
}

SymbolPtr StrSymbol::createSymbol(char c) {
    switch (c)
    {
    case 'F':
        return S<ForwardDraw>(1);
    case '[':
        return S<StartBranch>();
    case ']':
        return S<EndBranch>();
    case '+':
        return S<Turn>(config.angle);
    case '-':
        return S<Turn>(-config.angle); 
    default:
        cerr << "Symbol " << c << " not supported!" << endl;
        throw runtime_error("Symbol nout found");
        break;
    }
}