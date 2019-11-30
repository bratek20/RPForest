#include "FamilyForward.h"

std::vector<SymbolPtr> FamilyForward::produce() {
    return {
        S<FamilyForward>(s*r, r)
    };
}