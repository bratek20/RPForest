#ifndef LEAF_MATERIAL_H
#define LEAF_MATERIAL_H

#include "Material.h"

class LeafMaterial : public Material {
    glm::vec3 calcDiffuse(glm::vec3 pos) const override;
};

#endif
