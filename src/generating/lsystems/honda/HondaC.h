#ifndef HONDA_C_H
#define HONDA_C_H

#include "Symbols.h"

class HondaC : public Symbol {
    float l;
    float w;

public:
    HondaC(float l, float w) : l(l), w(w) {} 

    std::vector<SymbolPtr> produce() override;

    std::string toString() override {
        return "HondaC(" + std::to_string(l) + ", " + std::to_string(w) + ")";
    }

};

#endif