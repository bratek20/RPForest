

#ifndef MESH_H
#define MESH_H

#include "Ptr.h"
#include "Shader.h"
#include "Triangle.h"

class Mesh;
using MeshPtr = std::shared_ptr<Mesh>;

class Mesh : public Ptr<Mesh, MeshPtr> {
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Triangle> triangles;
    Material material;
    bool drawLines = false;

   public:
    Mesh(std::vector<glm::vec3> vertices);
    Mesh(std::vector<Vertex> vertices,
         std::vector<unsigned int> indices,
         Material material = Material::DEFAULT);

    void draw(Shader& shader);

    std::vector<Vertex>& getVertices();
    std::vector<unsigned int>& getIndices();
    const std::vector<Triangle>& getTriangles() const;
    TrianglePtr getTriangle(int idx) const;

   private:
    unsigned int VAO, VBO, EBO;

    void setupMesh();
};
#endif
