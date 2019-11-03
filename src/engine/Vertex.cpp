

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

void Vertex::apply(const glm::mat4& m) {
    position = static_cast<glm::vec3>(m * glm::vec4(position, 1));
    normal = static_cast<glm::vec3>(m * glm::vec4(normal, 0));
}

bool Vertex::hasNormal() const {
    return normal != NORMAL_NOT_SET;
}

void Vertex::debug() {
    DebugActor::get()->drawLine(position, position + normal);
}