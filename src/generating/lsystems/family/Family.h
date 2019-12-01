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
    
    static int load1();
    static int load2();
    static int load3();
    static int load4();
    static int load5();
    static int load6();
};

#endif