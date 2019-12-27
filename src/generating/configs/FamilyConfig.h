#ifndef FAMILY_CONFIG_H
#define FAMILY_CONFIG_H

#include "GeneratorConfig.h"

struct FamilyConfig : public GeneratorConfig {
    float delta;
    float LA;
    float RA;
    float LB;
    float RB;
    float PD;
    
    FamilyConfig() {
        parse("delta", &delta);
        parse("LA", &LA);
        parse("RA", &RA);
        parse("LB", &LB);
        parse("RB", &RB);
        parse("PD", &PD);

        height = 0.2f;
    }
};

#endif