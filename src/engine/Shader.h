#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>

#include "Color.h"

class Shader {
protected:
    GLuint id;

public:
    Shader() {}
    Shader(std::string vsName, std::string fsName);

    void clear();
    void use();    
    GLuint getId() const;
    
    void applyFloat(const char* name, float value) const;
    void applyColor(const char* name, const Color& c) const;
    void applyColor(const char* name, const glm::vec3& c) const;
};

#endif