#ifndef AVECTOR3_H
#define AVECTOR3_H

#include <glm/glm.hpp>

using AVector3 = glm::vec3;

struct AUnitVector3 : protected AVector3 {
    AUnitVector3(AVector3 v) : AVector3(glm::normalize(v)) {}
    AUnitVector3(float x, float y, float z) : AUnitVector3(AVector3(x, y, z)) {}

    float X() const {
        return x;
    }

    float Y() const {
        return y;
    }

    float Z() const {
        return z;
    }
};

#endif