#ifndef SPAWNER_H
#define SPAWNER_H

#include "Generator.h"
#include "Actor.h"

class Spawner {
    std::vector<GeneratorPtr> generators;

public:
    Spawner(const std::vector<GeneratorPtr>& generators, const std::string& lSysFolder, Generator::LOD lod, const Material& mat);

    ActorPtr spawn();
};

#endif