

#ifndef BOUNDS_H
#define BOUNDS_H

#include <glm/glm.hpp>

#include "Utils.h"
#include "Material.h"

#include <vector>

struct Bounds {
    static const glm::vec3 MIN_NOT_SET;
    static const glm::vec3 MAX_NOT_SET;

    glm::vec3 pMin;
    glm::vec3 pMax;

    Bounds();
    Bounds(const std::vector<glm::vec3>& poses);
    Bounds(glm::vec3 pMin, glm::vec3 pMax) :
        pMin(pMin), pMax(pMax) {}

    Bounds merge(const Bounds& other) const;
    std::pair<Bounds, Bounds> split(Utils::Axis axis, float value) const;

    bool isValid() const;
    glm::vec3 diagonal() const;
    float surfaceArea() const;
    Utils::Axis maximumExtent() const;
};

#endif

