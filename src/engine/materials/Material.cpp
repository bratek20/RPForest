#include "Material.h"

void Material::apply(const Shader& shader) const {
    shader.applyColor("AmbientColor", calcAmbient());
    shader.applyColor("DiffuseColor", calcDiffuse());
    shader.applyColor("SpecularColor", calcSpecular());
}

bool Material::isLightSource() const {
    glm::vec3 emissive = calcEmissive();
    return emissive.x > 0 || emissive.y > 0 || emissive.z > 0; 
}