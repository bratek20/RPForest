#include "Materials.h"

using namespace std;
using namespace glm;

const ClassicMaterial Materials::DEFAULT = ClassicMaterial(vec3(0.8f, 0.8f, 0.8f),
                                         vec3(0.1f, 0.8f, 0.2f),
                                         vec3(0.0f, 0.0f, 0.0f),
                                         vec3(0, 0, 0));

const ClassicMaterial Materials::DEFAULT_LIGHT = ClassicMaterial(vec3(0.0f, 0.0f, 0.0f),
                                         vec3(1.0f, 1.0f, 1.0f),
                                         vec3(0.0f, 0.0f, 0.0f),
                                         vec3(17, 12, 4));

const ClassicMaterial Materials::NORMAL = ClassicMaterial(vec3(1.0f, 0.0f, 0.0f),
                                         vec3(1.0f, 0.0f, 0.0f),
                                         vec3(0.0f, 0.0f, 0.0f),
                                         vec3(17, 12, 4));

const ClassicMaterial Materials::DEBUG = ClassicMaterial(vec3(1.0f, 0.0f, 0.0f),
                                         vec3(1.0f, 0.0f, 0.0f),
                                         vec3(0.0f, 0.0f, 0.0f),
                                         vec3(17, 12, 4));

const LeafMaterial Materials::LEAF;
const BarkMaterial Materials::BARK;
const GroundMaterial Materials::GROUND;
const PlantMaterial Materials::PLANT;