#ifndef GENERATOR_H
#define GENERATOR_H

#include "Symbol.h"

#include <memory>
#include <vector>

class Generator {
    SymbolPtr axiom;
    int n;
    
public:
    Generator(SymbolPtr axiom, int n);

    ProcessContext generate();
};

#endif