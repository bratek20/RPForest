#ifndef SKY_CONFIG_H
#define SKY_CONFIG_H

#include "ConfigParser.h"

struct SkyConfig : public ConfigParser {
    glm::vec3 sunColor;
    float sunPower;
    float skyLuminanceFactor;

    float latitude;
    float longitude;
    int standardMeridian;
    int julianDay;
    float timeOfDay; 
    float turbidity;
    
    SkyConfig() {
        parse("SunColor", &sunColor);
        parse("SunPower", &sunPower);
        parse("SkyLuminanceFactor", &skyLuminanceFactor);

        parse("Latitude", &latitude);
        parse("Longitude", &longitude);
        parse("StandardMeridian", &standardMeridian);
        parse("JulianDay", &julianDay);
        parse("TimeOfDay", &timeOfDay);
        parse("Turbidity", &turbidity);
    }
};

#endif