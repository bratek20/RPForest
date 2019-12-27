#include "Assets.h"
#include "Light.h"
#include "Globals.h"

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

void Assets::init(){
    if(Globals::debug) {
        PROGRAM_3D = Program3D("../src/engine/Program3D.vs", "../src/engine/Program3D.fs");
    }
    
    string configsPath = ASSETS_PREFIX_PATH + "configs/";
    loadConfig(configsPath + "sky.conf", SKY_CONFIG);
    loadConfig(configsPath + "terrain.conf", TERRAIN_CONFIG);
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

vector<LSysConfig> Assets::loadLSysConfigs(const string& folderName) {
    vector<LSysConfig> configs;
    for(auto path : getAllPaths(folderName, ".lsys")){
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

vector<string> Assets::getAllPaths(const string& folderName, const string& extension) {
    string fullFolderPath = ASSETS_PREFIX_PATH + folderName;

    vector<string> paths;
    for (const auto & entry : fs::directory_iterator(fullFolderPath)) {
        if(entry.path().extension() == extension) {
            paths.push_back(entry.path());
        }
    }
    return paths;
}

