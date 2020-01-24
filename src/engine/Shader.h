#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>

#include "Color.h"

class Shader {
    char infoLog[512];
protected:
    GLuint id;

public:
    Shader() {}
    Shader(const std::string& vsCode, const std::string& fsCode);

    void clear();
    void use();    
    GLuint getId() const;
    
    void applyFloat(const char* name, float value) const;
    void applyColor(const char* name, const Color& c) const;
    void applyColor(const char* name, const glm::vec3& c) const;

private:
    GLuint makeProgram(const std::string& vsCode, const std::string& fsCode); 
    GLuint compileShader(const std::string& program, GLuint type);
};

#endif