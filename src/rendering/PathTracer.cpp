#include "PathTracer.h"
#include "Random.h"
#include "DebugActor.h"

#include <cstdio>

using namespace std;
using namespace glm;

bool PathTracer::drawLines = false;

PathTracer::CastData PathTracer::cast(Ray r, int k, AccStruct &accStruct, SkyLightSampler& lightSampler) {
    if (k <= 0) {
        return CastData();
    }

    HitData hit = accStruct.cast(r);    
    if (!hit.intersects()) {
        CastData skyCast;
        skyCast.hit = true;
        skyCast.emittance = lightSampler.cast(r);
        return skyCast;
    }
    
    bool isBounced = Random::tossCoin(Utils::average(hit.triangle->mat.calcDiffuse(hit.pos)));
    if(!isBounced){
        return CastData();
    }
    
    CastData ans;
    ans.hit = true;
    ans.emittance = hit.triangle->mat.calcEmissive(hit.pos) 
    + calcDirectLight(hit, accStruct, lightSampler) 
    + calcIndirectLight(hit, k, accStruct, lightSampler);
    return ans;
}

vec3 PathTracer::calcDirectLight(HitData& hit, AccStruct &accStruct, SkyLightSampler& lightSampler){
    auto lightSample = lightSampler.sample();
    vec3 lightPoint = lightSample.point;
    vec3 rayDir = normalize(lightPoint - hit.pos);

    HitData visibleHit = accStruct.cast(Ray(hit.pos, rayDir, true));
    if(visibleHit.intersects() && lightSample.triangle != nullptr && *visibleHit.triangle != *lightSample.triangle) {
        return vec3(0);
    }

    vec3 BRDF = hit.triangle->mat.calcDiffuse(hit.pos) / Utils::PI;

    float cosX = calcCos(rayDir, hit.triangle->getNormal(hit.baryPos), true);
    float cosY = calcCos(-rayDir, lightSample.normal, true);
    float dist = distance(lightPoint, hit.pos);
    float probability = lightSample.probability;
    float G = cosX * cosY / (dist * dist);
    auto ans = lightSample.color * BRDF * G / probability;
    return ans;
}

vec3 PathTracer::calcIndirectLight(HitData& hit, int k, AccStruct &accStruct, SkyLightSampler& lightSampler){
    vec3 hitNormal = hit.triangle->getNormal(hit.baryPos); 
    const Material& hitMat = hit.triangle->mat;
    vec3 newDir = Random::vectorOnHemisphereCos(hitNormal);
    Ray newR = Ray(hit.pos, newDir, true);

    CastData incoming = cast(newR, k-1, accStruct, lightSampler);
    HitData incomingHit = accStruct.cast(newR);
    bool hitLight = incomingHit.intersects() && incomingHit.triangle->mat.isLightSource(); 
    auto ans = hitLight ? vec3(0) : hitMat.calcDiffuse(hit.pos) * incoming.emittance;
    
    if(drawLines) {
        DebugActor::get()->drawLine(hit.pos, incomingHit.pos);
        drawLines = false;
    }
    
    return ans;
}

float PathTracer::calcCos(glm::vec3 dir, glm::vec3 normal, bool doubleSided) {
    float ans = dot(dir, normal);
     if ((ans < 0 || ans > 1) && doubleSided){
        return dot(dir, -normal);
    }
    return glm::clamp(ans, 0.0f, 1.0f);
}

