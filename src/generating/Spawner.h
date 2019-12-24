#ifndef SPAWNER_H
#define SPAWNER_H

#include "Generator.h"
#include "Actor.h"
#include "DiamondSquareTerrain.h"

class Spawner {
    std::vector<GeneratorPtr> generators;
    DiamondSquareTerrain& terrain;

public:
    Spawner(const std::vector<GeneratorPtr>& generators, const std::string& lSysFolder, Generator::LOD lod, const Material& mat, DiamondSquareTerrain& terrain);

    ActorPtr spawn();
};

#endif