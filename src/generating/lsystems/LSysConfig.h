#ifndef L_SYS_CONFIG_H
#define L_SYS_CONFIG_H

#include "GeneratorConfig.h"

#include <unordered_map>

struct LSysConfig : GeneratorConfig {
    int lSysN;
    float angle;
    std::string axiom;
    std::unordered_map<char, std::string> productions;

    LSysConfig() {
        parse("Angle", &angle);
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

        material = "Plant";
    }
};

#endif