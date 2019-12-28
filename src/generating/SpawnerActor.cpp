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
    int xGridN = config.xGridN;
    int zGridN = config.zGridN; 
    float cellSize = config.cellSize;
    
    vec2 halfOffset = vec2(cellSize, cellSize) * 0.5f;
    vec2 cameraPos2 = Utils::toVec2(cameraPos, Utils::Y);
    vec2 centerOffset = vec2(xGridN, zGridN) * cellSize * -0.5f;
    auto randCellValue = [&]() {
        float range = cellSize * config.randomPositionPercentage / 2;
        return Random::uniform(-range, range);
    };
    for (int x = 0; x < xGridN; x++) {
        for (int z = 0; z < zGridN; z++) {
            vec2 randOffset = vec2(randCellValue(), randCellValue());

            vec2 worldPos = vec2(x, z) * cellSize;
            worldPos += halfOffset + cameraPos2 + config.cameraOffset + centerOffset; 
            worldPos += randOffset;

            if(Random::tossCoin(config.spawnProbability)){
                spawn(worldPos.x, worldPos.y);
            }
        }
    }
}

ActorPtr SpawnerActor::spawn(float x, float z) {
    int idx = Random::range(0, generators.size());
    ModelPtr model = generators[idx]->get();
    
    ActorPtr actor = Actor::create(model);
    addChild(actor);

    float rotation = Random::uniform(0, 360);
    float scale = Random::uniform(config.minElementScale, config.maxElementScale);
    actor->setRotation({0, rotation, 0});
    actor->setScale({scale, scale, scale});

    actor->setPosition({x, 0, z});
    float height = terrain.calcHeight(x, z);
    actor->move({0, height, 0});

    return actor;
}