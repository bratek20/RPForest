

#include "Globals.h"
#include "Mesh.h"
#include "Utils.h"
#include "DebugActor.h"

#include <iostream>

using namespace std;

const glm::vec3 Vertex::NORMAL_NOT_SET = glm::vec3(0);

Vertex::Vertex(glm::vec3 position) : Vertex(position, NORMAL_NOT_SET){}

Vertex::Vertex(glm::vec3 position, glm::vec3 normal)
    : position(position), normal(normal) {}

void Vertex::apply(const glm::mat4& posM, const glm::mat3& normM) {
    position = static_cast<glm::vec3>(posM * glm::vec4(position, 1));
    normal = normalize(normM * normal);
}

bool Vertex::hasNormal() const {
    return normal != NORMAL_NOT_SET;
}

void Vertex::debug() {
    DebugActor::get()->drawLine(position, position + normal);
}