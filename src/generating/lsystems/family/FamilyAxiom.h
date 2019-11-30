#ifndef FAMILY_AXIOM_H
#define FAMILY_AXIOM_H

#include "Symbols.h"

class FamilyAxiom : public Symbol {
public:
    std::vector<SymbolPtr> produce() override;

    std::string toString() override {
        return "";
    }

};

#endif