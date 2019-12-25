#include "Generator.h"

#include "Random.h"
#include "Shapes.h"

using namespace std;

const Generator::ParamLoader Generator::EMPTY = [](){};

Generator::Generator(SymbolPtr axiom, std::vector<ParamLoader> paramLoaders, float height, LOD lod, const Material& mat) :
    axiom(axiom), paramLoaders(paramLoaders), height(height), lod(lod), mat(mat) {}

void Generator::generateAll() {
    int prevLod = Shapes::getConeBasePointsNum();
    const Material* prevMat = Shapes::getConeMaterial();

    Shapes::setConeBasePointsNum(lod);
    Shapes::setConeMaterial(&mat);
    
    for(auto& loader: paramLoaders){
        models.push_back(generate(axiom, loader));
    }

    Shapes::setConeBasePointsNum(prevLod);
    Shapes::setConeMaterial(prevMat);
}

ModelPtr Generator::generate(SymbolPtr axiom, ParamLoader paramLoader) {
    paramLoader();
    vector<SymbolPtr> current = {axiom};
    vector<SymbolPtr> next;

    for (int i = 0; i < getN(); i++) {
        for (auto &s : current) {
            auto result = s->produce();
            next.insert(next.end(), result.begin(), result.end());
        }
        current = std::move(next);
        next.clear();
    }

    ProcessContext pc;
    for (auto &s : current) {
        s->process(pc);
    }

    pc.model->matchHeight(height);
    return pc.model;
}


ModelPtr Generator::get(int n) {
    if(models.empty()) {
        generateAll();
    }
    return models[n];
}

ModelPtr Generator::getRandom() {
    return get(Random::range(0, models.size()));
}