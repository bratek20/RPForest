#include "GroundMaterial.h"
#include "Random.h"

using namespace std;
using namespace glm;

vec3 GroundMaterial::calcDiffuse(vec3 pos) const {
    return vec3(0, 0.9, 0);//  + vec3(0.88, 0.66, 0.37); Random::noise(pos) * 0.1f + 
}
