#ifndef FAMILY_B_H
#define FAMILY_B_H

#include "Symbols.h"

class FamilyB : public Symbol {
    float t;
public:
    FamilyB(float t) : t(t) {}

    std::vector<SymbolPtr> produce() override;

    std::string toString() override {
        return "";
    }

};

#endif