#include "SkyLightSampler.h"
#include "Random.h"
#include "Utils.h"

using namespace std;

SkyLightSampler::SkyLightSampler(float radius) : radius(radius) {
}

LightSampleData SkyLightSampler::sample() {
    float area = 2 * Utils::PI * radius * radius;
    
    LightSampleData ans;
    ans.point = Random::vectorOnHemisphereCos() * radius;
    ans.normal = glm::normalize(-ans.point);
    ans.probability = 1 /  area;
    ans.material = Material::DEFAULT_LIGHT;
    return ans;
}

glm::vec3 SkyLightSampler::cast(Ray r) {
    return Material::DEFAULT_LIGHT.diffuse;
}