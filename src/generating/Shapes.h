#ifndef SHAPES_H
#define SHAPES_H

#include "Mesh.h"
#include "Material.h"

class Shapes {
    static int CONE_BASE_POINTS_NUM;

public:
    static void setConeBasePointsNum(int num);
    static int getConeBasePointsNum();

    static MeshPtr genCone(float downRadius, float upRadius, float height, const Material& mat);
    static MeshPtr genPlane(float width, float depth);
    static MeshPtr genCircle(int pointsNum, float radius);

private:
    static std::vector<glm::vec3> genCirclePoints(int pointsNum, float radius, float y);
    static std::vector<unsigned int> genCircleIndices(int pointsNum);
};

#endif