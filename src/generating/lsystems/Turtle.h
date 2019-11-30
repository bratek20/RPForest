#ifndef TURTLE_H
#define TURTLE_H

#include <glm/glm.hpp>
#include <string>

class Turtle {
    static const float RADIUS_NOT_SET;

    glm::vec3 front = glm::vec3(0, 1, 0);
    glm::vec3 left = glm::vec3(-1, 0, 0);
    glm::vec3 up = glm::vec3(0, 0, 1);

    glm::vec3 pos = glm::vec3(0, 0, 0);
    float radius = RADIUS_NOT_SET;

   public:


    void move(float length);

    void rotateFront(float angle);
    void rotateLeft(float angle);
    void rotateUp(float angle);
    void centerLeft();
    void bend(glm::vec3 T, float e);

    glm::vec3 getPos() const;
    
    void setRadius(float radius);
    float getRadius(float defaultValue = 1) const;

    glm::mat4 getWorldMat() const;
    void debug();

   private:
    glm::vec3 getFront() const;
    glm::mat3 toMat() const;
    void apply(const glm::mat3& mat);
    glm::mat4 getRotationMat() const;
    glm::mat4 getPositionMat() const;
};

#endif