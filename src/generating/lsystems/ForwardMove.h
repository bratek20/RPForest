#ifndef FORWARD_MOVE_H
#define FORWARD_MOVE_H

#include "Symbol.h"

class ForwardMove : public Symbol {
    float length;

public:
    ForwardMove(float length) : length(length) {} 

    void process(ProcessContext& pc) override {
        pc.current.move(length);
    }

    std::string toString() override {
        return "ForwardMove(" + std::to_string(length) + ")";
    }

};

#endif