#include "Generator.h"

#include "Random.h"

using namespace std;

Generator::Generator(SymbolPtr axiom, std::vector<ParamLoader> paramLoaders) {
    for(auto& loader: paramLoaders){
        models.push_back(generate(axiom, loader));
    }
}

ModelPtr Generator::generate(SymbolPtr axiom, ParamLoader paramLoader) {
    int n = paramLoader();
    vector<SymbolPtr> current = {axiom};
    vector<SymbolPtr> next;

    for (int i = 0; i < n; i++) {
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


ModelPtr Generator::get(int n) const {
    return models[n];
}

ModelPtr Generator::getRandom() const {
    return get(Random::range(0, models.size()));
}