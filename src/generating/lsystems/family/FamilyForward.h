#ifndef FAMILY_FORWARD_H
#define FAMILY_FORWARD_H

#include "Symbols.h"

class FamilyForward : public ForwardDraw {
    float s;
    float r;
public:
    FamilyForward(float s, float r) : ForwardDraw(s), s(s), r(r) {}

    std::vector<SymbolPtr> produce() override;

    std::string toString() override {
        return "";
    }

};

#endif