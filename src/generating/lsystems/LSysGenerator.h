#ifndef L_SYS_GENERATOR_H
#define L_SYS_GENERATOR_H

#include "Generator.h"
#include "LSysConfig.h"

class LSysGenerator : public Generator {
public:
    LSysGenerator(const LSysConfig& config);
    
    int getN() override { return 1; };

private:
    SymbolPtr generateAxiom(const LSysConfig& config);
};

#endif