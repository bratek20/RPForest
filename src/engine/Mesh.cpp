

#include "Mesh.h"
#include "Globals.h"
#include "Utils.h"

#include <iostream>

using namespace std;

Mesh::Mesh(std::vector<glm::vec3> vertices) {
    drawLines = true;
    for (auto& v : vertices) {
        this->vertices.push_back(Vertex(v));
    }
    for (int i = 0; i < vertices.size(); i++) {
        indices.push_back(i);
    }
    material = Material::DEFAULT;
    setupMesh();
}

Mesh::Mesh(vector<Vertex> vertices,
           vector<unsigned int> indices,
           Material material)
    : vertices(move(vertices)), indices(move(indices)), material(material) {

    setupMesh();
}

void Mesh::apply(const glm::mat4& m) {
    for(auto& v : vertices) {
        v.apply(m);
    }

    setupMesh();
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
        glDrawElements(drawLines ? GL_LINES : GL_TRIANGLES, indices.size(),
                       GL_UNSIGNED_INT, 0);
    }
    glBindVertexArray(0);

    // always good practice to set everything back to defaults once configured.
    glActiveTexture(GL_TEXTURE0);
}
void Mesh::setupMesh() {
    triangles.clear();
    if (indices.size() % 3 == 0) {
        for (unsigned i = 0; i < indices.size(); i += 3) {
            triangles.emplace_back(vertices[indices[i]],
                                   vertices[indices[i + 1]],
                                   vertices[indices[i + 2]], material);
        }
    }

    if (!Globals::debug) {
        return;
    }
    // create buffers/arrays
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    // load data into vertex buffers
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // A great thing about structs is that their memory layout is sequential for
    // all its items. The effect is that we can simply pass a pointer to the
    // struct and it translates perfectly to a glm::vec3/2 array which again
    // translates to 3/2 floats which translates to a byte array.
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

    // vertex texture coords
    // glEnableVertexAttribArray(2);
    // glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
    //                       (void *)offsetof(Vertex, uv));
    // // vertex tangent
    // glEnableVertexAttribArray(3);
    // glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
    // (void*)offsetof(Vertex, tangent));
    // // vertex bitangent
    // glEnableVertexAttribArray(4);
    // glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
    // (void*)offsetof(Vertex, bitangent));

    glBindVertexArray(0);
}

std::vector<Vertex>& Mesh::getVertices() {
    return vertices;
}

std::vector<unsigned int>& Mesh::getIndices() {
    return indices;
}

const vector<Triangle>& Mesh::getTriangles() const {
    return triangles;
}

TrianglePtr Mesh::getTriangle(int idx) const {
    return &triangles[idx];
}

void Mesh::debug() {
    for(auto& v: vertices) {
        v.debug();
    }
}
