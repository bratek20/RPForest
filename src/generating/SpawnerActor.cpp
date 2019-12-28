#include "SpawnerActor.h"
#include "Assets.h"
#include "LSysGenerator.h"
#include "Random.h"

using namespace std;
using namespace glm;

SpawnerActor::SpawnerActor(const SpawnerConfig& config,
                           DiamondSquareTerrain& terrain)
    : Actor(nullptr), config(config), generators(Assets::getGenerators(config.generatorType)), terrain(terrain) {}

SpawnerActorPtr SpawnerActor::create(
    const SpawnerConfig& config,
    DiamondSquareTerrain& terrain,
    glm::vec3 cameraPos) {

    SpawnerActorPtr spawner =
        SpawnerActorPtr(new SpawnerActor(config, terrain));
    spawner->spawnAll(cameraPos);
    return spawner;
}

void SpawnerActor::spawnAll(vec3 cameraPos) {
    for (int x = 0; x < config.xGridN; x++) {
        for (int z = 0; z < config.zGridN; z++) {
            float worldX = x * config.cellSize + cameraPos.x + config.cameraOffset.x;
            float worldZ = z * config.cellSize + cameraPos.z + config.cameraOffset.y;  
            
            if(Random::tossCoin(config.spawnProbability)){
                spawn(worldX, worldZ);
            }
        }
    }
}

ActorPtr SpawnerActor::spawn(float x, float z) {
    int idx = Random::range(0, generators.size());
    ModelPtr model = generators[idx]->get();
    ActorPtr actor = Actor::create(model);
    addChild(actor);
    
    actor->setPosition({x, 0, z});
    float height = terrain.calcHeight(x, z);
    actor->move({0, height, 0});

    return actor;
}