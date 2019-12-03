

#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Material.h"
#include "Vertex.h"
#include "Bounds.h"

struct Triangle {
    const Vertex& v1;
    const Vertex& v2;
    const Vertex& v3;
    const Material& mat;

    Triangle(Vertex& v1, Vertex& v2, Vertex& v3, const Material& mat);

    float calcArea() const;
    bool isInside(glm::vec3 point) const;

    glm::vec3 getEdge12() const;
    glm::vec3 getEdge13() const;
    glm::vec3 getNormal(glm::vec2 baryPos) const;
    glm::vec3 getNormal(glm::vec3 pos) const;
    glm::vec3 calcBaseNormal() const;
    std::vector<glm::vec3> getPositions() const;
    glm::vec3 getCenter() const;
};
using TrianglePtr = const Triangle*;

#endif

