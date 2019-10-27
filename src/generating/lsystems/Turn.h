#ifndef TURN_H
#define TURN_H

#include "Symbol.h"

class Turn : public Symbol {
    float angle;

public:
    Turn(float angle) : angle(angle) {} 

    void process(ProcessContext& pc) override {
        pc.current.rotateUp(angle);
    }

    std::string toString() override {
        return "Turn(" + std::to_string(angle) + ")";
    }

};

#endif