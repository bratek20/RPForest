#include "LeafMaterial.h"
#include "Utils.h"
#include "Assets.h"

using namespace glm;

vec3 LeafMaterial::calcDiffuse(vec3 pos) const {
    return Utils::mixColors(Assets::LEAF_MATERIAL_CONFIG, pos);
}
