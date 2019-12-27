#include "FamilyA.h"
#include "Family.h"
#include "FamilyForward.h"
#include "FamilyB.h"

std::vector<SymbolPtr> FamilyA::produce() {
    return {
        S<FamilyForward>(Family::C().LA, Family::C().RA),
        
        S<StartBranch>(),
        S<Turn>(-Family::C().delta),
        S<FamilyB>(t),
        S<SaveVertex>(),
        S<EndBranch>(),

        S<StartBranch>(),
        S<FamilyA>(t+1),
        S<EndBranch>(),

        S<StartBranch>(),
        S<Turn>(+Family::C().delta),
        S<FamilyB>(t),
        S<SaveVertex>(),
        S<EndBranch>(),
    };
}