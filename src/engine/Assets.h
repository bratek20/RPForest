#ifndef ASSETS_H
#define ASSETS_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>
#include <vector>
#include <functional>

#include "Program3D.h"
#include "LSysConfig.h"
#include "SkyConfig.h"
#include "TerrainConfig.h"
#include "Generator.h"

class Assets {
    static const std::string ASSETS_PREFIX_PATH;
    static const std::vector<std::string> POSSIBLE_PATH_PREFIXES;

public:
    static Program3D PROGRAM_3D;
    static SkyConfig SKY_CONFIG;
    static TerrainConfig TERRAIN_CONFIG;

    static std::vector<GeneratorPtr> PLANT_GENERATORS;
    static std::vector<GeneratorPtr> TREE_GENERATORS;
    static std::vector<GeneratorPtr> LEAF_GENERATORS;

    static void init(); 
    static void clear();

    static std::string validPath(const std::string& path);
    static std::string photoSavePath(const std::string& name);

private:
    static void loadConfig(const std::string& path, ConfigParser& config);
    
    template<typename GeneratorType, typename ConfigType>
    static std::vector<GeneratorPtr> loadGenerators(const std::string& folder, const std::string& extension) {
        auto configs = loadGeneratorConfigs<ConfigType>(folder, extension);
        std::vector<GeneratorPtr> generators;
        for(auto& config : configs) {
            generators.push_back(GeneratorPtr(new GeneratorType(config)));
        }
        return generators;
    }

    template<typename T>
    static std::vector<GeneratorConfigPtr> loadGeneratorConfigs(const std::string& folder, const std::string& extension) {
        using namespace std;
        vector<GeneratorConfigPtr> configs;
        for(auto path : getAllPaths(folder, extension)){
            GeneratorConfigPtr config = GeneratorConfigPtr(new T());
            if(!config->load(path)){
                cerr << "Config at path " << path << " failed to load" << endl;
            }
            else{
                configs.push_back(config);
            }
        }
        return configs;
    }

    static bool isValidPath(const std::string& path);
    static std::vector<std::string> getAllPaths(const std::string& folder, const std::string& extension);
};

#endif