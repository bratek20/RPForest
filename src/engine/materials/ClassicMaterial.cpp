#include "ClassicMaterial.h"

using namespace std;

ClassicMaterial::ClassicMaterial(glm::vec3 ambient,
                   glm::vec3 diffuse,
                   glm::vec3 specular,
                   glm::vec3 emissive)
    : ambient(ambient),
      diffuse(diffuse),
      specular(specular),
      emissive(emissive){}

glm::vec3 ClassicMaterial::calcDiffuse(glm::vec3 pos) const {
    return diffuse;
}

glm::vec3 ClassicMaterial::calcAmbient(glm::vec3 pos) const {
    return ambient;
}

glm::vec3 ClassicMaterial::calcSpecular(glm::vec3 pos) const {
    return specular;
}

glm::vec3 ClassicMaterial::calcEmissive(glm::vec3 pos) const {
    return emissive;    
}