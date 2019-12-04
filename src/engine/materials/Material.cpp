#include "Material.h"

void Material::apply(const Shader& shader) const {
    shader.applyColor("AmbientColor", calcAmbient(glm::vec3()));
    shader.applyColor("DiffuseColor", calcDiffuse(glm::vec3()));
    shader.applyColor("SpecularColor", calcSpecular(glm::vec3()));
}

bool Material::isLightSource() const {
    glm::vec3 emissive = calcEmissive(glm::vec3());
    return emissive.x > 0 || emissive.y > 0 || emissive.z > 0; 
}