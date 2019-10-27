#ifndef LIGHT_SAMPLER_H
#define LIGHT_SAMPLER_H

#include "Mesh.h"
#include "Config.h"

class LightSampler {
    std::vector<TrianglePtr> lightSources;
    std::vector<float> thresholds;

public:
    struct SampleData{
        glm::vec3 point;
        TrianglePtr source;
        float probability;
    };

    LightSampler() = default;
    LightSampler(const std::vector<TrianglePtr>& triangles);

    SampleData sample();
};

#endif