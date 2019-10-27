#include "Honda.h"
#include "HondaA.h"
#include "HondaB.h"
#include "HondaC.h"

std::vector<SymbolPtr> HondaA::produce() {
    return {
        S<SetWidth>(w),
        S<ForwardDraw>(l),
        S<StartBranch>(),
        S<Pitch>(Honda::a0),
        S<HondaB>(l * Honda::r2, w * Honda::wr),
        S<EndBranch>(),
        S<Roll>(-Honda::d),
        S<HondaA>(l*Honda::r1, w*Honda::wr)
    };
}