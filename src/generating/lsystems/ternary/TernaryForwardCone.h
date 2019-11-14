#ifndef TERNARY_FORWARD_CONE_H
#define TERNARY_FORWARD_CONE_H

#include "Symbols.h"
#include "Ternary.h"

class TernaryForwardCone : public ForwardConeDraw {
    float l;
    float w;
public:
    TernaryForwardCone(float l, float w) : ForwardConeDraw(l, w), l(l), w(w) {} 

    std::vector<SymbolPtr> produce() override {
        return {S<TernaryForwardCone>(l * Ternary::lr, w * Ternary::vr)};
    }

    void process(ProcessContext& pc) override {
        ForwardConeDraw::process(pc);
        pc.current.bend(Ternary::T, Ternary::e);
    }

    std::string toString() override {
        return "";
    }

};

#endif