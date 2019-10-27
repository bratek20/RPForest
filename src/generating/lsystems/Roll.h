#ifndef ROLL_H
#define ROLL_H

#include "Symbol.h"

class Roll : public Symbol {
    float angle;

public:
    Roll(float angle) : angle(angle) {} 

    void process(ProcessContext& pc) override {
        pc.current.rotateFront(angle);
    }

    std::string toString() override {
        return "Roll(" + std::to_string(angle) + ")";
    }

};

#endif