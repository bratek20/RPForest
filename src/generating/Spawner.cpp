#include "Spawner.h"
#include "Assets.h"
#include "LSysGenerator.h"
#include "Random.h"

using namespace std;
using namespace glm;

Spawner::Spawner(const vector<GeneratorPtr>& generators, const string& lSysFolder, Generator::LOD lod, const Material& mat, DiamondSquareTerrain& terrain) :
    terrain(terrain) {
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
    vec3 pos = vec3(1,0,0) * i;
    pos.y = terrain.calcHeight(pos.x, pos.z);
    cout << pos << endl;
    actor->move(pos);
    i+=1;
    return actor;
}