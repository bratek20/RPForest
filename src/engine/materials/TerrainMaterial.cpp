#include "TerrainMaterial.h"
#include "Random.h"
#include "Utils.h"

using namespace std;
using namespace glm;

vec3 TerrainMaterial::calcDiffuse(vec3 pos) const {
    float rockStartY = 25;
    float grassEndY = 50;
    
    if(pos.y > grassEndY) {
        return calcRockColor(pos);
    }
    if(pos.y >= rockStartY) {
        float grassFactor = (grassEndY - pos.y) / (grassEndY - rockStartY);
        return mix(calcRockColor(pos), calcGrassColor(pos), grassFactor);
    }
    return calcGrassColor(pos); 
}

vec3 TerrainMaterial::calcGrassColor(vec3 pos) const {
    vec3 grassColor = Utils::toColor(76,154,0);
    vec3 dirtColor = Utils::toColor(155, 118, 83);
    return mix(grassColor, dirtColor, Random::noise(pos * 0.1f));
}

vec3 TerrainMaterial::calcRockColor(vec3 pos) const {
    vec3 lighterRockColor = Utils::toColor(129, 125, 120);
    vec3 darkerRockColor = Utils::toColor(45,39,33);
    return mix(lighterRockColor, darkerRockColor, Random::noise(pos * 0.1f));
}
