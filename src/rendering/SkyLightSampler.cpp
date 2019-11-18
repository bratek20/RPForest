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
    vec3 oc = r.origin;
    float a = dot(r.direction, r.direction);
    float b = 2.0 * dot(oc, r.direction);
    float c = dot(oc,oc) - radius*radius;
    float discriminant = b*b - 4*a*c;
    if(discriminant < 0){
        return vec3(0);
    }
    else{
        float t = (-b - sqrt(discriminant)) / (2.0*a);
        if(t < 0) {
            t = (-b + sqrt(discriminant)) / (2.0*a);          
        }
        vec3 pos = r.calcPoint(t);
        return helper.calcColor(pos);
    }
}


