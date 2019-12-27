#include "Honda.h"
#include "HondaA.h"
#include "HondaB.h"
#include "HondaC.h"

std::vector<SymbolPtr> HondaB::produce() {
    return {
        S<ForwardConeDraw>(l, w),
        S<StartBranch>(),
        S<Turn>(-Honda::C().a2),
        S<CenterLeft>(),
        S<HondaC>(l * Honda::C().r2, w * Honda::C().wr),
        S<EndBranch>(),
        S<HondaC>(l*Honda::C().r1, w*Honda::C().wr),
        S<Leaf>()
    };
}