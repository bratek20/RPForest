#include "Honda.h"
#include "HondaA.h"

Honda::Honda(GeneratorConfigPtr config)
    : Generator(Symbol::S<HondaA>(1, 0.1), config) {}
