#ifndef TRIANGLE_LIGHT_SAMPLER_H
#define TRIANGLE_LIGHT_SAMPLER_H

#include "LightSampler.h"
#include "Mesh.h"
#include "Config.h"

class TriangleLightSampler : public LightSampler{
    std::vector<TrianglePtr> lightSources;
    std::vector<float> thresholds;

public:
    TriangleLightSampler(const std::vector<TrianglePtr>& triangles);

    LightSampleData sample() override;
};

#endif