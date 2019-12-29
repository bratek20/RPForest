#include "Assets.h"
#include "Light.h"
#include "Globals.h"
#include "LSysGenerator.h"
#include "Honda.h"
#include "Family.h"

#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <fstream>
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;

using namespace std;

const string Assets::ASSETS_PREFIX_PATH = "../assets/";
const vector<string> Assets::POSSIBLE_PATH_PREFIXES = 
{
    "",
    ASSETS_PREFIX_PATH
};

Program3D Assets::PROGRAM_3D;
SkyConfig Assets::SKY_CONFIG;
TerrainConfig Assets::TERRAIN_CONFIG;
CameraConfig Assets::CAMERA_CONFIG;
vector<SpawnerConfig> Assets::SPAWNER_CONFIGS;

vector<GeneratorPtr> Assets::PLANT_GENERATORS;
vector<GeneratorPtr> Assets::TREE_GENERATORS;
vector<GeneratorPtr> Assets::LEAF_GENERATORS;

MaterialConfig Assets::GROUND_MATERIAL_CONFIG;
MaterialConfig Assets::ROCK_MATERIAL_CONFIG;
MaterialConfig Assets::PLANT_MATERIAL_CONFIG;
MaterialConfig Assets::LEAF_MATERIAL_CONFIG;
MaterialConfig Assets::BARK_MATERIAL_CONFIG;

void Assets::init(){
    if(Globals::debug) {
        PROGRAM_3D = Program3D("../src/engine/Program3D.vs", "../src/engine/Program3D.fs");
    }
    
    loadConfig("configs", "sky.conf", SKY_CONFIG);
    loadConfig("configs", "terrain.conf", TERRAIN_CONFIG);
    loadConfig("configs", "camera.conf", CAMERA_CONFIG);
 
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

bool Assets::loadConfig(const std::string& path, ConfigParser& config) {
    cout << "Loading config at path: " << path << endl;
    if(!config.load(path)){
        cerr << "Config failed to load!!!" << endl;
        return false;
    }
    return true;
}

bool Assets::loadConfig(const std::string& folder, const std::string& name, ConfigParser& config) {
    loadConfig(ASSETS_PREFIX_PATH + folder + "/" + name, config);
}

void Assets::clear(){
}

string Assets::validPath(const string& path){
    for(auto& prefix : POSSIBLE_PATH_PREFIXES){
        string fullPath = prefix + path;
        if(isValidPath(fullPath)){
            return fullPath;
        }
    }

    cerr << "No valid path for: " << path << endl;
    return path;
}

string Assets::photoSavePath(const string& name){
    return "../photos/" + name;
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
    string fullFolderPath = ASSETS_PREFIX_PATH + folder;

    vector<string> paths;
    for (const auto & entry : fs::directory_iterator(fullFolderPath)) {
        if(entry.path().extension() == extension) {
            paths.push_back(entry.path());
        }
    }
    return paths;
}

