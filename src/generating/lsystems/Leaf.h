#ifndef LEAF_H
#define LEAF_H

#include "Symbol.h"

class Leaf : public Symbol {
public:
    Leaf() = default;

    void process(ProcessContext& pc) override;

    std::string toString() override {
        return "";
    }

};

#endif