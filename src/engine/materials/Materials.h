#ifndef MATERIALS_H
#define MATERIALS_H

#include "ClassicMaterial.h"
#include "LeafMaterial.h"
#include "BarkMaterial.h"
#include "GroundMaterial.h"
#include "PlantMaterial.h"

class Materials {
public:
    static const ClassicMaterial DEFAULT;
    static const ClassicMaterial DEFAULT_LIGHT;
    static const ClassicMaterial NORMAL;
    static const ClassicMaterial DEBUG;
    
    static const LeafMaterial LEAF;
    static const BarkMaterial BARK;
    static const GroundMaterial GROUND;
    static const PlantMaterial PLANT;
};

#endif
