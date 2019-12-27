#ifndef LEAF_MATERIAL_H
#define LEAF_MATERIAL_H

#include "Material.h"

class LeafMaterial : public Material {
public:
    LeafMaterial() : Material("Leaf") {}

    glm::vec3 calcDiffuse(glm::vec3 pos) const override;
};

#endif
