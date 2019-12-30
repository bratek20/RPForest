#ifndef UTILS_H
#define UTILS_H

#include "MaterialConfig.h"

#include <functional>
#include <glm/glm.hpp>
#include <vector>

std::ostream& operator<<(std::ostream& out, const glm::vec3& v);

class Utils {
public:
    enum Axis {
        X = 0,
        Y = 1,
        Z = 2
    };

    enum class CmpType {
        MIN,
        MAX
    };

    static const float PI;
    static const float INF;
    static const glm::vec3 VX;
    static const glm::vec3 VY;
    static const glm::vec3 VZ;
    static const std::array<Axis, 3> AXES;
    static Axis next(Axis axis, int step = 1);

    static float findBest(const std::vector<glm::vec3>& poses, Axis axis, CmpType cmpType); 

    static glm::vec2 toVec2(const glm::vec3& v, Axis toOmit);

    static glm::mat4 getScaleMat(float scale);

    static glm::mat4 getRotateGlobalMat(glm::vec3 globalY);
    static glm::vec3 rotateGlobal(glm::vec3 vec, glm::vec3 globalY);

    static glm::mat3 calcNormM(glm::mat4 posM);

    static float average(glm::vec3 v);
    static bool hasNaN(glm::vec3 v);
    
    static glm::vec3 mixColors(const MaterialConfig& config, glm::vec3 pos);
    static glm::vec3 mixColors(glm::vec3 color1, glm::vec3 color2, glm::vec3 pos, float noisePosFactor, float noiseValFactor);
    
    template<typename T>
    static std::vector<T> merge(const std::vector<T>& v1, const std::vector<T>& v2) {
        std::vector<T> ans = v1;
        ans.insert(ans.end(), v2.begin(), v2.end());
        return ans;
    }
};

#endif