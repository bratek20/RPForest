#include "PathTracer.h"
#include "Random.h"
#include "DebugActor.h"

#include <cstdio>

using namespace std;
using namespace glm;

bool PathTracer::drawLines = false;

PathTracer::CastData PathTracer::cast(Ray r, int k, AccStruct &accStruct, LightSampler& lightSampler) {
    if (k <= 0) {
        return CastData();
    }

    HitData hit = accStruct.cast(r);
    if (!hit.intersects()) {
        return CastData();
    }
    bool isBounced = Random::tossCoin(hit.triangle->mat.diffuse.getAverage());
    if(!isBounced){
        return CastData();
    }

    CastData ans;
    ans.hit = true;
    ans.emittance = hit.triangle->mat.emissive 
    + calcDirectLight(hit, accStruct, lightSampler) 
    + calcIndirectLight(hit, k, accStruct, lightSampler);
    return ans;
}

vec3 PathTracer::calcDirectLight(HitData& hit, AccStruct &accStruct, LightSampler& lightSampler){
    auto lightSample = lightSampler.sample();
    vec3 lightPoint = lightSample.point;
    TrianglePtr source = lightSample.source;
    vec3 rayDir = normalize(lightPoint - hit.pos);

    HitData visibleHit = accStruct.cast(Ray(hit.pos, rayDir, true));
    if(!visibleHit.intersects() || visibleHit.triangle != source){
        return vec3(0);
    }

    vec3 BRDF = hit.triangle->mat.diffuse / M_PI;

    float cosX = clamp(dot(rayDir, hit.triangle->getNormal(hit.baryPos)), 0.0f, 1.0f);
    float cosY = clamp(dot(-rayDir, source->getNormal(visibleHit.baryPos)), 0.0f, 1.0f);
    float dist = distance(lightPoint, hit.pos);
    float probability = lightSample.probability / source->calcArea();
    float G = cosX * cosY / (dist * dist);
    auto ans = source->mat.emissive * BRDF * G / probability;
    return ans;
}

vec3 PathTracer::calcIndirectLight(HitData& hit, int k, AccStruct &accStruct, LightSampler& lightSampler){
    vec3 hitNormal = hit.triangle->getNormal(hit.baryPos); 
    const Material& hitMat = hit.triangle->mat;
    vec3 newDir = Random::vectorOnHemisphereCos(hitNormal);
    Ray newR = Ray(hit.pos, newDir, true);

    CastData incoming = cast(newR, k-1, accStruct, lightSampler);
    HitData incomingHit = accStruct.cast(newR);
    bool hitLight = incomingHit.intersects() && incomingHit.triangle->mat.isLightSource(); 
    auto ans = hitLight ? vec3(0) : hitMat.diffuse.asVec3() * incoming.emittance;
    
    if(drawLines) {
        DebugActor::get()->drawLine(hit.pos, incomingHit.pos);
    }
    return ans;
}

