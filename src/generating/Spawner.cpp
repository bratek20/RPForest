#include "Spawner.h"
#include "Assets.h"
#include "LSysGenerator.h"
#include "Random.h"

using namespace std;

Spawner::Spawner(const std::vector<GeneratorPtr>& generators, const std::string& lSysFolder, Generator::LOD lod, const Material& mat) {
    this->generators.insert(this->generators.end(), generators.begin(), generators.end());
    auto lSysConfigs = Assets::loadLSysConfigs(lSysFolder);
    for(auto& config : lSysConfigs) {
        this->generators.push_back(GeneratorPtr(new LSysGenerator(config, lod, mat)));
    }
}

ActorPtr Spawner::spawn() {
    int idx = Random::range(1, generators.size());
    ModelPtr model = generators[idx]->getRandom();
    ActorPtr actor = Actor::create(model);
    static float i = 0;
    actor->move(glm::vec3(1,0,0) * i);
    i+=1;
    return actor;
}