#ifndef SET_WIDTH_H
#define SET_WIDTH_H

#include "Symbol.h"

class SetWidth : public Symbol {
    float width;

public:
    SetWidth(float width) : width(width) {} 

    void process(ProcessContext& pc) override {
        pc.current.width = width;
    }

    std::string toString() override {
        return "SetWidth(" + std::to_string(width) + ")";
    }

};

#endif