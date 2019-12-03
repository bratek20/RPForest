#include "Shader.h"

#include <common/shader.hpp>
#include <iostream>

using namespace std;

Shader::Shader(string vsName, string fsName) {
    id = LoadShaders(vsName.c_str(), fsName.c_str());
    use();
}

void Shader::clear() { glDeleteProgram(id); }

void Shader::use() { glUseProgram(id); }

GLuint Shader::getId() const { return id; }

void Shader::applyFloat(const char *name, float value) const {
    GLuint valueId = glGetUniformLocation(id, name);
    glUniform1f(valueId, value);
}

void Shader::applyColor(const char *name, const Color &c)  const {
    GLuint colorId = glGetUniformLocation(id, name);
    glUniform3f(colorId, c.r, c.g, c.b);
}

void Shader::applyColor(const char* name, const glm::vec3& c) const {
    GLuint colorId = glGetUniformLocation(id, name);
    glUniform3f(colorId, c.r, c.g, c.b);
}