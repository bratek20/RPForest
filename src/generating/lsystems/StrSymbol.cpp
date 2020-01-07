#include "StrSymbol.h"
#include "Symbols.h"
#include <unordered_map>

using namespace std;

StrSymbol::StrSymbol(std::string&& str, const LSysConfig& config) : str(str), config(config) {

}

vector<SymbolPtr> StrSymbol::produce() {
    vector<SymbolPtr> symbols;
    symbols.push_back(S<SetRadius>(config.initRadius));
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
    case 'f':
        return S<ForwardMove>(1);
    case '[':
        return S<StartBranch>();
    case ']':
        return S<EndBranch>();
    case '+':
        return S<Turn>(config.turnAngle);
    case '-':
        return S<Turn>(-config.turnAngle); 
    case '^':
        return S<Pitch>(-config.pitchAngle);
    case '&':
        return S<Pitch>(config.pitchAngle); 
    case '\\':
        return S<Roll>(config.rollAngle);
    case '/':
        return S<Roll>(-config.rollAngle);
    case '|':
        return S<Turn>(180);  
    case '{':
        return S<StartPolygon>(); 
    case '.':
        return S<SaveVertex>(); 
    case '}':
        return S<EndPolygon>();   
    default:
        return nullptr;
    }
}