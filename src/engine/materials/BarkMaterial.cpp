#include "BarkMaterial.h"
#include "Utils.h"
#include "Assets.h"

using namespace glm;

vec3 BarkMaterial::calcDiffuse(vec3 pos) const {
    return Utils::mixColors(Assets::BARK_MATERIAL_CONFIG, pos);
}
