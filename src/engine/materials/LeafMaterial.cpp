#include "LeafMaterial.h"
#include "Random.h"

using namespace std;
using namespace glm;

vec3 LeafMaterial::calcDiffuse(vec3 pos) const {
    return vec3(0, Random::noise(pos), 0);
}
