#ifndef TERNARY_AXIOM_H
#define TERNARY_AXIOM_H

#include "Symbols.h"
#include "TernaryRadius.h"
#include "TernaryForward.h"
#include "TernaryA.h"

class TernaryAxiom : public Symbol {
public:
    std::vector<SymbolPtr> produce() {
        return {
            S<TernaryRadius>(0.01),
            S<TernaryForward>(2),
            S<Roll>(45),
            S<TernaryA>()
        };
    }
};

#endif