#ifndef SPAWNER_CONFIG_H
#define SPAWNER_CONFIG_H

#include "ConfigParser.h"

struct SpawnerConfig : public ConfigParser {
    glm::vec2 cameraOffset;
    int xGridN = 1;
    int zGridN = 1;
    float cellSize = 0;
    
    std::string generatorType;
    float spawnProbability = 1; 
    
    SpawnerConfig() {
        parse("CameraOffset", &cameraOffset);
        parse("XGridN", &xGridN);
        parse("ZGridN", &zGridN);
        parse("CellSize", &cellSize);
        parse("GeneratorType", &generatorType);
        parse("SpawnProbability", &spawnProbability);
    }
};

#endif