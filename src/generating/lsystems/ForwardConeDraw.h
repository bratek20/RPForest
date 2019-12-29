#ifndef FORWARD_CONE_DRAW_H
#define FORWARD_CONE_DRAW_H

#include "Symbol.h"
#include "Shapes.h"

class ForwardConeDraw : public Symbol {
    float length;
    float radius;

public:
    ForwardConeDraw(float length, float radius) : length(length), radius(radius) {} 

    void process(ProcessContext& pc) override {
        auto mesh = Shapes::genCone(pc.current.getRadius(radius), radius, length, *pc.material); 
        mesh->apply(pc.current.getWorldMat());
        pc.current.move(length);
        pc.current.setRadius(radius);
        pc.model->add(mesh);
    }

    std::string toString() override {
        return "ForwardConeDraw(" + std::to_string(length) + ", " + std::to_string(radius) + ")";
    }

};

#endif