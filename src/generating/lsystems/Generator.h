#ifndef GENERATOR_H
#define GENERATOR_H

#include "Symbol.h"
#include "Model.h"

#include <memory>
#include <vector>

class Generator {
    std::vector<ModelPtr> models;

public:
    using ParamLoader = std::function<int()>;

    Generator(SymbolPtr axiom, std::vector<ParamLoader> paramLoaders);

    ModelPtr get(int n) const;
    ModelPtr getRandom() const;

private:
    ModelPtr generate(SymbolPtr axiom, ParamLoader loader);
};

#endif