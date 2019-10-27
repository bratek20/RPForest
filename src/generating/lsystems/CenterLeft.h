#ifndef CENTER_LEFT_H
#define CENTER_LEFT_H

#include "Symbol.h"

class CenterLeft : public Symbol {
public:
    CenterLeft() {} 

    void process(ProcessContext& pc) override {
        pc.current.centerLeft();
    }

    std::string toString() override {
        return "CenterLeft";
    }

};

#endif