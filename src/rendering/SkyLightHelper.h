#ifndef SKY_LIGHT_HELPER_H
#define SKY_LIGHT_HELPER_H

#include "LightSampler.h"
#include "Material.h"
#include "AccStruct.h"

#include <vector>

struct DistributionParams {
    using Coeffs = std::vector<std::pair<float, float>>;
    float a;
    float b;
    float c;
    float d;
    float e;

    DistributionParams(Coeffs coeffs, float turbidity);
};

class SkyLightHelper {
    static const DistributionParams::Coeffs LUMINANCE_COEFFS;
    static const DistributionParams::Coeffs X_CHROMA_COEFFS;
    static const DistributionParams::Coeffs Y_CHROMA_COEFFS;

    static const glm::mat4x3 X_CHROMA_ZENITH_MAT;
    static const glm::mat4x3 Y_CHROMA_ZENITH_MAT;

public:
    SkyLightHelper(float turbidity, glm::vec3 sunPos);

    const float T;
    const glm::vec3 SUN_POS;
    const float SUN_THETA;
    const DistributionParams LUMINANCE_PARAMS;
    const DistributionParams X_CHROMA_PARAMS;
    const DistributionParams Y_CHROMA_PARAMS;

    const float LUMINANCE_ZENITH;
    const float X_CHROMA_ZENITH;
    const float Y_CHROMA_ZENITH;

    glm::vec3 calcColor(glm::vec3 skyPos);

private:
    float calcLuminanceZenith();
    float calcChromaZenith(glm::mat4x3 mat);
    
    float calcTheta(glm::vec3 v);
    float calcGamma(glm::vec3 skyPos);

    glm::vec3 toRGB(float luminance, float xChroma, float yChroma);
    float calcDistribution(DistributionParams params, float theta, float gamma);
};

#endif