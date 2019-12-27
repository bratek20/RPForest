#include "Family.h"
#include "FamilyForward.h"
#include "FamilyB.h"

std::vector<SymbolPtr> FamilyB::produce() {
    if(t <= 0){
        return {};
    }
    return {
        S<FamilyForward>(Family::C().LB, Family::C().RB),
        S<FamilyB>(t-Family::C().PD)
    };
}