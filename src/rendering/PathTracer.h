#ifndef PATH_TRACER_H
#define PATH_TRACER_H

#include "Color.h"
#include "AccStruct.h"
#include "SkyLightSampler.h"

class PathTracer{
public:
    static bool drawLines;

    struct CastData {
        bool hit = false;
        glm::vec3 emittance = glm::vec3(0,0,0);
    };
    static CastData cast(Ray r, int k, AccStruct& accStruct, SkyLightSampler& lightSampler);

private:
    static glm::vec3 calcDirectLight(HitData& hit, AccStruct &accStruct, SkyLightSampler& lightSampler);
    static glm::vec3 calcIndirectLight(HitData& hit, int k, AccStruct &accStruct, SkyLightSampler& lightSampler);
};

#endif