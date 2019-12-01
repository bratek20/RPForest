#ifndef PROCESS_CONTEXT_H
#define PROCESS_CONTEXT_H

#include "Turtle.h"
#include "Model.h"
#include "Polygon.h"

struct ProcessContext {
    Turtle current;
    std::vector<Turtle> stack;
    ModelPtr model = Model::New(); 
    std::vector<Polygon> polygons;    
};

#endif