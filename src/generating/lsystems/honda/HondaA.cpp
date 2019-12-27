#include "Honda.h"
#include "HondaA.h"
#include "HondaB.h"
#include "HondaC.h"

std::vector<SymbolPtr> HondaA::produce() {
    return {
        S<ForwardConeDraw>(l, w),
        S<StartBranch>(),
        S<Pitch>(Honda::C().a0),
        S<HondaB>(l * Honda::C().r2, w * Honda::C().wr),
        S<EndBranch>(),
        S<Roll>(-Honda::C().d),
        S<HondaA>(l*Honda::C().r1, w*Honda::C().wr)
    };
}