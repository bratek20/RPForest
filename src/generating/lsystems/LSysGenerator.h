#ifndef L_SYS_GENERATOR_H
#define L_SYS_GENERATOR_H

#include "Generator.h"
#include "GeneratorConfigCaster.h"
#include "LSysConfig.h"

class LSysGenerator : public Generator {
public:
    LSysGenerator(GeneratorConfigPtr config);
    
private:
    SymbolPtr generateAxiom(const LSysConfig& config);
};

#endif