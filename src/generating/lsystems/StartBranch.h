#ifndef START_BRANCH_H
#define START_BRANCH_H

#include "Symbol.h"

class StartBranch : public Symbol {
public:
    StartBranch() {} 

    void process(ProcessContext& pc) override {
        pc.stack.push_back(pc.current);
    }

    std::string toString() override {
        return "StartBranch";
    }

};

#endif