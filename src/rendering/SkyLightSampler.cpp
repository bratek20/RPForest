#include "SkyLightSampler.h"
#include "Random.h"
#include "Utils.h"

using namespace std;
using namespace glm;

SkyLightSampler::SkyLightSampler(float radius) : radius(radius), helper(1, vec3(0, radius, 0)) {
}

LightSampleData SkyLightSampler::sample() {
    float area = 2 * Utils::PI * radius * radius;
    
    LightSampleData ans;
    ans.point = Random::vectorOnHemisphereCos() * radius;
    ans.normal = glm::normalize(-ans.point);
    ans.probability = 1 /  area;
    ans.material = Material::DEFAULT_LIGHT;
    ans.material.emissive = ans.material.diffuse = helper.calcColor(ans.point);
    return ans;
}

glm::vec3 SkyLightSampler::cast(Ray r) {
    return Material::DEFAULT_LIGHT.diffuse;
}


