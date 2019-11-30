#include "FamilyAxiom.h"
#include "FamilyA.h"

std::vector<SymbolPtr> FamilyAxiom::produce() {
    return {
        S<StartPolygon>(),
        S<FamilyA>(0),
        S<EndPolygon>()
    };
}