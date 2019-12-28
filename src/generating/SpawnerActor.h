#ifndef SPAWNER__ACTOR_H
#define SPAWNER__ACTOR_H

#include "Generator.h"
#include "Actor.h"
#include "DiamondSquareTerrain.h"
#include "SpawnerConfig.h"

class SpawnerActor;
using SpawnerActorPtr = std::shared_ptr<SpawnerActor>;

class SpawnerActor : public Actor {
    const SpawnerConfig& config;
    const std::vector<GeneratorPtr>& generators;
    DiamondSquareTerrain& terrain;

public:
    static SpawnerActorPtr create(const SpawnerConfig& config, DiamondSquareTerrain& terrain, glm::vec3 cameraPos);

private:
    SpawnerActor(const SpawnerConfig& config, DiamondSquareTerrain& terrain);

    void spawnAll(glm::vec3 cameraPos);
    ActorPtr spawn(float x, float z);
};

#endif