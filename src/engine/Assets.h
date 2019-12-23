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

class Assets {
    static const std::string ASSETS_PREFIX_PATH;
    static const std::vector<std::string> POSSIBLE_PATH_PREFIXES;

public:
    static Program3D program;
    
    static void init(); 
    static void clear();
    static std::string validPath(const std::string& path);
    static std::string photoSavePath(const std::string& name);
    static std::vector<LSysConfig> loadLSysConfigs(const std::string& folderName);

private:
    static bool isValidPath(const std::string& path);
    static std::vector<std::string> getAllPaths(const std::string& folderName, const std::string& extension);
};

#endif