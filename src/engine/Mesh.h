

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
         bool genNormals,
         Material material = Material::DEFAULT);

    void apply(const glm::mat4& m);
    void apply(const glm::mat4& posM, const glm::mat3& normM);
    void draw(Shader& shader);

    std::vector<Vertex>& getVertices();
    std::vector<unsigned int>& getIndices();
    const std::vector<Triangle>& getTriangles() const;
    TrianglePtr getTriangle(int idx) const;

    void debug();
    
   private:
    static const unsigned int VAO_NOT_SET;
    unsigned int VAO = VAO_NOT_SET;
    unsigned int VBO, EBO;

    void setup(bool genNormals);
    void setupTriangles(bool genNormals);
    void setupDraw();
};
#endif
