#include "Honda.h"
#include "HondaA.h"
#include "HondaB.h"
#include "HondaC.h"

std::vector<SymbolPtr> HondaC::produce() {
    return {
        S<SetWidth>(w),
        S<ForwardDraw>(l),
        S<StartBranch>(),
        S<Turn>(Honda::a2),
        S<CenterLeft>(),
        S<HondaB>(l * Honda::r2, w * Honda::wr),
        S<EndBranch>(),
        S<HondaB>(l*Honda::r1, w*Honda::wr)
    };
}