#ifndef TERRAIN_CONFIG_H
#define TERRAIN_CONFIG_H

#include "ConfigParser.h"

struct TerrainConfig : public ConfigParser {
    int n;
    float size;
    float initHeight;
    float spread;
    float spreadReductionRate;
    
    TerrainConfig() {
        parse("N", &n);
        parse("Size", &size);
        parse("InitHeight", &initHeight);
        parse("Spread", &spread);
        parse("SpreadReductionRate", &spreadReductionRate);
    }
};

#endif