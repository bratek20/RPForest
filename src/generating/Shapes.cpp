#include "Shapes.h"
#include "Utils.h"
#include "Material.h"

using namespace std;
using namespace glm;

int Shapes::CONE_BASE_POINTS_NUM = 3;

void Shapes::setConeBasePointsNum(int num) {
    CONE_BASE_POINTS_NUM = num;
}

int Shapes::getConeBasePointsNum() {
    return CONE_BASE_POINTS_NUM;
}

MeshPtr Shapes::genPlane(float width, float depth) {
    float hw = width /2;
    float hd = depth /2;

    vector<Vertex> vertices(3);
    vertices[0] = Vertex(vec3(-hw, 0, -hd), Utils::VY);
    vertices[1] = Vertex(vec3(hw, 0, -hd), Utils::VY);
    vertices[2] = Vertex(vec3(-hw, 0, hd), Utils::VY);
    vertices[3] = Vertex(vec3(hw, 0, hd), Utils::VY);

    vector<unsigned int> indices = {0,1,2, 3,2,1}; 
    return Mesh::New(vertices, indices, false, Materials::TERRAIN);
}

MeshPtr Shapes::genCone(float downRadius, float upRadius, float height, const Material& mat) {
    auto down = genCirclePoints(CONE_BASE_POINTS_NUM, downRadius, 0);
    auto up = genCirclePoints(CONE_BASE_POINTS_NUM, upRadius, height);

    vec3 center = vec3(0, height/2, 0);
    vector<Vertex> vertices(CONE_BASE_POINTS_NUM * 2);
    for (int i = 0; i < CONE_BASE_POINTS_NUM; i++) {
        vertices[i] = Vertex(down[i], normalize(vec3(down[i].x, 0, down[i].z)));
        vertices[i + CONE_BASE_POINTS_NUM] = Vertex(up[i], normalize(vec3(up[i].x, 0, up[i].z)));
    }

    vector<unsigned int> indices;
    // for(int i=1;i<CONE_BASE_POINTS_NUM-1;i++){
    //     indices.push_back(0);
    //     indices.push_back(i);
    //     indices.push_back(i + 1);

    //     indices.push_back(CONE_BASE_POINTS_NUM);
    //     indices.push_back(CONE_BASE_POINTS_NUM + i);
    //     indices.push_back(CONE_BASE_POINTS_NUM + i + 1);
    // }

    static auto next = [](int i){return (i + 1)%CONE_BASE_POINTS_NUM;};
    for(int i=0;i<CONE_BASE_POINTS_NUM;i++){
        indices.push_back(i);
        indices.push_back(next(i));
        indices.push_back(CONE_BASE_POINTS_NUM + next(i));

        indices.push_back(i);
        indices.push_back(CONE_BASE_POINTS_NUM + next(i));
        indices.push_back(CONE_BASE_POINTS_NUM + i);
    }
    return Mesh::New(vertices, indices, false, mat);
}

MeshPtr Shapes::genCircle(int pointsNum, float radius) {
    auto points = genCirclePoints(pointsNum, radius, 20);
    auto indices = genCircleIndices(pointsNum);
    vector<Vertex> vertices;
    for(vec3 point : points) {
        vertices.emplace_back(point, -Utils::VY);
    }
    return Mesh::New(vertices, indices, false, Materials::SUN);
}

vector<vec3> Shapes::genCirclePoints(int pointsNum, float radius, float y) {
    vector<vec3> points;
    for (int i = 0; i < pointsNum; i++) {
        float angle = 2 * Utils::PI * i / pointsNum;
        float x = radius * cos(angle);
        float z = radius * sin(angle);
        points.push_back(vec3(x, y, z));
    }
    return points;
}

vector<unsigned int> Shapes::genCircleIndices(int pointsNum) {
    vector<unsigned int> indices;
    for(int i=1;i<pointsNum-1;i++){
        indices.push_back(0);
        indices.push_back(i);
        indices.push_back(i + 1);
    }
    return indices;
}