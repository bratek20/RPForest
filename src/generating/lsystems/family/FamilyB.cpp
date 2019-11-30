#include "Family.h"
#include "FamilyForward.h"
#include "FamilyB.h"

std::vector<SymbolPtr> FamilyB::produce() {
    if(t <= 0){
        return {};
    }
    return {
        S<FamilyForward>(Family::LB, Family::RB),
        S<FamilyB>(t-Family::PD)
    };
}