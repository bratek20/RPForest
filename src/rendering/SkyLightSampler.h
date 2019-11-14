#ifndef SKY_LIGHT_SAMPLER_H
#define SKY_LIGHT_SAMPLER_H

#include "LightSampler.h"
#include "Material.h"
#include "AccStruct.h"

class SkyLightSampler : public LightSampler {
public:
    SkyLightSampler() = default;
    SkyLightSampler(float radius);

    LightSampleData sample() override;
    glm::vec3 cast(Ray r);

private:
    float radius;
};

#endif