#include "Honda.h"
#include "HondaA.h"
#include "HondaB.h"
#include "HondaC.h"

std::vector<SymbolPtr> HondaB::produce() {
    return {
        S<SetWidth>(w),
        S<ForwardDraw>(l),
        S<StartBranch>(),
        S<Turn>(-Honda::a2),
        S<CenterLeft>(),
        S<HondaC>(l * Honda::r2, w * Honda::wr),
        S<EndBranch>(),
        S<HondaC>(l*Honda::r1, w*Honda::wr)
    };
}