#ifndef PROCESS_CONTEXT_H
#define PROCESS_CONTEXT_H

#include "Turtle.h"

#include <vector>

struct ProcessContext {
    Turtle current;
    std::vector<Turtle> stack;
    std::vector<glm::vec3> verticies;
};

#endif