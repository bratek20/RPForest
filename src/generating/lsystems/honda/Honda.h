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
    
    static int load1();
    static int load2();
    static int load3();
    static int load4();
};

#endif