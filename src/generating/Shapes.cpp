#include "Shapes.h"
#include "Utils.h"

using namespace std;
using namespace glm;

MeshPtr Shapes::genPlane(float width, float depth) {
    float hw = width /2;
    float hd = depth /2;

    vector<Vertex> vertices(4);
    vertices[0] = Vertex(vec3(-hw, 0, -hd), Utils::UP);
    vertices[1] = Vertex(vec3(hw, 0, -hd), Utils::UP);
    vertices[2] = Vertex(vec3(-hw, 0, hd), Utils::UP);
    vertices[3] = Vertex(vec3(hw, 0, hd), Utils::UP);

    vector<unsigned int> indices = {0,1,2, 3,2,1}; 
    return Mesh::New(vertices, indices);
}

MeshPtr Shapes::genCone(float downRadius, float upRadius, float height) {
    static const int POINTS_NUM = 8;
    auto down = genCirclePoints(POINTS_NUM, downRadius, 0);
    auto up = genCirclePoints(POINTS_NUM, upRadius, height);

    vec3 center = vec3(0, height/2, 0);
    vector<Vertex> vertices(POINTS_NUM * 2);
    for (int i = 0; i < POINTS_NUM; i++) {
        vertices[i] = Vertex(down[i], normalize(down[i] - center));
        vertices[i + POINTS_NUM] = Vertex(up[i], normalize(up[i] - center));
    }

    vector<unsigned int> indices;
    for(int i=1;i<POINTS_NUM-1;i++){
        indices.push_back(0);
        indices.push_back(i);
        indices.push_back(i + 1);

        indices.push_back(POINTS_NUM);
        indices.push_back(POINTS_NUM + i);
        indices.push_back(POINTS_NUM + i + 1);
    }

    static auto next = [](int i){return (i + 1)%POINTS_NUM;};
    for(int i=0;i<POINTS_NUM;i++){
        indices.push_back(i);
        indices.push_back(next(i));
        indices.push_back(POINTS_NUM + next(i));

        indices.push_back(i);
        indices.push_back(POINTS_NUM + next(i));
        indices.push_back(POINTS_NUM + i);
    }
    Material mat = Material(Color(0.5f, 0.25f, 0.0f),
                                         Color(0.5f, 0.25f, 0.0f),
                                         Color(0.0f, 0.0f, 0.0f),
                                         glm::vec3(0, 0, 0),
                                         10);
    return Mesh::New(vertices, indices, mat);
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