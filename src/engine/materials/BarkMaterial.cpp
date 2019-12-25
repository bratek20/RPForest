#include "BarkMaterial.h"
#include "Random.h"

using namespace std;
using namespace glm;

vec3 BarkMaterial::calcDiffuse(vec3 pos) const {
    //return vec3(0.59, 0.29, 0);
    return vec3(1, 1, 1);
}
