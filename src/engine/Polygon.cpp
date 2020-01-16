#include "Polygon.h"

#include <iostream>

using namespace std;

void Polygon::save(glm::vec3 pos) {
    poses.push_back(pos);
}

MeshPtr Polygon::genMesh(const Material& mat) {
    vector<Vertex> vertices;
    vector<unsigned int> indices;

    vertices.emplace_back(poses[0]);
    vertices.emplace_back(poses[1]);
    for (unsigned int i = 2; i < poses.size(); i++) {
        auto firstPos = vertices[0].position;
        auto lastPos = vertices.back().position;
        if(firstPos != lastPos && firstPos != poses[i] && lastPos != poses[i]){
            vertices.emplace_back(poses[i]);

            indices.push_back(0);
            indices.push_back(vertices.size()-2);
            indices.push_back(vertices.size()-1);
        }
    }
    return Mesh::New(vertices, indices, true, mat);
}
