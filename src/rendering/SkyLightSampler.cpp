#include "SkyLightSampler.h"
#include "Assets.h"
#include "Random.h"
#include "Utils.h"

using namespace std;
using namespace glm;

SkyLightSampler::SkyLightSampler(float radius)
    : radius(radius),
      sunSky(Assets::SKY_CONFIG.latitude,
             Assets::SKY_CONFIG.longitude,
             Assets::SKY_CONFIG.standardMeridian,
             Assets::SKY_CONFIG.julianDay,
             Assets::SKY_CONFIG.timeOfDay,
             Assets::SKY_CONFIG.turbidity) {}

void SkyLightSampler::initLightSources(ModelPtr sunModel) {
    this->sunModel = sunModel;
    lightSources = sunModel->getTriangles();

    thresholds.clear();
    for (auto& tri : lightSources) {
        thresholds.push_back(tri->calcArea() *
                             tri->mat.calcEmissive(tri->getCenter()).length());
    }
    for (unsigned i = 1; i < thresholds.size(); i++) {
        thresholds[i] += thresholds[i - 1];
    }
}

LightSampleData SkyLightSampler::sample() {
    float randVal = Random::uniform(0, thresholds.back());
    LightSampleData ans;
    int idx = lower_bound(thresholds.begin(), thresholds.end(), randVal) -
                thresholds.begin();
    auto source = lightSources[idx];

    ans.point = Random::pointInTriangle(source);
    ans.normal = source->getNormal(ans.point);
    ans.color = source->mat.calcEmissive(ans.point);
    ans.probability =
        idx == 0 ? thresholds[0] : thresholds[idx] - thresholds[idx - 1];
    ans.probability /= thresholds.back();
    ans.triangle = source;
    return ans;
}

glm::vec3 SkyLightSampler::cast(Ray r) {
    if (r.direction.y < 0) {
        r.direction.y = 0;
    }
    return calcColor(r.direction);
}

vec3 SkyLightSampler::getSunPos() const {
    vec3 pos = sunSky.GetSunPosition();
    swap(pos.y, pos.z);
    return pos * radius;
}

vec3 SkyLightSampler::calcColor(vec3 skyPos) {
    swap(skyPos.y, skyPos.z);
    vec3 radiance = sunSky.GetSkyxyYRadiance(skyPos);
    vec3 ans =
        toRGB(Assets::SKY_CONFIG.skyLuminanceFactor * radiance.z, radiance.x, radiance.y);

    if (Utils::hasNaN(ans)) {
        ans =
        toRGB(Assets::SKY_CONFIG.skyLuminanceFactor * radiance.z, radiance.x, radiance.y);
        return vec3(0);
    }
    return ans;
}

vec3 SkyLightSampler::toRGB(float luminance, float xChroma, float yChroma) {
    float Y = luminance;
    float X = xChroma * Y / yChroma;
    float Z = (1 - xChroma - yChroma) * Y / yChroma;

    float R = 3.2404542 * X - 1.5371385 * Y - 0.4985314 * Z;
    float G = -0.9692660 * X + 1.8760108 * Y + 0.0415560 * Z;
    float B = 0.0556434 * X - 0.2040259 * Y + 1.0572252 * Z;

    static auto adj = [](float C) {
        if (abs(C) < 0.0031308) {
            return 12.92 * C;
        }
        if(C < 0){
            return 0.0;
        }
        return 1.055 * pow(C, 0.41666) - 0.055;
    };

    return vec3(adj(R), adj(G), adj(B));
}
