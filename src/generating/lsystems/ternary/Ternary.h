#ifndef TERNARY_H
#define TERNARY_H

#include "Generator.h"

class Ternary : public Generator {
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

    static int load1();
    static int load2();
    static int load3();
    static int load4();
};

#endif