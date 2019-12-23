#include "Assets.h"
#include "Light.h"

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

Program3D Assets::program;

void Assets::init(){
    program = Program3D("../src/engine/Program3D.vs", "../src/engine/Program3D.fs");
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

