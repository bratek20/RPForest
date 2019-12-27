#include "Honda.h"
#include "HondaA.h"
#include "HondaB.h"
#include "HondaC.h"

std::vector<SymbolPtr> HondaC::produce() {
    return {
        S<ForwardConeDraw>(l, w),
        S<StartBranch>(),
        S<Turn>(Honda::C().a2),
        S<CenterLeft>(),
        S<HondaB>(l * Honda::C().r2, w * Honda::C().wr),
        S<EndBranch>(),
        S<HondaB>(l*Honda::C().r1, w*Honda::C().wr),
        S<Leaf>()
    };
}