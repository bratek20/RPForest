#include "TriangleLightSampler.h"
#include "Random.h"
#include <iostream>

using namespace std;

TriangleLightSampler::TriangleLightSampler(const vector<TrianglePtr>& triangles){
    for(auto& tri : triangles){
        if(tri->mat.isLightSource()){
            lightSources.push_back(tri);
            thresholds.push_back(tri->calcArea() * tri->mat.emissive.length());
        }
    }
    for(unsigned i = 1; i < thresholds.size(); i++){
        thresholds[i] += thresholds[i-1];
    }
    cout << "Found " << lightSources.size() << " light sources" << endl;
}

LightSampleData TriangleLightSampler::sample(){
    float randomValue = Random::uniform(0, thresholds.back());
    int idx = lower_bound(thresholds.begin(), thresholds.end(), randomValue) - thresholds.begin();
    auto source = lightSources[idx]; 
    
    LightSampleData ans;
    ans.point = Random::pointInTriangle(source);
    ans.normal = source->getNormal(ans.point);
    ans.material = source->mat;
    ans.probability = idx == 0 ? thresholds[0] : thresholds[idx] - thresholds[idx-1];
    ans.probability /= thresholds.back();
    ans.triangle = source;
    return ans;
}