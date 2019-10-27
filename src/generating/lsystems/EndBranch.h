#ifndef END_BRANCH_H
#define END_BRANCH_H

#include "Symbol.h"

class EndBranch : public Symbol {
public:
    EndBranch() {} 

    void process(ProcessContext& pc) override {
        pc.current = pc.stack.back();
        pc.stack.pop_back();
    }

    std::string toString() override {
        return "EndBranch";
    }

};

#endif