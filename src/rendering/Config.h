#ifndef CONFIG_H
#define CONFIG_H

#include "ConfigParser.h"

struct Config : public ConfigParser {
    std::string photoName;
    glm::vec2 resolution;
    int samples = 1;
    int maxRayBounces = 5;
    bool debugMode = false;
    
    Config();
};

#endif