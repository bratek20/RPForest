#ifndef TERNARY_A_H
#define TERNARY_A_H

#include "Symbols.h"
#include "TernaryRadius.h"
#include "TernaryForward.h"
#include "Ternary.h"

class TernaryA : public Symbol {
public:
    std::vector<SymbolPtr> produce() override {
        return {
            S<TernaryRadius>(Ternary::vr * 0.01),
            S<TernaryForward>(0.5),
            S<StartBranch>(),
            S<Pitch>(Ternary::a),
            S<TernaryForward>(0.5),
            S<TernaryA>(),
            S<EndBranch>(),
            S<Roll>(Ternary::d1),

            S<StartBranch>(),
            S<Pitch>(Ternary::a),
            S<TernaryForward>(0.5),
            S<TernaryA>(),
            S<EndBranch>(),
            S<Roll>(Ternary::d2),

            S<StartBranch>(),
            S<Pitch>(Ternary::a),
            S<TernaryForward>(0.5),
            S<TernaryA>(),
            S<EndBranch>(),
        };
    }
};

#endif