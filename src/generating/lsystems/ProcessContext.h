#ifndef PROCESS_CONTEXT_H
#define PROCESS_CONTEXT_H

#include "Turtle.h"
#include "Mesh.h"

struct ProcessContext {
    Turtle current;
    std::vector<Turtle> stack;
    std::vector<MeshPtr> meshes; 
    std::vector<glm::vec3> vertices;
};

#endif