#ifndef SAVE_VERTEX_H
#define SAVE_VERTEX_H

#include "Symbol.h"

class SaveVertex : public Symbol {
public:
    SaveVertex() {} 

    void process(ProcessContext& pc) override {
        pc.polygons.back().save(pc.current.getPos());
    }

    std::string toString() override {
        return "";
    }

};

#endif