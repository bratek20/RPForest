#ifndef SKY_LIGHT_SAMPLER_H
#define SKY_LIGHT_SAMPLER_H

#include "LightSampler.h"
#include "ASunSky.H"
#include "AccStruct.h"

class SkyLightSampler : public LightSampler {
public:
    SkyLightSampler(float radius);

    LightSampleData sample() override;
    glm::vec3 cast(Ray r);

private:
    glm::vec3 calcColor(glm::vec3 skyPos);
    float calcTheta(glm::vec3 v);
    float calcPhi(glm::vec3 v);

    glm::vec3 toRGB(float luminance, float xChroma, float yChroma);

    float radius;
    ASunSky sunSky;
};

#endif