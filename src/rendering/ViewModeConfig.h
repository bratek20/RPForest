#ifndef VIEW_MODE_CONFIG_H
#define VIEW_MODE_CONFIG_H

#include "ConfigParser.h"

struct ViewModeConfig : public ConfigParser {
    bool enabled = false;
    glm::vec2 resolution = glm::vec2(800, 600);
    float cameraVelocity = 10;
    
    ViewModeConfig() {
        parse("Enabled", &enabled);
        parse("Resolution", &resolution);
        parse("CameraVelocity", &cameraVelocity);
    }
};

#endif