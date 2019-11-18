#include "SkyLightHelper.h"
#include "Utils.h"

using namespace std;
using namespace glm;

DistributionParams::DistributionParams(Coeffs coeffs, float T) {
    a = coeffs[0].first * T + coeffs[0].second;
    b = coeffs[1].first * T + coeffs[1].second;
    c = coeffs[2].first * T + coeffs[2].second;
    d = coeffs[3].first * T + coeffs[3].second;
    e = coeffs[4].first * T + coeffs[4].second;
}

const DistributionParams::Coeffs SkyLightHelper::LUMINANCE_COEFFS = 
{{0.1787, -1.463},{-0.3554, 0.4275},{-0.0227, 5.3251},{0.1206, -2.5771},{-0.0670, 0.3703} };

const DistributionParams::Coeffs SkyLightHelper::X_CHROMA_COEFFS  = 
{{-0.0193, -0.2592},{-0.0665, 0.0008},{-0.0004, 0.2125},{-0.0641, -0.8989},{-0.0033, 0.0452} };

const DistributionParams::Coeffs SkyLightHelper::Y_CHROMA_COEFFS  = 
{{-0.0167, -0.2608},{-0.0950, 0.0092},{-0.0079, 0.2102},{-0.0441, -1.6537},{-0.0109, 0.0529} };

const mat4x3 SkyLightHelper::X_CHROMA_ZENITH_MAT = 
{0.00166, -0.02903, 0.11693, -0.00375, 0.06377, -0.21196, 0.00209, -0.03202, 0.065052, 0, 0.00394, 0.25886};
const mat4x3 SkyLightHelper::Y_CHROMA_ZENITH_MAT =
{0.00275, -0.04214, 0.15346, -0.00610, 0.08970, -0.26756, 0.00317, -0.04153, 0.06670, 0, 0.00516, 0.26688};

SkyLightHelper::SkyLightHelper(float turbidity, vec3 sunPos) :
    T(turbidity),
    SUN_POS(sunPos),
    SUN_THETA(calcTheta(sunPos)),

    LUMINANCE_PARAMS(LUMINANCE_COEFFS, turbidity),
    X_CHROMA_PARAMS(X_CHROMA_COEFFS, turbidity),
    Y_CHROMA_PARAMS(Y_CHROMA_COEFFS, turbidity),
    
    LUMINANCE_ZENITH(calcLuminanceZenith()),
    X_CHROMA_ZENITH(calcChromaZenith(X_CHROMA_ZENITH_MAT)),
    Y_CHROMA_ZENITH(calcChromaZenith(Y_CHROMA_ZENITH_MAT)) {
}

vec3 SkyLightHelper::calcColor(vec3 skyPos) {
    float theta = calcTheta(skyPos);
    float gamma = calcGamma(skyPos);

    float luminance = LUMINANCE_ZENITH * calcDistribution(LUMINANCE_PARAMS, theta, gamma) / calcDistribution(LUMINANCE_PARAMS, 0, SUN_THETA);
    float xChroma = X_CHROMA_ZENITH * calcDistribution(X_CHROMA_PARAMS, theta, gamma) / calcDistribution(X_CHROMA_PARAMS, 0, SUN_THETA);
    float yChroma = Y_CHROMA_ZENITH * calcDistribution(Y_CHROMA_PARAMS, theta, gamma) / calcDistribution(Y_CHROMA_PARAMS, 0, SUN_THETA);

    return toRGB(luminance, xChroma, yChroma);
}

vec3 SkyLightHelper::toRGB(float luminance, float xChroma, float yChroma) {
    float Y = luminance;
    float X = xChroma * Y / yChroma;
    float Z = (1 - xChroma - yChroma) * Y / yChroma;

    float R =  3.2404542*X - 1.5371385*Y - 0.4985314*Z;
    float G = -0.9692660*X + 1.8760108*Y + 0.0415560*Z;
    float B =  0.0556434*X - 0.2040259*Y + 1.0572252*Z;

    static auto adj = [](float C){
        if (abs(C) < 0.0031308) {
            return 12.92 * C;
        }
        return 1.055 * pow(C, 0.41666) - 0.055;
    };

    return vec3(adj(R), adj(G), adj(B));
}

float SkyLightHelper::calcDistribution(DistributionParams params, float theta, float gamma) {
    float A = params.a;
    float B = params.b;
    float C = params.c;
    float D = params.d;
    float E = params.e;

    return (1 + A*exp(B / cos(theta))) * (1 + C*exp(D*gamma) + E * pow(cos(gamma), 2)); 
}

float SkyLightHelper::calcLuminanceZenith() {
    float chi = (4.0f/9 - T / 120) * (Utils::PI - 2 * SUN_THETA);
    float value = (4.0453 * T - 4.9710) * tan(chi) - 0.2155 * T + 2.4192;
    return abs(value);
}

float SkyLightHelper::calcChromaZenith(mat4x3 mat) {
    vec3 TVec = vec3(pow(T, 2), pow(T, 1), 1);
    vec4 sunThetaVec = vec4(pow(SUN_THETA, 3), pow(SUN_THETA, 2), pow(SUN_THETA, 1), 1); 
    return dot(TVec * mat, sunThetaVec);
}

float SkyLightHelper::calcTheta(vec3 v) {
    return acos(normalize(v).y);
}

float SkyLightHelper::calcGamma(vec3 skyPos) {
    return asin(length(cross(normalize(skyPos), normalize(SUN_POS))));
}