#ifndef SPAWNER__ACTOR_H
#define SPAWNER__ACTOR_H

#include "Generator.h"
#include "Actor.h"
#include "DiamondSquareTerrain.h"

class SpawnerActor;
using SpawnerActorPtr = std::shared_ptr<SpawnerActor>;

class SpawnerActor : public Actor {
    const std::vector<GeneratorPtr>& generators;
    DiamondSquareTerrain& terrain;

public:
    static SpawnerActorPtr create(const std::vector<GeneratorPtr>& generators, DiamondSquareTerrain& terrain, glm::vec3 center, int xGridN, int zGridN, float cellSize);

private:
    SpawnerActor(const std::vector<GeneratorPtr>& generators, DiamondSquareTerrain& terrain);

    void spawnAll(glm::vec3 center, int xGridN, int zGridN, float cellSize);
    ActorPtr spawn(float x, float z);
};

#endif