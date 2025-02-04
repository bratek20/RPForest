

#ifndef MESH_H
#define MESH_H

#include "Ptr.h"
#include "Shader.h"
#include "Triangle.h"
#include "Materials.h"

class Mesh;
using MeshPtr = std::shared_ptr<Mesh>;

class Mesh : public Ptr<Mesh, MeshPtr> {
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Triangle> triangles;
    const Material& material;
    bool drawLines = false;

   public:
    Mesh(std::vector<glm::vec3> vertices);
    Mesh(std::vector<Vertex> vertices,
         std::vector<unsigned int> indices,
         bool genNormals,
         const Material& material = Materials::DEFAULT);

    ~Mesh();
    void clear();

    void merge(MeshPtr mesh);

    void apply(const glm::mat4& m);
    void apply(const glm::mat4& posM, const glm::mat3& normM);
    void draw(Shader& shader);

    MeshPtr copy() const;

    std::vector<Vertex>& getVertices();
    std::vector<unsigned int>& getIndices();
    const std::vector<Triangle>& getTriangles() const;
    TrianglePtr getTriangle(int idx) const;
    const Material& getMaterial() const;

    void debug();
    
   private:
    static const unsigned int VAO_NOT_SET;
    unsigned int VAO = VAO_NOT_SET;
    unsigned int VBO, EBO;
    bool drawDirty = true;

    void setup(bool genNormals);
    void setupTriangles(bool genNormals);
    void setupDraw();
};
#endif
