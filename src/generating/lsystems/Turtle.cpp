#include "Turtle.h"

void Turtle::move(float dist) {
    pos += front * dist;    
}

void Turtle::rotateFront(float angle) {
    auto rot = glm::mat3x3({
        cos(angle), sin(angle), 0, 
        -sin(angle), cos(angle), 0, 
        0, 0, 1});
    apply(toMat() * rot);
}

void Turtle::rotateLeft(float angle) {
    auto rot = glm::mat3x3({
        cos(angle), 0, -sin(angle),
        0, 1, 0,
        sin(angle), 0, cos(angle)});
    apply(toMat() * rot);
}

void Turtle::rotateUp(float angle) {
    auto rot = glm::mat3x3({
        1, 0, 0,
        0, cos(angle), -sin(angle), 
        0, sin(angle), cos(angle)});
    apply(toMat() * rot);
}

void Turtle::centerLeft() {
    static glm::vec3 OPPOSITE_GRAVITY(0, 1, 0); 
    left = glm::normalize(glm::cross(OPPOSITE_GRAVITY, front));
    up = glm::cross(front, left);
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