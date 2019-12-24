#include "Spawner.h"
#include "Assets.h"
#include "LSysGenerator.h"
#include "Random.h"

using namespace std;
using namespace glm;

float zg = 0;
Spawner::Spawner(const vector<GeneratorPtr>& generators, const string& lSysFolder, Generator::LOD lod, const Material& mat, DiamondSquareTerrain& terrain) :
    terrain(terrain), generators(generators) {
    z=zg;
    zg+=0.5;
    auto lSysConfigs = Assets::loadLSysConfigs(lSysFolder);
    for(auto& config : lSysConfigs) {
        this->generators.push_back(GeneratorPtr(new LSysGenerator(config, lod, mat)));
    }
}

ActorPtr Spawner::spawn() {
    int idx = Random::range(0, generators.size());
    ModelPtr model = generators[idx]->getRandom();
    ActorPtr actor = Actor::create(model);
    
    vec3 pos = vec3(x,0,z);
    pos.y = terrain.calcHeight(pos.x, pos.z);
    cout << pos << endl;
    actor->move(pos);
    x+=0.5;
    return actor;
}