

#include "Mesh.h"
#include "Utils.h"
#include "Globals.h"

#include <iostream>

using namespace std;

const glm::vec3 Vertex::NORMAL_NOT_SET = glm::vec3(0);

Vertex::Vertex(glm::vec3 position) {
    this->position = position;
    normal = NORMAL_NOT_SET;
}

bool Vertex::hasNormal() const { return normal != NORMAL_NOT_SET; }