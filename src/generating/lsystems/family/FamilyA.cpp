#include "FamilyA.h"
#include "Family.h"
#include "FamilyForward.h"
#include "FamilyB.h"

std::vector<SymbolPtr> FamilyA::produce() {
    return {
        S<FamilyForward>(Family::LA, Family::RA),
        
        S<StartBranch>(),
        S<Turn>(-Family::delta),
        S<FamilyB>(t),
        S<SaveVertex>(),
        S<EndBranch>(),

        S<StartBranch>(),
        S<FamilyA>(t+1),
        S<EndBranch>(),

        S<StartBranch>(),
        S<Turn>(+Family::delta),
        S<FamilyB>(t),
        S<SaveVertex>(),
        S<EndBranch>(),
    };
}