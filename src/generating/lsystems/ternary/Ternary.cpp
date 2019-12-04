#include "Ternary.h"
#include "TernaryAxiom.h"

int Ternary::n = 6;
float Ternary::d1;
float Ternary::d2;
float Ternary::a;
float Ternary::lr;
float Ternary::vr = 1.732;
glm::vec3 Ternary::T;
float Ternary::e;

Ternary::Ternary() : Generator(Symbol::S<TernaryAxiom>(), {load1, load2, load3, load4}) {
}

void Ternary::onModelGenerated(ModelPtr model) {
    model->matchHeight(2);
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
    d1 = 137.50;
    d2 = 137.50;
    a = 18.95;
    lr = 1.109;
    T = glm::vec3(0, -1, 0);
    e = 0.14;
    n = 8;
}

void Ternary::load3() {
    d1 = 112.50;
    d2 = 157.50;
    a = 22.50;
    lr = 1.790;
    T = glm::vec3(-0.02, -1, 0);
    e = 0.27;
    n = 8;
}

void Ternary::load4() {
    d1 = 180.00;
    d2 = 252.00;
    a = 36.00;
    lr = 1.070;
    T = glm::vec3(-0.61, 0.77, -0.19);
    e = 0.4;
    n = 6;
}
