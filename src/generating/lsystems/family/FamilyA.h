#ifndef FAMILY_A_H
#define FAMILY_A_H

#include "Symbols.h"

class FamilyA : public Symbol {
    float t;
public:
    FamilyA(float t) : t(t) {}

    std::vector<SymbolPtr> produce() override;

    std::string toString() override {
        return "";
    }

};

#endif