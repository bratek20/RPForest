

#ifndef MESH_H
#define MESH_H

#include "Shader.h"
#include "Triangle.h"

class Mesh {
public:
    /*  Mesh Data  */
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Triangle> triangles;
    Material material;
    unsigned int VAO;
    bool drawLines = false;
    /*  Functions  */
    // constructor
    Mesh() = default;
    Mesh(std::vector<glm::vec3> vertices);
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, const Material& material);

    // render the mesh
    void draw(Shader& shader);
    const std::vector<Triangle>& getTriangles() const;
    TrianglePtr getTriangle(int idx) const;

private:
    /*  Render data  */
    unsigned int VBO, EBO;

    /*  Functions    */
    // initializes all the buffer objects/arrays
    void setupMesh();
};
#endif

