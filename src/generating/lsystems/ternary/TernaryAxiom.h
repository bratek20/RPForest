#ifndef TERNARY_AXIOM_H
#define TERNARY_AXIOM_H

#include "Symbols.h"
#include "TernaryA.h"

class TernaryAxiom : public Symbol {
public:
    std::vector<SymbolPtr> produce() {
        return {
            S<TernaryForwardCone>(2, 0.01),
            S<Roll>(45),
            S<TernaryA>()
        };
    }
};

#endif