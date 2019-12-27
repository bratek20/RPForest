#ifndef GENERATOR_CONFIG_CASTER_H
#define GENERATOR_CONFIG_CASTER_H

#include "Generator.h"

template<typename T>
class GeneratorConfigCaster {
public:
    static const T& C(){
        return static_cast<const T&>(*Generator::CONF);
    }
};

#endif