#include "Materials.h"
#include "Assets.h"

using namespace std;
using namespace glm;

const ClassicMaterial Materials::DEFAULT =
    ClassicMaterial(vec3(0.8f, 0.8f, 0.8f),
                    vec3(0.1f, 0.8f, 0.2f),
                    vec3(0.0f, 0.0f, 0.0f),
                    vec3(0, 0, 0));

const ClassicMaterial Materials::NORMAL =
    ClassicMaterial(vec3(1.0f, 0.0f, 0.0f),
                    vec3(1.0f, 0.0f, 0.0f),
                    vec3(0.0f, 0.0f, 0.0f),
                    vec3(0, 0, 0));

const ClassicMaterial Materials::DEBUG = ClassicMaterial(vec3(1.0f, 0.0f, 0.0f),
                                                         vec3(1.0f, 0.0f, 0.0f),
                                                         vec3(0.0f, 0.0f, 0.0f),
                                                         vec3(0, 0, 0));

const LeafMaterial Materials::LEAF;
const BarkMaterial Materials::BARK;
const GroundMaterial Materials::GROUND;
const PlantMaterial Materials::PLANT;

ClassicMaterial Materials::SUN;

void Materials::init() {
    SUN = ClassicMaterial(Assets::SKY_CONFIG.sunColor, Assets::SKY_CONFIG.sunColor,
                          vec3(0.0f, 0.0f, 0.0f), Assets::SKY_CONFIG.sunColor * Assets::SKY_CONFIG.sunPower);
}