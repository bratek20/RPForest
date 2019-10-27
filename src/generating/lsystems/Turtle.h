#ifndef TURTLE_H
#define TURTLE_H

#include <glm/glm.hpp>

struct Turtle {
    glm::vec3 pos;

    glm::vec3 front;
    glm::vec3 left;
    glm::vec3 up;

    float width; 

    void move(float length);

    void rotateFront(float angle);
    void rotateLeft(float angle);
    void rotateUp(float angle);  
    void centerLeft();  

private:
    glm::mat3x3 toMat() const;
    void apply(const glm::mat3x3& mat);
};

#endif