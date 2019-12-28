#ifndef MATERIALS_H
#define MATERIALS_H

#include "ClassicMaterial.h"
#include "LeafMaterial.h"
#include "BarkMaterial.h"
#include "TerrainMaterial.h"
#include "PlantMaterial.h"

#include <unordered_map>

class Materials {
    static std::unordered_map<std::string, const Material*> materials;

public:
    static const ClassicMaterial DEFAULT;
    static const ClassicMaterial DEBUG;
    
    static const LeafMaterial LEAF;
    static const BarkMaterial BARK;
    static const TerrainMaterial TERRAIN;
    static const PlantMaterial PLANT;

    static ClassicMaterial SUN;
    
    static void init();

    static const Material& get(const std::string& name);

private:
    static void add(const Material& mat);
};

#endif
