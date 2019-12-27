#ifndef CONFIG_H
#define CONFIG_H

#include "ConfigParser.h"

struct Config : public ConfigParser {
    std::string photoName;
    glm::vec2 resolution;
    int samples = 1;
    int maxRayBounces = 5;
    bool debugMode = false;
    
    Config() {
        customParse("#", [](std::ifstream& file){
            std::string comment;
            getline(file, comment);
            (void)comment;
        });
        parse("PhotoName", &photoName);
        parse("Resolution", &resolution);
        parse("Samples", &samples);
        parse("MaxRayBounces", &maxRayBounces);
        parse("DebugMode", &debugMode);
    }
};

#endif