#ifndef GROUND_MATERIAL_H
#define GROUND_MATERIAL_H

#include "Material.h"

class GroundMaterial : public Material {
    glm::vec3 calcDiffuse(glm::vec3 pos) const override;
};

#endif
