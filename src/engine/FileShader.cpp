#include "FileShader.h"

#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

FileShader::FileShader(const string& vsPath, const string& fsPath) : Shader(getCode(vsPath), getCode(fsPath)) {
}

string FileShader::getCode(const string& path) {
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

    return shaderCode;
}