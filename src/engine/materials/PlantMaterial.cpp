#include "PlantMaterial.h"
#include "Utils.h"
#include "Assets.h"

using namespace glm;

vec3 PlantMaterial::calcDiffuse(vec3 pos) const {
    return Utils::mixColors(Assets::PLANT_MATERIAL_CONFIG, pos);
}
