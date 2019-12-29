#ifndef MATERIAL_CONFIG_H
#define MATERIAL_CONFIG_H

#include "ConfigParser.h"

struct MaterialConfig : public ConfigParser {
    glm::vec3 color1;
    glm::vec3 color2;
    float noisePositionFactor = 1;
    float noiseValueFactor = 1;

    MaterialConfig() {
        parse("Color1", &color1);
        parse("Color2", &color2);
        parse("NoisePositionFactor", &noisePositionFactor);
        parse("NoiseValueFactor", &noiseValueFactor);
    }
};

#endif