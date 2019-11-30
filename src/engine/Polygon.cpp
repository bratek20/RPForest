#include "Polygon.h"

#include <iostream>

using namespace std;

void Polygon::save(glm::vec3 pos) {
    poses.push_back(pos);
}

MeshPtr Polygon::genMesh() {
    vector<Vertex> vertices;
    vector<unsigned int> indices;

    vertices.emplace_back(poses[0]);
    vertices.emplace_back(poses[1]);
    for (int i = 2; i < poses.size(); i++) {
        vertices.emplace_back(poses[i]);
        if(poses[0] != poses[i-1] && poses[0] != poses[i] && poses[i-1] != poses[i]){
            indices.push_back(0);
            indices.push_back(i-1);
            indices.push_back(i);
        }
        else{
            cout << "skipping" << endl;
        }

    }
    cout << "Poses size: " << poses.size() << endl;
    return Mesh::New(vertices, indices);
}
