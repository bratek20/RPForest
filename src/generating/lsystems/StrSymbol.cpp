#include "StrSymbol.h"
#include "Symbols.h"
#include <unordered_map>

using namespace std;

StrSymbol::StrSymbol(std::string&& str, const LSysConfig& config) : str(str), config(config) {

}

vector<SymbolPtr> StrSymbol::produce() {
    vector<SymbolPtr> symbols;
    symbols.push_back(S<SetRadius>(0.3));
    for(char c : str){
        auto symbol = createSymbol(c);
        if(symbol != nullptr){
            symbols.push_back(symbol);
        }
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
        return nullptr;
    }
}