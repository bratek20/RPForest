#include "Turtle.h"
#include "Utils.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/common.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

#include <iostream>

using namespace std;
using namespace glm;

const float Turtle::RADIUS_NOT_SET = 0;

void Turtle::move(float dist) {
    pos += getFront() * dist;
}

void Turtle::rotateFront(float angle) {
    rotation.y += angle;
    // angle = radians(-angle);
    // auto rot = mat3x3({
    //     cos(angle), sin(angle), 0,
    //     -sin(angle), cos(angle), 0,
    //     0, 0, 1});
    // apply(toMat() * rot);
}

void Turtle::rotateUp(float angle) {
    rotation.z += angle;
    // angle = radians(angle);
    // auto rot = mat3x3({
    //     cos(angle), 0, -sin(angle),
    //     0, 1, 0,
    //     sin(angle), 0, cos(angle)});
    // apply(toMat() * rot);
}

void Turtle::rotateLeft(float angle) {
    rotation.x += angle;
    // angle = radians(-angle);
    // auto rot = mat3x3({
    //     1, 0, 0,
    //     0, cos(angle), -sin(angle),
    //     0, sin(angle), cos(angle)});
    // apply(toMat() * rot);
}

void Turtle::centerLeft() {
    // static vec3 OPPOSITE_GRAVITY(0, 1, 0);
    // left = normalize(cross(OPPOSITE_GRAVITY, front));
    // up = cross(front, left);
    rotation.y = 0;
}

void Turtle::bend(vec3 T, float e) {
    float alpha = e * length(cross(getFront(), T));
    rotateLeft(degrees(alpha));
}

glm::vec3 Turtle::getFront() const {
    static const vec4 FRONT = vec4(0, 1, 0, 0);
    return static_cast<vec3>(getRotationMat() * FRONT);
}
mat3x3 Turtle::toMat() const {
    return mat3x3(
        {front.x, left.x, up.x, front.y, left.y, up.y, front.z, left.z, up.z});
}

void Turtle::apply(const mat3x3& mat) {
    front = vec3(mat[0][0], mat[1][0], mat[2][0]);
    left = vec3(mat[0][1], mat[1][1], mat[2][1]);
    up = vec3(mat[0][2], mat[1][2], mat[2][2]);
}

void Turtle::setRadius(float radius) {
    this->radius = radius;
}

float Turtle::getRadius(float defaultValue) const {
    if (radius == RADIUS_NOT_SET) {
        return defaultValue;
    }
    return radius;
}

void Turtle::debug(const std::string& label) {
    cout << label << endl;
    cout << "front: " << front << endl;
    cout << "left: " << left << endl;
    cout << "up: " << up << endl;
}

mat4 Turtle::getWorldMat() const {
    return getPositionMat() * getRotationMat();
}

mat4 Turtle::getPositionMat() const {
    return translate(mat4(1.0f), pos);
}

mat4 Turtle::getRotationMat() const {
    static const vec3 xAxis = vec3(1, 0, 0);
    static const vec3 yAxis = vec3(0, 1, 0);
    static const vec3 zAxis = vec3(0, 0, 1);

    mat4 rotationMat(1.0f);
    quat rotZ = angleAxis(radians(rotation.z), zAxis);
    quat rotY = angleAxis(radians(rotation.y), yAxis);
    quat rotX = angleAxis(radians(rotation.x), xAxis);

    rotationMat = toMat4(rotZ * rotY * rotX);
    return rotationMat;
}
