#ifndef PATH_TRACER_CONFIG_H
#define PATH_TRACER_CONFIG_H

#include "ConfigParser.h"

struct PathTracerConfig : public ConfigParser {
    std::string photoName;
    glm::vec2 resolution;
    int samples = 1;
    int maxRayBounces = 5;
    bool debugMode = false;
    
    PathTracerConfig() {
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