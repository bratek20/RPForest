#ifndef FAMILY_H
#define FAMILY_H

#include "Generator.h"
#include "GeneratorConfigCaster.h"
#include "FamilyConfig.h"

class Family : public Generator, public GeneratorConfigCaster<FamilyConfig> {
public:
    Family(GeneratorConfigPtr config);
};

#endif