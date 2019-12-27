#ifndef GENERATOR_H
#define GENERATOR_H

#include "Symbol.h"
#include "Model.h"
#include "GeneratorConfig.h"

#include <memory>
#include <vector>

class Generator;
using GeneratorPtr = std::shared_ptr<Generator>;

class Generator {
    SymbolPtr axiom;
    GeneratorConfigPtr config;

    ModelPtr model;

public:
    static GeneratorConfigPtr CONF;

    Generator(SymbolPtr axiom, GeneratorConfigPtr config);

    ModelPtr get();

private:
    ModelPtr generate();
};

#endif