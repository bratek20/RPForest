#include "Turtle.h"
#include "Utils.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/common.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/vector_angle.hpp> 
#include <iostream>
#include "DebugActor.h"

using namespace std;
using namespace glm;

const float Turtle::RADIUS_NOT_SET = 0;

void Turtle::move(float dist) {
    pos += getFront() * dist;
}

void Turtle::rotateFront(float angle) {
    angle = radians(angle);
    auto rot = mat3x3({
        cos(angle), 0, -sin(angle),
        0, 1, 0,
        sin(angle), 0, cos(angle)});
    apply(rot * toMat());
}

void Turtle::rotateUp(float angle) {
    angle = radians(angle);
    auto rot = mat3x3({
        cos(angle), sin(angle), 0,
        -sin(angle), cos(angle), 0,
        0, 0, 1});
    apply(rot * toMat());
}

void Turtle::rotateLeft(float angle) {
    angle = radians(angle);
    auto rot = mat3x3({
        1, 0, 0,
        0, cos(angle), -sin(angle),
        0, sin(angle), cos(angle)});
    apply(rot * toMat());
}

void Turtle::centerLeft() {
    static vec3 OPPOSITE_GRAVITY(0, 1, 0);
    left = normalize(cross(OPPOSITE_GRAVITY, front));
    up = cross(front, left);
}

void Turtle::bend(vec3 T, float e) {
    float alpha = e * length(cross(getFront(), T));
    rotateLeft(degrees(alpha));
}

glm::vec3 Turtle::getFront() const {
    return front;
}

mat3 Turtle::toMat() const {
    return mat3(
        {left.x, front.x, up.x, left.y, front.y, up.y, left.z, front.z, up.z});
}

void Turtle::apply(const mat3& mat) {
    left = vec3(mat[0][0], mat[1][0], mat[2][0]);
    front = vec3(mat[0][1], mat[1][1], mat[2][1]);
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

void Turtle::debug() {
    DebugActor::get()->getModel()->clearMeshes();
    DebugActor::get()->drawLine(pos, pos + front);
    DebugActor::get()->drawLine(pos, pos + left);
    DebugActor::get()->drawLine(pos, pos + up);
}

mat4 Turtle::getWorldMat() const {
    return getPositionMat() * getRotationMat();
}

mat4 Turtle::getPositionMat() const {
    return translate(mat4(1.0f), pos);
}

mat4 Turtle::getRotationMat() const {
    glm::vec3 right;
    glm::vec3 globalNormal = front; // TODO_BR move to utils and use it in random as well
    if(abs(globalNormal.x) < abs(globalNormal.y)){
        right = glm::vec3(1, 0, 0);
    }
    else{
        right = glm::vec3(0, 1, 0);
    }

    glm::vec3 globalZ = glm::normalize(glm::cross(globalNormal, right));
    glm::vec3 globalX = glm::normalize(glm::cross(globalZ, globalNormal));
    return mat4(globalX.x, globalX.y, globalX.z, 0, 
                globalNormal.x, globalNormal.y, globalNormal.z, 0,
                globalZ.x, globalZ.y, globalZ.z, 0,
                0, 0, 0, 1);
}
