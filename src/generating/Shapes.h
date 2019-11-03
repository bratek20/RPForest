#ifndef SHAPES_H
#define SHAPES_H

#include "Mesh.h"

class Shapes {
public:
    static MeshPtr genCone(float downRadius, float upRadius, float height);
    static MeshPtr genPlane(float width, float depth);

private:
    static std::vector<glm::vec3> genCirclePoints(int pointsNum, float radius, float y);
};

#endif