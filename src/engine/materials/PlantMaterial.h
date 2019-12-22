#ifndef PLANT_MATERIAL_H
#define PLANT_MATERIAL_H

#include "Material.h"

class PlantMaterial : public Material {
    glm::vec3 calcDiffuse(glm::vec3 pos) const override;
};

#endif
