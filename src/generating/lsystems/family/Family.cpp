#include "Family.h"
#include "FamilyAxiom.h"

Family::Family(GeneratorConfigPtr config)
    : Generator(Symbol::S<FamilyAxiom>(), config) {}