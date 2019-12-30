#ifndef GENERATOR_CONFIG_H
#define GENERATOR_CONFIG_H

#include "ConfigParser.h"
#include "Material.h"

#include <iostream>

struct GeneratorConfig;
using GeneratorConfigPtr = std::shared_ptr<GeneratorConfig>;

struct GeneratorConfig : public ConfigParser {
    int n = -1;
    float height = -1;
    int coneBasePoints = 3;
    std::string material;
    float initRadius;

    GeneratorConfig() {
        parse("N", &n);
        parse("Height", &height);
        parse("ConeBasePoints", &coneBasePoints);
        parse("Material", &material);
        parse("InitRadius", &initRadius);
    }

    bool check() const {
        using namespace std;
        if (n == -1) {
            cerr << "Config N not set" << endl;
            return false;
        }
        if (height == -1) {
            cerr << "Config Height not set" << endl;
            return false;
        }
        return true;
    }

    template<typename T>
    const T& as() {
        return static_cast<const T&>(*this);
    }
};

#endif