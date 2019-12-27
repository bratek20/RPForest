#ifndef CLASSIC_MATERIAL_H
#define CLASSIC_MATERIAL_H

#include "Material.h"

class ClassicMaterial : public Material {
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    glm::vec3 emissive;

public:
    ClassicMaterial() {}
    ClassicMaterial(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 emissive);

    glm::vec3 calcDiffuse(glm::vec3 pos) const override;
    glm::vec3 calcAmbient(glm::vec3 pos) const override;
    glm::vec3 calcSpecular(glm::vec3 pos) const override;
    glm::vec3 calcEmissive(glm::vec3 pos) const override;
};

#endif
