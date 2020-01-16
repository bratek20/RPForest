#ifndef LIGHT_SAMPLER_H
#define LIGHT_SAMPLER_H

#include "Triangle.h"

struct LightSampleData {
    glm::vec3 point;
    glm::vec3 normal;
    glm::vec3 color;
    float probability;

    TrianglePtr triangle = nullptr;
};

class LightSampler {
public:    
    virtual ~LightSampler(){}

    virtual LightSampleData sample() = 0;
};

#endif