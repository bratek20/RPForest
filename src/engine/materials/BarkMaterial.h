#ifndef BARK_MATERIAL_H
#define BARK_MATERIAL_H

#include "Material.h"

class BarkMaterial : public Material {
public:
    BarkMaterial() : Material("Bark") {}

    glm::vec3 calcDiffuse(glm::vec3 pos) const override;
};

#endif
