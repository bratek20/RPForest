#ifndef HONDA_CONFIG_H
#define HONDA_CONFIG_H

#include "GeneratorConfig.h"

struct HondaConfig : public GeneratorConfig {
    float r1;
    float r2;
    float a0;
    float a2;
    float d;
    float wr;
    
    HondaConfig() {
        parse("R1", &r1);
        parse("R2", &r2);
        parse("A0", &a0);
        parse("A2", &a2);
        parse("D", &d);
        parse("Wr", &wr);

        coneBasePoints = 6;
        height = 2.0f;
        material = "Bark";
        initRadius = 0.2f;
    }
};

#endif