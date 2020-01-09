#ifndef CAMERA_CONFIG_H
#define CAMERA_CONFIG_H

#include "ConfigParser.h"

struct CameraConfig : public ConfigParser {
    float lookHeight = 1;
    glm::vec3 lookDirection = glm::vec3(0, 0, 1);
    float lookDistance = 2;
    
    float edgeMinOffset = 10;
    float expectedPositionY = 0;
    
    CameraConfig() {
        parse("LookHeight", &lookHeight);
        parse("LookDirection", &lookDirection);
        parse("LookDistance", &lookDistance);
        parse("EdgeMinOffset", &edgeMinOffset);
        parse("ExpectedPositionY", &expectedPositionY);
    }
};

#endif