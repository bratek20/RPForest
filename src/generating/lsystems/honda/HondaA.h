#ifndef HONDA_A_H
#define HONDA_A_H

#include "Symbols.h"

class HondaA : public Symbol {
    float l;
    float w;

public:
    HondaA(float l, float w) : l(l), w(w) {} 

    std::vector<SymbolPtr> produce() override;

    std::string toString() override {
        return "HondaA(" + std::to_string(l) + ", " + std::to_string(w) + ")";
    }

};

#endif