#include "Config.h"

#include <iostream>

using namespace std;

MeshPtr LightConfig::createMesh() const {
    return Mesh::New(vector<Vertex>{v1, v2, v3}, vector<unsigned int>{0, 1, 2}, true, Materials::DEFAULT_LIGHT);
}

bool Config::load(const string &path) {
    ifstream file(path);
    if (!file.is_open()) {
        cerr << "File: " << path << " not opened!";
        return false;
    }

    string type;
    while (file >> type) {
        if (type == "#") {
            // comments
            string comment;
            getline(file, comment);
            (void)comment;
        } else if (type == "NAME") {
            file >> photoName;
        } else if (type == "K") {
            file >> k;
        } else if (type == "RES") {
            file >> xRes >> yRes;
        } else if (type == "POS") {
            camera.pos = readVec3(file);
        } else if (type == "LOOK_AT") {
            camera.lookAt = readVec3(file);
        } else if (type == "UP") {
            camera.up = readVec3(file);
        } else if (type == "YVIEW") {
            file >> camera.yView;
        } else if (type == "L") {
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