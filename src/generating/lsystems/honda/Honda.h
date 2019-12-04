#ifndef HONDA_H
#define HONDA_H

#include "Generator.h"

class Honda : public Generator {
public:
    static int n;
    static float r1;
    static float r2;
    static float a0;
    static float a2;
    static float d;
    static float wr;

    Honda();
    
    int getN() override {
        return n;
    }

    void onModelGenerated(ModelPtr model) override;

    static void load1();
    static void load2();
    static void load3();
    static void load4();
};

#endif