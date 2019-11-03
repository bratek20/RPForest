#include "Ternary.h"
#include "TernaryAxiom.h"

int Ternary::n = 3;
float Ternary::d1;
float Ternary::d2;
float Ternary::a;
float Ternary::lr;
float Ternary::vr = 1.732;
glm::vec3 Ternary::T;
float Ternary::e;

Ternary::Ternary() : Generator(Symbol::S<TernaryAxiom>(), n) {
    load1();
}

void Ternary::load1() {
    d1 = 94.74;
    d2 = 132.63;
    a = 18.95;
    lr = 1.109;
    T = glm::vec3(0, -1, 0);
    e = 0.22;
    n = 6;
}

void Ternary::load2() {
    d1 = 94.74;
    d2 = 132.63;
    a = 18.95;
    lr = 1.109;
    T = glm::vec3(0, -1, 0);
    e = 0.22;
    n = 6;
}

void Ternary::load3() {
    d1 = 94.74;
    d2 = 132.63;
    a = 18.95;
    lr = 1.109;
    T = glm::vec3(0, -1, 0);
    e = 0.22;
    n = 6;
}

void Ternary::load4() {
    d1 = 94.74;
    d2 = 132.63;
    a = 18.95;
    lr = 1.109;
    T = glm::vec3(0, -1, 0);
    e = 0.22;
    n = 6;
}
