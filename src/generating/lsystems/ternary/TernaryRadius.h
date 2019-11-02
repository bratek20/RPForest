#ifndef TERNARY_RADIUS_H
#define TERNARY_RADIUS_H

#include "Symbols.h"
#include "Ternary.h"

class TernaryRadius : public SetRadius {
    float w;

public:
    TernaryRadius(float w) : SetRadius(w), w(w) {} 

    std::vector<SymbolPtr> produce() override {
        return {
            S<TernaryRadius>(w * Ternary::vr)
        };
    }
};

#endif