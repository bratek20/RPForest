#ifndef FILE_SHADER_H
#define FILE_SHADER_H

#include "Shader.h"

class FileShader : public Shader {
public:
    FileShader() {}
    FileShader(const std::string& vsPath, const std::string& fsPath);

private: 
    std::string getCode(const std::string& path);
};

#endif