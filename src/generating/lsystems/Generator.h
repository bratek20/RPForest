#ifndef GENERATOR_H
#define GENERATOR_H

#include "Symbol.h"
#include "Model.h"
#include "LSysConfig.h"

#include <memory>
#include <vector>

class Generator {
public:
    enum LOD {
        LOW = 3,
        MEDIUM = 4,
        HIGH = 5
    };

    using ParamLoader = std::function<void()>;
    static const ParamLoader EMPTY;
     
    Generator(SymbolPtr axiom, std::vector<ParamLoader> paramLoaders, float height, LOD lod, const Material& mat);

    virtual int getN() = 0;

    ModelPtr get(int n);
    ModelPtr getRandom();

private:
    SymbolPtr axiom;
    std::vector<ParamLoader> paramLoaders;
    float height;
    LOD lod;
    const Material& mat;

    std::vector<ModelPtr> models;

    void generateAll();
    ModelPtr generate(SymbolPtr axiom, ParamLoader loader);
};

#endif