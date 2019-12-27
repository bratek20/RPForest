#include "Generator.h"

#include "Random.h"
#include "Shapes.h"

using namespace std;
GeneratorConfigPtr Generator::CONF;

Generator::Generator(SymbolPtr axiom, GeneratorConfigPtr config) :
    axiom(axiom), config(config) {}

ModelPtr Generator::generate() {
    if(!config->check()){
        cerr << "Config check failed for: " << config->getPath() << endl;
        return Model::New();
    }

    int prevPoints = Shapes::getConeBasePointsNum();
    const Material* prevMat = Shapes::getConeMaterial();
    GeneratorConfigPtr prevConf = CONF;

    Shapes::setConeBasePointsNum(config->coneBasePoints);
    Shapes::setConeMaterial(&Materials::get(config->material));
    CONF = config;

    vector<SymbolPtr> current = {axiom};
    vector<SymbolPtr> next;
    for (int i = 0; i < config->n; i++) {
        for (auto &s : current) {
            auto result = s->produce();
            next.insert(next.end(), result.begin(), result.end());
        }
        current = std::move(next);
        next.clear();
        //cout << current.size() << endl;
    }

    ProcessContext pc;
    for (auto &s : current) {
        s->process(pc);
    }
    pc.model->matchHeight(config->height);

    Shapes::setConeBasePointsNum(prevPoints);
    Shapes::setConeMaterial(prevMat);
    CONF = prevConf;

    return pc.model;
}


ModelPtr Generator::get() {
    if(model == nullptr) {
        model = generate();
    }
    return model;
}