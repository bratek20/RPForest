#ifndef PROCESS_CONTEXT_H
#define PROCESS_CONTEXT_H

#include "Turtle.h"
#include "Mesh.h"
#include "Polygon.h"

struct ProcessContext {
    Turtle current;
    std::vector<Turtle> stack;
    std::vector<MeshPtr> meshes; 
    std::vector<Polygon> polygons;    
};

#endif