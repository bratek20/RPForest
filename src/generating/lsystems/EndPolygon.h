#ifndef END_POLYGON_H
#define END_POLYGON_H

#include "Symbol.h"

class EndPolygon : public Symbol {
public:
    EndPolygon() {} 

    void process(ProcessContext& pc) override {
        pc.model->add(pc.polygons.back().genMesh());
        pc.polygons.pop_back();
    }

    std::string toString() override {
        return "";
    }

};

#endif