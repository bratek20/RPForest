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
    float randomPositionPercentage = 0.5;
    float minElementScale = 0.5;
    float maxElementScale = 2;
    
    SpawnerConfig() {
        parse("CameraOffset", &cameraOffset);
        parse("XGridN", &xGridN);
        parse("ZGridN", &zGridN);
        parse("CellSize", &cellSize);
        
        parse("GeneratorType", &generatorType);
        parse("SpawnProbability", &spawnProbability);
        parse("RandomPositionPercentage", &randomPositionPercentage);
        parse("MinElementScale", &minElementScale);
        parse("MaxElementScale", &maxElementScale);
    }
};

#endif