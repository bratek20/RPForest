#include "BarkMaterial.h"
#include "Random.h"

using namespace std;
using namespace glm;

vec3 BarkMaterial::calcDiffuse(vec3 pos) const {
    return Random::noise(pos) * vec3(0.59, 0.29, 0);
}
