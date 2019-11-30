#ifndef START_POLYGON_H
#define START_POLYGON_H

#include "Symbol.h"

class StartPolygon : public Symbol {
public:
    StartPolygon() {} 

    void process(ProcessContext& pc) override {
        pc.polygons.emplace_back();
    }

    std::string toString() override {
        return "";
    }

};

#endif