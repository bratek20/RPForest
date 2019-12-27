#ifndef HONDA_H
#define HONDA_H

#include "Generator.h"
#include "GeneratorConfigCaster.h"
#include "HondaConfig.h"

class Honda : public Generator, public GeneratorConfigCaster<HondaConfig> {
public:
    Honda(GeneratorConfigPtr config);
};

#endif