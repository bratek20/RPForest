#include "Material.h"

using namespace std;

Material Material::DEFAULT = Material(Color(0.8f, 0.8f, 0.8f),
                                         Color(0.1f, 0.8f, 0.2f),
                                         Color(0.0f, 0.0f, 0.0f),
                                         glm::vec3(0, 0, 0),
                                         10);

Material Material::DEFAULT_LIGHT = Material(Color(0.0f, 0.0f, 0.0f),
                                         Color(1.0f, 1.0f, 1.0f),
                                         Color(0.0f, 0.0f, 0.0f),
                                         glm::vec3(17, 12, 4),
                                         10);

Material::Material(Color ambient,
                   Color diffuse,
                   Color specular,
                   glm::vec3 emissive,
                   float ns)
    : ambient(ambient),
      diffuse(diffuse),
      specular(specular),
      emissive(emissive),
      ns(ns) {}

bool Material::isLightSource() const {
    return emissive.x > 0 || emissive.y > 0 || emissive.z > 0;
}

void Material::apply(Shader& shader) {
    shader.applyFloat("NS", ns);
    shader.applyColor("AmbientColor", ambient);
    shader.applyColor("DiffuseColor", diffuse);
    shader.applyColor("SpecularColor", specular);
}