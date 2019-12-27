#include "Assets.h"
#include "Light.h"
#include "Globals.h"
#include "LSysGenerator.h"
#include "Honda.h"

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

vector<GeneratorPtr> Assets::PLANT_GENERATORS;
vector<GeneratorPtr> Assets::TREE_GENERATORS;

void Assets::init(){
    if(Globals::debug) {
        PROGRAM_3D = Program3D("../src/engine/Program3D.vs", "../src/engine/Program3D.fs");
    }
    
    string configsPath = ASSETS_PREFIX_PATH + "configs/";
    loadConfig(configsPath + "sky.conf", SKY_CONFIG);
    loadConfig(configsPath + "terrain.conf", TERRAIN_CONFIG);

    PLANT_GENERATORS = loadLSysGenerators("plants", Generator::LOW, Materials::PLANT);
    
    TREE_GENERATORS = loadLSysGenerators("trees", Generator::HIGH, Materials::BARK);
    TREE_GENERATORS.push_back(GeneratorPtr(new Honda()));
}

void Assets::loadConfig(const std::string& path, ConfigParser& config) {
    cout << "Loading config at path: " << path << endl;
    if(!config.load(path)){
        cerr << "Config failed to load!!!" << endl;
    }
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

vector<GeneratorPtr> Assets::loadLSysGenerators(const string& folder, Generator::LOD lod, const Material& mat) {
    auto lSysConfigs = Assets::loadLSysConfigs(folder);
    vector<GeneratorPtr> generators;
    for(auto& config : lSysConfigs) {
        generators.push_back(GeneratorPtr(new LSysGenerator(config, lod, mat)));
    }
    return generators;
}

vector<LSysConfig> Assets::loadLSysConfigs(const string& folder) {
    vector<LSysConfig> configs;
    for(auto path : getAllPaths(folder, ".lsys")){
        LSysConfig config;
        if(!config.load(path)){
            cerr << "Config at path " << path << " failed to load" << endl;
        }
        else{
            configs.push_back(config);
        }
    }
    return configs;
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

