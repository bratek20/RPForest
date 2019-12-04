#ifndef GENERATOR_H
#define GENERATOR_H

#include "Symbol.h"
#include "Model.h"

#include <memory>
#include <vector>

class Generator {
public:
    using ParamLoader = std::function<void()>;

    Generator(SymbolPtr axiom, std::vector<ParamLoader> paramLoaders);

    virtual int getN() = 0;
    virtual void onModelGenerated(ModelPtr model) { }

    ModelPtr get(int n);
    ModelPtr getRandom();

private:
    SymbolPtr axiom;
    std::vector<ParamLoader> paramLoaders;
    std::vector<ModelPtr> models;

    void generateAll();
    ModelPtr generate(SymbolPtr axiom, ParamLoader loader);
};

#endif