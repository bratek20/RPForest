#include "Materials.h"
#include "Assets.h"

using namespace std;
using namespace glm;

unordered_map<std::string, const Material*> Materials::materials;

const ClassicMaterial Materials::DEFAULT =
    ClassicMaterial("Default",
                    vec3(0.8f, 0.8f, 0.8f),
                    vec3(0.9f, 0.9f, 0.9f),
                    vec3(0.0f, 0.0f, 0.0f),
                    vec3(0, 0, 0));

const ClassicMaterial Materials::DEBUG = ClassicMaterial("Debug",
                                                         vec3(1.0f, 0.0f, 0.0f),
                                                         vec3(1.0f, 0.0f, 0.0f),
                                                         vec3(0.0f, 0.0f, 0.0f),
                                                         vec3(0, 0, 0));

const LeafMaterial Materials::LEAF;
const BarkMaterial Materials::BARK;
const TerrainMaterial Materials::TERRAIN;
const PlantMaterial Materials::PLANT;

ClassicMaterial Materials::SUN;

void Materials::init() {
    SUN = ClassicMaterial(
        "Sun", Assets::SKY_CONFIG.sunColor, Assets::SKY_CONFIG.sunColor,
        vec3(0.0f, 0.0f, 0.0f),
        Assets::SKY_CONFIG.sunColor * Assets::SKY_CONFIG.sunPower);

    add(DEFAULT);
    add(DEBUG);
    add(LEAF);
    add(BARK);
    add(TERRAIN);
    add(PLANT);
    add(SUN);
}

const Material& Materials::get(const std::string& name) {
    auto it = materials.find(name);
    return it != materials.end() ? *it->second : DEFAULT;
}

void Materials::add(const Material& mat) {
    materials[mat.getName()] = &mat;
}