#ifndef SHAPES_H
#define SHAPES_H

#include "Mesh.h"
#include "Material.h"

class Shapes {
    static int CONE_BASE_POINTS_NUM;
    static const Material* CONE_MATERIAL;
    
public:
    static void setConeBasePointsNum(int num);
    static void setConeMaterial(const Material& mat);
    static MeshPtr genCone(float downRadius, float upRadius, float height);
    static MeshPtr genPlane(float width, float depth);

private:
    static std::vector<glm::vec3> genCirclePoints(int pointsNum, float radius, float y);
};

#endif