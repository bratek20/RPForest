#ifndef L_SYS_CONFIG_H
#define L_SYS_CONFIG_H

#include "GeneratorConfig.h"

#include <unordered_map>

struct LSysConfig : GeneratorConfig {
    int lSysN;
    
    float turnAngle = 0;
    float pitchAngle = 0;
    float rollAngle = 0;

    std::string axiom;
    std::unordered_map<char, std::string> productions;

    LSysConfig() {
        parse("TurnAngle", &turnAngle);
        parse("PitchAngle", &pitchAngle);
        parse("RollAngle", &rollAngle);        
        
        parse("Axiom", &axiom);
        customParse("Prod", [&](std::ifstream& file){
            std::string symbol, arrow, production;
            file >> symbol >> arrow >> production;
            productions[symbol[0]] = production;
        });
        customParse("N", [&](std::ifstream& file){
            file >> lSysN;
            n = 1;
        });

        initRadius = 0.3f;
        material = "Plant";
    }
};

#endif