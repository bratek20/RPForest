#ifndef SKY_LIGHT_SAMPLER_H
#define SKY_LIGHT_SAMPLER_H

#include "LightSampler.h"
#include "SkyLightHelper.h"

class SkyLightSampler : public LightSampler {
public:
    SkyLightSampler(float radius);

    LightSampleData sample() override;
    glm::vec3 cast(Ray r);

private:
    float radius;
    SkyLightHelper helper;
};

#endif