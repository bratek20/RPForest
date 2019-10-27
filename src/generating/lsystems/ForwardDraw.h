#ifndef FORWARD_DRAW_H
#define FORWARD_DRAW_H

#include "Symbol.h"

class ForwardDraw : public Symbol {
    float length;

public:
    ForwardDraw(float length) : length(length) {} 

    void process(ProcessContext& pc) override {
        pc.verticies.push_back(pc.current.pos);
        pc.current.move(length);
        pc.verticies.push_back(pc.current.pos);
    }

    std::string toString() override {
        return "ForwardDraw(" + std::to_string(length) + ")";
    }

};

#endif