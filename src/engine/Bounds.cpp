

#include "Bounds.h"

using namespace std;

const glm::vec3 Bounds::MIN_NOT_SET = glm::vec3(Utils::INF);;
const glm::vec3 Bounds::MAX_NOT_SET = glm::vec3(-Utils::INF);

Bounds::Bounds()
    : pMin(MIN_NOT_SET),
      pMax(MAX_NOT_SET) {}

Bounds::Bounds(const vector<glm::vec3> &poses) {
    for (auto axis : Utils::AXES) {
        float minVal = Utils::findBest(poses, axis, Utils::CmpType::MIN);
        float maxVal = Utils::findBest(poses, axis, Utils::CmpType::MAX);
        pMin[axis] = minVal;
        pMax[axis] = maxVal;
    }
}

Bounds Bounds::merge(const Bounds &other) const {
    vector<glm::vec3> poses;
    if(this->isValid()){
        poses.push_back(pMin);
        poses.push_back(pMax);
    }
    if(other.isValid()){
        poses.push_back(other.pMin);
        poses.push_back(other.pMax);
    }
    return Bounds(poses);
}

pair<Bounds, Bounds> Bounds::split(Utils::Axis axis, float value) const {
    pair<Bounds, Bounds> ans = {*this, *this};
    ans.first.pMax[axis] = ans.second.pMin[axis] = value;
    return ans; 
}

bool Bounds::isValid() const {
    return pMin != MIN_NOT_SET && pMax != MAX_NOT_SET;
}

glm::vec3 Bounds::diagonal() const { return pMax - pMin; }

float Bounds::surfaceArea() const {
    glm::vec3 d = diagonal();
    return 2 * (d.x * d.y + d.x * d.z + d.y * d.z);
}

Utils::Axis Bounds::maximumExtent() const {
    glm::vec3 d = diagonal();
    if (d.x > d.y && d.x > d.z) {
        return Utils::Axis::X;
    }

    else if (d.y > d.z) {
        return Utils::Axis::Y;
    }

    else {
        return Utils::Axis::Z;
    }
}
