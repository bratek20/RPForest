#include "Shader.h"

#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

Shader::Shader(const string& vsPath, const string& fsPath) {
    id = makeProgram(vsPath, fsPath);
    use();
}

GLuint Shader::makeProgram(const string& vsPath, const string& fsPath) {
    GLuint vertexId = compileShader(vsPath, GL_VERTEX_SHADER);
    GLuint fragmentId = compileShader(fsPath, GL_FRAGMENT_SHADER);

    GLuint id = glCreateProgram();
    glAttachShader(id, vertexId);
    glAttachShader(id, fragmentId);
    glLinkProgram(id);

    int success;
    glGetProgramiv(id, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(id, 512, NULL, infoLog);
        cout << "Failed to link shader program\n" << infoLog << endl;
    }

    glDeleteShader(vertexId);
    glDeleteShader(fragmentId);
    return id;
}

GLuint Shader::compileShader(const string& path, GLuint type) {
    string shaderCode;
    ifstream shaderFile;
    shaderFile.exceptions(ifstream::failbit | ifstream::badbit);
    try {
        shaderFile.open(path);

        stringstream shaderStream;
        shaderStream << shaderFile.rdbuf();
        shaderCode = shaderStream.str();

        shaderFile.close();
    } catch (ifstream::failure e) {
        cout << "Failed ot read shader file: " << path << endl;
    }

    const char* cShaderCode = shaderCode.c_str();
    GLuint id = glCreateShader(type);
    glShaderSource(id, 1, &cShaderCode, NULL);
    glCompileShader(id);

    int success;
    glGetShaderiv(id, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(id, 512, NULL, infoLog);
        cerr << "Shader compilation failed for: " << path << "\n"
             << infoLog << endl;
    };

    return id;
}

void Shader::clear() {
    glDeleteProgram(id);
}

void Shader::use() {
    glUseProgram(id);
}

GLuint Shader::getId() const {
    return id;
}

void Shader::applyFloat(const char* name, float value) const {
    GLuint valueId = glGetUniformLocation(id, name);
    glUniform1f(valueId, value);
}

void Shader::applyColor(const char* name, const Color& c) const {
    GLuint colorId = glGetUniformLocation(id, name);
    glUniform3f(colorId, c.r, c.g, c.b);
}

void Shader::applyColor(const char* name, const glm::vec3& c) const {
    GLuint colorId = glGetUniformLocation(id, name);
    glUniform3f(colorId, c.r, c.g, c.b);
}