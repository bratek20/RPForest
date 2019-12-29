#ifndef RANDOM_H
#define RANDOM_H

#include <random>
#include <glm/glm.hpp>
#include <memory>

class Triangle;
using TrianglePtr = const Triangle*;

class Random {
    static std::default_random_engine generator;

public:
    static void init();

    static int range(int b, int e);
    static float uniform(float a = 0.0f, float b = 1.0f);
    static bool tossCoin(float winProbability);
    
    static glm::vec3 vectorOnHemisphereUniform(glm::vec3 normal = glm::vec3(0, 1, 0));
    static glm::vec3 vectorOnHemisphereCos(glm::vec3 normal = glm::vec3(0, 1, 0));
    static glm::vec3 pointInTriangle(TrianglePtr triangle);
    
    static float noise(glm::vec3 v);

    template<typename T>
    static T randomElement(const std::vector<T>& v) {
        return v[range(0, v.size())];
    }
};
#endif