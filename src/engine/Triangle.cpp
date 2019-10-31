

#include "Triangle.h"

using namespace std;

Triangle::Triangle(Vertex& v1, Vertex& v2, Vertex& v3)    
    : v1(v1), v2(v2), v3(v3) {
    static int nextId = 1;
    id = nextId++;
    auto poses = getPositions();
    bounds = Bounds(poses);
}

Triangle::Triangle(Vertex &v1, Vertex &v2, Vertex &v3, const Material &mat)
    : Triangle(v1, v2, v3) {
    this->mat = mat;
}

float Triangle::calcArea() const {
    return cross(getEdge12(), getEdge13()).length() / 2;
}

bool Triangle::isInside(glm::vec3 point) const{
    float area = calcArea();
    float alpha = cross(v2.position - point, v3.position - point).length() / (2 * area);
    float beta = cross(v3.position - point, v1.position - point).length() / (2 * area);
    float gamma = 1 - alpha - beta;
    
    static auto check = [](float value){
        return value >= 0 && value <= 1;
    };
    return check(alpha) && check(beta) && check(gamma); 
}

glm::vec3 Triangle::getEdge12() const{
    return v2.position - v1.position;
}

glm::vec3 Triangle::getEdge13() const{
    return v3.position - v1.position;
}

glm::vec3 Triangle::getNormal(glm::vec2 baryPos) const {
    if (v1.hasNormal() && v2.hasNormal() && v3.hasNormal()) {
        return (1 - baryPos.x - baryPos.y) * v1.normal + baryPos.x * v2.normal +
               baryPos.y * v3.normal;
    } else {
        return getNormal();
    }
}

glm::vec3 Triangle::getNormal() const {
    return glm::normalize(
        glm::cross(v2.position - v1.position, v3.position - v1.position));
}

vector<glm::vec3> Triangle::getPositions() const {
    return {v1.position, v2.position, v3.position};
}

Bounds Triangle::getBounds() const {
    return bounds;
}

glm::vec3 Triangle::getCenter() const {
    return (v1.position + v2.position + v3.position) / 3.0f;
}
