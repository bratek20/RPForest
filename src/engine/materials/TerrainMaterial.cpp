#include "TerrainMaterial.h"
#include "Assets.h"
#include "Utils.h"

using namespace glm;

vec3 TerrainMaterial::calcDiffuse(vec3 pos) const {
    float rockStartY = Assets::TERRAIN_CONFIG.rockStartY;
    float groundEndY = Assets::TERRAIN_CONFIG.groundEndY;
    
    if(pos.y > groundEndY) {
        return calcRockColor(pos);
    }
    if(pos.y >= rockStartY) {
        float grassFactor = (groundEndY - pos.y) / (groundEndY - rockStartY);
        return mix(calcRockColor(pos), calcGroundColor(pos), grassFactor);
    }
    return calcGroundColor(pos); 
}

vec3 TerrainMaterial::calcGroundColor(vec3 pos) const {
    return Utils::mixColors(Assets::GROUND_MATERIAL_CONFIG, pos);
}

vec3 TerrainMaterial::calcRockColor(vec3 pos) const {
    return Utils::mixColors(Assets::ROCK_MATERIAL_CONFIG, pos);
}
