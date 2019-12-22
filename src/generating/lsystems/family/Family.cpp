#include "Family.h"
#include "FamilyAxiom.h"

int Family::n = 20;
float Family::delta = 60;
float Family::LA;
float Family::RA;
float Family::LB;
float Family::RB;
float Family::PD;

Family::Family()
    : Generator(Symbol::S<FamilyAxiom>(),
                {load1, load2, load3, load4, load5, load6},
                0.2f, Generator::LOW, Materials::LEAF) {}

void Family::load1() {
    LA = 5;
    RA = 1.0;
    LB = 1.0;
    RB = 1.00;
    PD = 0.00;
}

void Family::load2() {
    LA = 5;
    RA = 1.0;
    LB = 1.0;
    RB = 1.00;
    PD = 1.00;
}

void Family::load3() {
    LA = 5;
    RA = 1.0;
    LB = 0.6;
    RB = 1.06;
    PD = 0.25;
}

void Family::load4() {
    LA = 5;
    RA = 1.2;
    LB = 10.0;
    RB = 1.00;
    PD = 0.50;
}

void Family::load5() {
    LA = 5;
    RA = 1.2;
    LB = 4.0;
    RB = 1.10;
    PD = 0.25;
}

void Family::load6() {
    LA = 5;
    RA = 1.1;
    LB = 1.0;
    RB = 1.20;
    PD = 1.00;
}