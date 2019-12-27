#include "SpawnerActor.h"
#include "Assets.h"
#include "LSysGenerator.h"
#include "Random.h"

using namespace std;
using namespace glm;

SpawnerActor::SpawnerActor(const std::vector<GeneratorPtr>& generators,
                           DiamondSquareTerrain& terrain)
    : Actor(nullptr), generators(generators), terrain(terrain) {}

SpawnerActorPtr SpawnerActor::create(
    const std::vector<GeneratorPtr>& generators,
    DiamondSquareTerrain& terrain,
    glm::vec3 center,
    int xGridN,
    int zGridN,
    float cellSize) {

    SpawnerActorPtr spawner =
        SpawnerActorPtr(new SpawnerActor(generators, terrain));
    spawner->spawnAll(center, xGridN, zGridN, cellSize);
    return spawner;
}

void SpawnerActor::spawnAll(vec3 center, int xGridN, int zGridN, float cellSize) {
    for (int x = 0; x < xGridN; x++) {
        for (int z = 0; z < zGridN; z++) {
            float X = x * cellSize + center.x;
            float Z = z * cellSize + center.z;  
            spawn(X, Z);
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