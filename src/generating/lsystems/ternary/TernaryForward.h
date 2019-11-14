#ifndef TERNARY_FORWARD_H
#define TERNARY_FORWARD_H

#include "Symbols.h"
#include "Ternary.h"

class TernaryForward : public ForwardDraw {
    float l;
public:
    TernaryForward(float l) : ForwardDraw(l), l(l) {} 

    std::vector<SymbolPtr> produce() override {
        return {S<TernaryForward>(l * Ternary::lr)};
    }

    void process(ProcessContext& pc) override {
        ForwardDraw::process(pc);
        pc.current.bend(Ternary::T, Ternary::e);
    }
};

#endif