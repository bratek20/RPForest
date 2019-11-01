#ifndef MATERIAL_H
#define MATERIAL_H

#include <glm/glm.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Shader.h"
#include "Color.h"
#include "Texture.h"

#include <string>
#include <vector>

struct Material {
    static Material DEFAULT;
    static Material DEFAULT_LIGHT;
    
    unsigned int id;
    Color ambient;
    Color diffuse;
    Color specular;
    glm::vec3 emissive;
    float ns;

    Material() = default;
    Material(Color ambient, Color diffuse, Color specular, glm::vec3 emissive, float ns);
    void apply(Shader& shader);

    Color getTextureColor(float u, float v) const;
    bool isLightSource() const;
};

#endif
