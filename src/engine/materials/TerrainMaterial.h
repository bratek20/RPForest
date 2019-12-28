#ifndef TERRAIN_MATERIAL_H
#define TERRAIN_MATERIAL_H

#include "Material.h"

class TerrainMaterial : public Material {
public:
    TerrainMaterial() : Material("Terrain") {}
    
    glm::vec3 calcDiffuse(glm::vec3 pos) const override;
    
    glm::vec3 calcGrassColor(glm::vec3 pos) const;
    glm::vec3 calcRockColor(glm::vec3 pos) const;
};

#endif
