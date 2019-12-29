#ifndef TERRAIN_CONFIG_H
#define TERRAIN_CONFIG_H

#include "ConfigParser.h"

struct TerrainConfig : public ConfigParser {
    int n;
    float size;
    float initHeight;
    float spread;
    float spreadReductionRate;
    
    float rockStartY = 10;
    float groundEndY = 20;

    TerrainConfig() {
        parse("N", &n);
        parse("Size", &size);
        parse("InitHeight", &initHeight);
        parse("Spread", &spread);
        parse("SpreadReductionRate", &spreadReductionRate);

        parse("RockStartY", &rockStartY);
        parse("GroundEndY", &groundEndY);
    }
};

#endif