#ifndef TURTLE_H
#define TURTLE_H

#include <glm/glm.hpp>
#include <string>

struct Turtle {
    glm::vec3 pos = glm::vec3(0);

    glm::vec3 front = glm::vec3(0, 0, -1);
    glm::vec3 left = glm::vec3(-1, 0, 0);
    glm::vec3 up = glm::vec3(0, 1, 0);

    glm::vec3 rotation = glm::vec3(0);

    float width = 1;

    void move(float length);

    void rotateFront(float angle);
    void rotateLeft(float angle);
    void rotateUp(float angle);
    void centerLeft();

    glm::mat4 getWorldMat() const;
    void debug(const std::string& label);

   private:
    glm::mat3 toMat() const;
    void apply(const glm::mat3& mat);
    glm::mat4 getRotationMat() const;
    glm::mat4 getPositionMat() const;
};

#endif