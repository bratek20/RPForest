

#include "Mesh.h"
#include "Globals.h"
#include "Utils.h"

#include <iostream>
#include <limits>

using namespace std;
using namespace glm;

const unsigned int Mesh::VAO_NOT_SET = numeric_limits<unsigned int>::max();

Mesh::Mesh(vector<vec3> vertices) {
    drawLines = true;
    for (auto& v : vertices) {
        this->vertices.push_back(Vertex(v));
    }
    for (int i = 0; i < vertices.size(); i++) {
        indices.push_back(i);
    }
    material = Material::DEFAULT;
    setup(false);
}

Mesh::Mesh(vector<Vertex> vertices,
           vector<unsigned int> indices,
           bool genNormals,
           Material material)
    : vertices(move(vertices)), indices(move(indices)), material(material) {
    setup(genNormals);
}

void Mesh::apply(const mat4& m) {
    apply(m, Utils::calcNormM(m));
}

void Mesh::apply(const glm::mat4& posM, const glm::mat3& normM) {
    for (auto& v : vertices) {
        v.apply(posM, normM);
    }

    setupDraw();
}

void Mesh::draw(Shader& shader) {
    material.apply(shader);

    // draw mesh
    glBindVertexArray(VAO);
    if (indices.empty()) {
        glDrawArrays(GL_LINES, 0, VAO);
    } else if (indices.size() < 3) {
        glDrawElements(GL_LINES, indices.size(), GL_UNSIGNED_INT, 0);
    } else {
        glDrawElements(drawLines ? GL_LINE_STRIP : GL_TRIANGLES, indices.size(),
                       GL_UNSIGNED_INT, 0);
    }
    glBindVertexArray(0);

    // always good practice to set everything back to defaults once configured.
    glActiveTexture(GL_TEXTURE0);
}

void Mesh::setup(bool genNormals) {
    if (indices.size() % 3 == 0) {
        setupTriangles(genNormals);
    }
    setupDraw();
}

void Mesh::setupTriangles(bool genNormals) {
    triangles.clear();
    vector<vec3> normals;
    vector<int> count;
    if (genNormals) {
        normals.resize(vertices.size());
        count.resize(vertices.size());
    }

    for (unsigned i = 0; i < indices.size(); i += 3) {
        triangles.emplace_back(vertices[indices[i]], vertices[indices[i + 1]],
                               vertices[indices[i + 2]], material);
        if (genNormals) {
            vec3 normal = triangles.back().calcBaseNormal();
            for (int k = 0; k <= 2; k++) {
                normals[indices[i + k]] += normal;
                count[indices[i + k]]++;
            }
        }
    }

    if(genNormals){
        for(int i=0;i<vertices.size();i++){
            vertices[i].normal = normalize(normals[i] * (1.0f / count[i]));
        }
    }
}

void Mesh::setupDraw() {
    if (!Globals::debug) {
        return;
    }
    // create buffers/arrays
    if(VAO == VAO_NOT_SET) {
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);
    }

    glBindVertexArray(VAO);
    // load data into vertex buffers
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex),
                 &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int),
                 &indices[0], GL_STATIC_DRAW);

    // set the vertex attribute pointers
    // vertex Positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    // vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          (void*)offsetof(Vertex, normal));

    glBindVertexArray(0);
}

vector<Vertex>& Mesh::getVertices() {
    return vertices;
}

vector<unsigned int>& Mesh::getIndices() {
    return indices;
}

const vector<Triangle>& Mesh::getTriangles() const {
    return triangles;
}

TrianglePtr Mesh::getTriangle(int idx) const {
    return &triangles[idx];
}

void Mesh::debug() {
    for (auto& v : vertices) {
        v.debug();
    }
}
