#ifndef DEBUG_CONFIG_H
#define DEBUG_CONFIG_H

#include "ConfigParser.h"

struct DebugConfig : public ConfigParser {
    bool enabled = false;
    glm::vec2 resolution = glm::vec2(800, 600);
    float cameraVelocity = 10;
    
    DebugConfig() {
        parse("Enabled", &enabled);
        parse("Resolution", &resolution);
        parse("CameraVelocity", &cameraVelocity);
    }
};

#endif