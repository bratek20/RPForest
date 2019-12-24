#include "PlantMaterial.h"
#include "Random.h"

using namespace std;
using namespace glm;

vec3 PlantMaterial::calcDiffuse(vec3 pos) const {
    return vec3(0.9, 0.8, 0.7);
}
