#ifndef STR_SYMBOL_H
#define STR_SYMBOL_H

#include "Symbol.h"
#include "LSysConfig.h"
#include <string>

class StrSymbol : public Symbol {
    std::string str;
    LSysConfig config;

public:
    StrSymbol(std::string&& str, const LSysConfig& config);
    std::vector<SymbolPtr> produce() override;

private:
    SymbolPtr createSymbol(char c);

};

#endif