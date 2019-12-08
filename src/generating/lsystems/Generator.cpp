#include "Generator.h"

#include "Random.h"

using namespace std;

const Generator::ParamLoader Generator::EMPTY = [](){};

Generator::Generator(SymbolPtr axiom, std::vector<ParamLoader> paramLoaders) :
    axiom(axiom), paramLoaders(paramLoaders) {}

void Generator::generateAll() {
    for(auto& loader: paramLoaders){
        models.push_back(generate(axiom, loader));
        onModelGenerated(models.back());
    }
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