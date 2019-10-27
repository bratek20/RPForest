#ifndef HONDA_B_H
#define HONDA_B_H

#include "Symbols.h"

class HondaB : public Symbol {
    float l;
    float w;

public:
    HondaB(float l, float w) : l(l), w(w) {} 

    std::vector<SymbolPtr> produce() override;

    std::string toString() override {
        return "HondaB(" + std::to_string(l) + ", " + std::to_string(w) + ")";
    }

};

#endif