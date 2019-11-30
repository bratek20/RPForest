#ifndef POLYGON_H
#define POLYGON_H

#include "Mesh.h"

class Polygon {
    std::vector<glm::vec3> poses;

   public:
    void save(glm::vec3 pos);
    MeshPtr genMesh();
};

#endif