#ifndef PITCH_H
#define PITCH_H

#include "Symbol.h"

class Pitch : public Symbol {
    float angle;

public:
    Pitch(float angle) : angle(angle) {} 

    void process(ProcessContext& pc) override {
        pc.current.rotateLeft(angle);
    }

    std::string toString() override {
        return "Pitch(" + std::to_string(angle) + ")";
    }

};

#endif