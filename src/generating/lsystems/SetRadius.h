#ifndef SET_RADIUS_H
#define SET_RADIUS_H

#include "Symbol.h"

class SetRadius : public Symbol {
    float radius;

public:
    SetRadius(float radius) : radius(radius) {} 

    void process(ProcessContext& pc) override {
        pc.current.setRadius(radius);
    }

    std::string toString() override {
        return "SetRadius(" + std::to_string(radius) + ")";
    }

};

#endif