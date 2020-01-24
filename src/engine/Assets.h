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
#include "CameraConfig.h"
#include "SpawnerConfig.h"
#include "MaterialConfig.h"
#include "PathTracerConfig.h"
#include "ViewModeConfig.h"

class Assets {
    static std::string CONFIG_PATH;

public:
    static Program3D PROGRAM_3D;

    static SkyConfig SKY_CONFIG;
    static TerrainConfig TERRAIN_CONFIG;
    static CameraConfig CAMERA_CONFIG;
    static PathTracerConfig PATH_TRACER_CONFIG;
    static ViewModeConfig VIEW_MODE_CONFIG;
    static std::vector<SpawnerConfig> SPAWNER_CONFIGS;

    static std::vector<GeneratorPtr> PLANT_GENERATORS;
    static std::vector<GeneratorPtr> TREE_GENERATORS;
    static std::vector<GeneratorPtr> LEAF_GENERATORS;

    static MaterialConfig GROUND_MATERIAL_CONFIG;
    static MaterialConfig ROCK_MATERIAL_CONFIG;
    static MaterialConfig PLANT_MATERIAL_CONFIG;
    static MaterialConfig LEAF_MATERIAL_CONFIG;
    static MaterialConfig BARK_MATERIAL_CONFIG;
    
    static void init(const std::string& configPath);
    static void loadProgram3D();
    static void clear();

    static std::string photoSavePath(const std::string& name);

    static const std::vector<GeneratorPtr>& getGenerators(const std::string& generatorType);

private:
    static bool loadConfig(const std::string& path, ConfigParser& config);
    static bool loadConfig(const std::string& folder, const std::string& name, ConfigParser& config);

    template<typename T>
    static std::vector<T> loadConfigs(const std::string& folder, const std::string& extension) {
        using namespace std;
        vector<T> configs;
        for(auto path : getAllPaths(folder, extension)){
            T config;
            if(loadConfig(path, config)){
                configs.push_back(config);
            }
        }
        return configs;
    }

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
            if(loadConfig(path, *config)){
                configs.push_back(config);
            }
        }
        return configs;
    }

    static bool isValidPath(const std::string& path);
    static std::vector<std::string> getAllPaths(const std::string& folder, const std::string& extension);
};

#endif