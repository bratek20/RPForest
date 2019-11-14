#ifndef GENERATOR_H
#define GENERATOR_H

#include "Symbol.h"

#include <memory>
#include <vector>

class Generator {
    SymbolPtr axiom;

public:
    Generator(SymbolPtr axiom);

    virtual int getN() = 0;
    
    ProcessContext generate();
};

#endif