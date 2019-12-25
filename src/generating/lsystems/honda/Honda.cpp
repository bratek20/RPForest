#include "Honda.h"
#include "HondaA.h"

int Honda::n = 10;
float Honda::r1;
float Honda::r2;
float Honda::a0;
float Honda::a2;
float Honda::d = 137.5;
float Honda::wr = 0.707;

Honda::Honda()
    : Generator(Symbol::S<HondaA>(1, 0.1), {load1, load2, load3, load4},
     2, Generator::HIGH, Materials::BARK) {}

void Honda::load1() {
    r1 = 0.9;
    r2 = 0.6;
    a0 = 45;
    a2 = 45;
}

void Honda::load2() {
    r1 = 0.9;
    r2 = 0.9;
    a0 = 45;
    a2 = 45;
}

void Honda::load3() {
    r1 = 0.9;
    r2 = 0.8;
    a0 = 45;
    a2 = 45;
}

void Honda::load4() {
    r1 = 0.9;
    r2 = 0.7;
    a0 = 30;
    a2 = -30;
}
