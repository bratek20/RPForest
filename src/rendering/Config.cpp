#include "Config.h"

#include <iostream>

using namespace std;

Material LightConfig::DEFAULT_MAT = Material(Color(0.8f, 0.8f, 0.8f), 
                                    Color(0.8f, 0.8f, 0.8f),
                                    Color(0.0f, 0.0f, 0.0f),
                                    glm::vec3(17, 12, 4),
                                    10);

Mesh LightConfig::createMesh() const {
    return Mesh({v1, v2, v3}, {0, 1, 2}, LightConfig::DEFAULT_MAT);
}

bool Config::load(const string &path) {
    ifstream file(path);
    if (!file.is_open()) {
        cerr << "File: " << path << " not opened!";
        return false;
    }

    getline(file, comment);
    getline(file, loadScenePath);
    getline(file, photoName);
    file >> k;
    file >> xRes >> yRes;
    camera.viewPoint = readVec3(file);
    camera.lookAt = readVec3(file);
    camera.up = readVec3(file);
    file >> camera.yView;

    string type;
    while (file >> type) {
        if (type == "L") {
            LightConfig lc;
            lc.v1 = Vertex(readVec3(file));
            lc.v2 = Vertex(readVec3(file));
            lc.v3 = Vertex(readVec3(file));
            lc.color = readColor(file);
            file >> lc.intensity;
            lights.push_back(lc);
        } else if (type == "LC") {
            lightCoef = readVec3(file);
        } else if (type == "CV") {
            file >> camera.velocity;
        } else if (type == "BG") {
            background = readColor(file);
        } else if (type == "DM") {
            file >> debugMode;
        } else if (type == "RE") {
            file >> rayEpsilon;
        } else if (type == "SN") {
            file >> samplesNum;
        } else {
            cerr << "Type: " << type << " not supported!" << endl;
        }
    }

    for (auto &lc : lights) {
        lc.coefficients = lightCoef;
    }
    return true;
}

glm::vec3 Config::readVec3(ifstream &file) {
    float x, y, z;
    file >> x >> y >> z;
    return glm::vec3(x, y, z);
}

Color Config::readColor(std::ifstream &file) {
    int r, g, b;
    file >> r >> g >> b;
    unsigned char cr = r, cg = g, cb = b;
    return Color(cr, cg, cb);
}