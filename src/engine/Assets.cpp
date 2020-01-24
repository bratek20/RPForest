#include "Assets.h"
#include "Light.h"
#include "Globals.h"
#include "LSysGenerator.h"
#include "Honda.h"
#include "Family.h"
#include "ShaderCodes.h"

#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <fstream>
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;

using namespace std;

string Assets::CONFIG_PATH;

Program3D Assets::PROGRAM_3D;
SkyConfig Assets::SKY_CONFIG;
TerrainConfig Assets::TERRAIN_CONFIG;
CameraConfig Assets::CAMERA_CONFIG;
PathTracerConfig Assets::PATH_TRACER_CONFIG;
DebugConfig Assets::DEBUG_CONFIG;
vector<SpawnerConfig> Assets::SPAWNER_CONFIGS;

vector<GeneratorPtr> Assets::PLANT_GENERATORS;
vector<GeneratorPtr> Assets::TREE_GENERATORS;
vector<GeneratorPtr> Assets::LEAF_GENERATORS;

MaterialConfig Assets::GROUND_MATERIAL_CONFIG;
MaterialConfig Assets::ROCK_MATERIAL_CONFIG;
MaterialConfig Assets::PLANT_MATERIAL_CONFIG;
MaterialConfig Assets::LEAF_MATERIAL_CONFIG;
MaterialConfig Assets::BARK_MATERIAL_CONFIG;

void Assets::init(const std::string& configPath){
    CONFIG_PATH = configPath;
    if(CONFIG_PATH.back() == '/' || CONFIG_PATH.back() == '\\'){
        CONFIG_PATH.pop_back();
    }

    loadConfig("", "sky.conf", SKY_CONFIG);
    loadConfig("", "terrain.conf", TERRAIN_CONFIG);
    loadConfig("", "camera.conf", CAMERA_CONFIG);
    loadConfig("", "pathTracer.conf", PATH_TRACER_CONFIG);
    loadConfig("", "debug.conf", DEBUG_CONFIG);
    
    SPAWNER_CONFIGS = loadConfigs<SpawnerConfig>("spawners", ".spawner");

    PLANT_GENERATORS = loadGenerators<LSysGenerator, LSysConfig>("plants", ".lsys");
    
    TREE_GENERATORS = Utils::merge<GeneratorPtr>(
        loadGenerators<LSysGenerator, LSysConfig>("trees", ".lsys"),
        loadGenerators<Honda, HondaConfig>("trees", ".honda"));

    LEAF_GENERATORS = loadGenerators<Family, FamilyConfig>("leafs", ".family");

    loadConfig("materials", "ground.mat", GROUND_MATERIAL_CONFIG);
    loadConfig("materials", "rock.mat", ROCK_MATERIAL_CONFIG);
    loadConfig("materials", "plant.mat", PLANT_MATERIAL_CONFIG);
    loadConfig("materials", "leaf.mat", LEAF_MATERIAL_CONFIG);
    loadConfig("materials", "bark.mat", BARK_MATERIAL_CONFIG);    
}

void Assets::loadProgram3D() {
    if(DEBUG_CONFIG.enabled) {
        PROGRAM_3D = Program3D(ShaderCodes::VS_3D, ShaderCodes::FS_3D);
    }
}

bool Assets::loadConfig(const std::string& path, ConfigParser& config) {
    cout << "Loading config at path: " << path << endl;
    if(!config.load(path)){
        cerr << "Config failed to load!!!" << endl;
        return false;
    }
    return true;
}

bool Assets::loadConfig(const std::string& folder, const std::string& name, ConfigParser& config) {
    string insidePath = folder == "" ? name : folder + "/" + name; 
    return loadConfig(CONFIG_PATH + "/" + insidePath, config);
}

void Assets::clear(){
}

string Assets::photoSavePath(const string& name){
    return CONFIG_PATH + "/photos/" + name + ".exr";
}

bool Assets::isValidPath(const string& path){
    ifstream f(path.c_str());
    return f.good();
}

const std::vector<GeneratorPtr>& Assets::getGenerators(const std::string& generatorType) {
    if(generatorType == "Plant") {
        return PLANT_GENERATORS;
    }
    if(generatorType == "Tree") {
        return TREE_GENERATORS;
    }

    cerr << "No generators found for type: " << generatorType << endl;
    static vector<GeneratorPtr> EMPTY;
    return EMPTY;
}
vector<string> Assets::getAllPaths(const string& folder, const string& extension) {
    string fullFolderPath = CONFIG_PATH + "/" + folder;

    vector<string> paths;
    for (const auto & entry : fs::directory_iterator(fullFolderPath)) {
        if(entry.path().extension() == extension) {
            paths.push_back(entry.path());
        }
    }
    return paths;
}

