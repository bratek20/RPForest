#include "Turtle.h"
#include "Utils.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtc/quaternion.hpp>
//#include <glm/common.hpp>
#include <glm/gtx/quaternion.hpp>

#include <iostream>

using namespace std;

void Turtle::move(float dist) {
    static const glm::vec4 FRONT = glm::vec4(0,1,0,0);
    pos += static_cast<glm::vec3>(getRotationMat() * FRONT) * dist;
}

void Turtle::rotateFront(float angle) {
    rotation.y += angle;
    // angle = glm::radians(-angle);
    // auto rot = glm::mat3x3({
    //     cos(angle), sin(angle), 0, 
    //     -sin(angle), cos(angle), 0, 
    //     0, 0, 1});
    // apply(toMat() * rot);
}

void Turtle::rotateUp(float angle) {
    rotation.z += angle;
    // angle = glm::radians(angle);
    // auto rot = glm::mat3x3({
    //     cos(angle), 0, -sin(angle),
    //     0, 1, 0,
    //     sin(angle), 0, cos(angle)});
    // apply(toMat() * rot);
}

void Turtle::rotateLeft(float angle) {
    rotation.x += angle;
    // angle = glm::radians(-angle);
    // auto rot = glm::mat3x3({
    //     1, 0, 0,
    //     0, cos(angle), -sin(angle), 
    //     0, sin(angle), cos(angle)});
    // apply(toMat() * rot);


}

void Turtle::centerLeft() {
    //static glm::vec3 OPPOSITE_GRAVITY(0, 1, 0); 
    //left = glm::normalize(glm::cross(OPPOSITE_GRAVITY, front));
    //up = glm::cross(front, left);
}

glm::mat3x3 Turtle::toMat() const {
    return glm::mat3x3({
         front.x, left.x, up.x,
         front.y, left.y, up.y,
         front.z, left.z, up.z
    });
}

void Turtle::apply(const glm::mat3x3& mat) {
    front = glm::vec3(mat[0][0], mat[1][0], mat[2][0]);
    left = glm::vec3(mat[0][1], mat[1][1], mat[2][1]);
    up = glm::vec3(mat[0][2], mat[1][2], mat[2][2]);
}

void Turtle::debug(const std::string& label) {
    cout << label << endl;
    cout << "front: " << front << endl;
    cout << "left: " << left << endl;
    cout << "up: " << up << endl;
}


glm::mat4 Turtle::getRotationMat() const{
    static const glm::vec3 xAxis = glm::vec3(1,0,0);
    static const glm::vec3 yAxis = glm::vec3(0,1,0);
    static const glm::vec3 zAxis = glm::vec3(0,0,1);

    glm::mat4 rotationMat(1.0f);
    glm::quat rotZ = glm::angleAxis(glm::radians(rotation.z), zAxis);
    glm::quat rotY = glm::angleAxis(glm::radians(rotation.y), yAxis);
    glm::quat rotX = glm::angleAxis(glm::radians(rotation.x), xAxis);
    
    rotationMat = glm::toMat4(rotZ * rotY * rotX);
    return rotationMat;
}