#ifndef CLASSIC_MATERIAL_H
#define CLASSIC_MATERIAL_H

#include "Material.h"
#include "Color.h"

class ClassicMaterial : public Material {
    Color ambient;
    Color diffuse;
    Color specular;
    glm::vec3 emissive;

public:
    ClassicMaterial(Color ambient, Color diffuse, Color specular, glm::vec3 emissive);

    glm::vec3 calcDiffuse(glm::vec3 pos) const override;
    glm::vec3 calcAmbient(glm::vec3 pos) const override;
    glm::vec3 calcSpecular(glm::vec3 pos) const override;
    glm::vec3 calcEmissive(glm::vec3 pos) const override;
};

#endif
