#ifndef FAMILY_H
#define FAMILY_H

#include "Generator.h"

class Family : public Generator {
public:
    static int n;
    static float delta;
    static float LA;
    static float RA;
    static float LB;
    static float RB;
    static float PD;

    Family();

    int getN() override {
        return n;
    }
    
    static void load1();
    static void load2();
    static void load3();
    static void load4();
    static void load5();
    static void load6();
};

#endif