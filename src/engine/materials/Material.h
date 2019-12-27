#ifndef MATERIAL_H
#define MATERIAL_H

#include <glm/glm.hpp>

#include "Shader.h"

class Material {
    std::string name;

public:
    Material(const std::string& name);
    virtual ~Material() {}

    void apply(const Shader& shader) const;

    bool isLightSource() const;
    const std::string& getName() const;
    
    virtual glm::vec3 calcDiffuse(glm::vec3 pos) const { return pos; };
    virtual glm::vec3 calcAmbient(glm::vec3 pos) const { return calcDiffuse(pos); };
    virtual glm::vec3 calcSpecular(glm::vec3 pos) const { return pos; };
    virtual glm::vec3 calcEmissive(glm::vec3 pos) const { return glm::vec3(); };
};

#endif
