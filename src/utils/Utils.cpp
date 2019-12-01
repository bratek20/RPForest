#include "Utils.h"

#include <limits>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtc/matrix_transform.hpp>

using namespace std;
using namespace glm;

const float Utils::PI = 3.14159265;
const float Utils::INF = std::numeric_limits<float>::max();
const vec3 Utils::VX = vec3(1, 0, 0);
const vec3 Utils::VY = vec3(0, 1, 0);
const vec3 Utils::VZ = vec3(0, 0, 1);

const array<Utils::Axis, 3> Utils::AXES { Utils::Axis::X, Utils::Axis::Y, Utils::Axis::Z};

Utils::Axis Utils::next(Axis axis, int step){
    return static_cast<Axis>((axis + step) % 3);
}

float Utils::findBest(const vector<vec3>& poses, Axis axis, CmpType cmpType){
    float ans = cmpType == CmpType::MIN ? INF : -INF;
    function<bool(float,float)> comparator = less<float>();
    if(cmpType == CmpType::MAX){
        comparator = greater<float>();
    }

    for (vec3 pos : poses) {
        ans = min(ans, pos[axis], comparator);
    }
    return ans;
}

vec2 Utils::toVec2(const vec3& v, Axis toOmit){
    vec2 ans;
    int i=0;
    for(Axis a : AXES){
        if(a != toOmit){
            ans[i++] = v[a];
        }
    }
    return ans;
}

mat4 Utils::getScaleMat(float scale) {
    return glm::scale(glm::mat4(1.0f), vec3(scale, scale, scale));
}

mat4 Utils::getRotateGlobalMat(vec3 globalY) {
    vec3 right;
    if(abs(globalY.x) < abs(globalY.y)){
        right = vec3(1, 0, 0);
    }
    else{
        right = vec3(0, 1, 0);
    }

    vec3 globalZ = normalize(cross(globalY, right));
    vec3 globalX = normalize(cross(globalZ, globalY));
    return mat4(globalX.x, globalX.y, globalX.z, 0, 
                globalY.x, globalY.y, globalY.z, 0,
                globalZ.x, globalZ.y, globalZ.z, 0,
                0, 0, 0, 1);
}

vec3 Utils::rotateGlobal(vec3 vec, vec3 globalY){
    return static_cast<vec3>(vec4(vec.x, vec.y, vec.z, 0) * getRotateGlobalMat(globalY));
}

glm::mat3 Utils::calcNormM(glm::mat4 posM) {
    return transpose(inverse(posM));
}

ostream& operator<<(ostream& out, const vec3& v){
    out << "{" <<v.x << "," << v.y << "," << v.z << "}";
    return out;
}