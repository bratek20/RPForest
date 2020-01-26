#ifndef SKY_LIGHT_SAMPLER_H
#define SKY_LIGHT_SAMPLER_H

#include "LightSampler.h"
#include "ASunSky.H"
#include "AccStruct.h"
#include "Model.h"

class SkyLightSampler : public LightSampler {
    float radius;
    ASunSky sunSky;
    ModelPtr sunModel;

    std::vector<TrianglePtr> lightSources;
    std::vector<float> thresholds;

public:
    SkyLightSampler(float radius);
    
    void initLightSources(ModelPtr sunModel);
    
    LightSampleData sample() override;
    glm::vec3 cast(Ray r);
    
    glm::vec3 getSunPos() const;

private:
    glm::vec3 calcColor(glm::vec3 skyPos);
    float calcTheta(glm::vec3 v);
    float calcPhi(glm::vec3 v);

    glm::vec3 toRGB(float luminance, float xChroma, float yChroma);
};

#endif