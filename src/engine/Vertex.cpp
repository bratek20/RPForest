

#include "Globals.h"
#include "Mesh.h"
#include "Utils.h"

#include <iostream>

using namespace std;

const glm::vec3 Vertex::NORMAL_NOT_SET = glm::vec3(0);

Vertex::Vertex(glm::vec3 position) : Vertex(position, NORMAL_NOT_SET){}

Vertex::Vertex(glm::vec3 position, glm::vec3 normal)
    : position(position), normal(normal) {}

bool Vertex::hasNormal() const {
    return normal != NORMAL_NOT_SET;
}