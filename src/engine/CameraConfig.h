#ifndef CAMERA_CONFIG_H
#define CAMERA_CONFIG_H

#include "ConfigParser.h"

struct CameraConfig : public ConfigParser {
    float lookHeight = 1;
    glm::vec3 lookDirection = glm::vec3(0, 0, 1);
    float edgeMinOffset = 10;

    float expectedPositionY = 0;
    float expectedArea = 0;
    float expectedHeightDiffs = 0;
    
    float debugVelocity = 10;
    
    CameraConfig() {
        parse("LookHeight", &lookHeight);
        parse("LookDirection", &lookDirection);
        parse("EdgeMinOffset", &edgeMinOffset);

        parse("ExpectedPositionY", &expectedPositionY);
        parse("ExpectedArea", &expectedArea);
        parse("ExpectedHeightDiffs", &expectedHeightDiffs);
        
        parse("DebugVelocity", &debugVelocity);
    }
};

#endif