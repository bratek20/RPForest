#ifndef TERNARY_H
#define TERNARY_H

#include "Generator.h"

class Ternary {
public:
    static int n;
    static float d1;
    static float d2;
    static float a;
    static float lr;
    static float vr;
    static glm::vec3 T;
    static float e;

    Ternary();
    
    static void load1();
    static void load2();
    static void load3();
    static void load4();
};

#endif