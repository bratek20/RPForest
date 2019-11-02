#ifndef FORWARD_DRAW_H
#define FORWARD_DRAW_H

#include "Symbol.h"
#include "Shapes.h"

class ForwardDraw : public Symbol {
    float length;

public:
    ForwardDraw(float length) : length(length) {} 

    void process(ProcessContext& pc) override {
        auto mesh = Shapes::genCone(pc.current.getRadius(), pc.current.getRadius(), length); 
        mesh->apply(pc.current.getWorldMat());
        pc.current.move(length);
        pc.meshes.push_back(mesh);
    }

    std::string toString() override {
        return "ForwardDraw(" + std::to_string(length) + ")";
    }

};

#endif