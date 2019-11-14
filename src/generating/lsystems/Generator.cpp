#include "Generator.h"

using namespace std;

Generator::Generator(SymbolPtr axiom) : axiom(axiom) {}

ProcessContext Generator::generate() {
    vector<SymbolPtr> current = {axiom};
    vector<SymbolPtr> next;

    for (int i = 0; i < getN(); i++) {
        for (auto &s : current) {
            auto result = s->produce();
            next.insert(next.end(), result.begin(), result.end());
        }
        current = std::move(next);
        next.clear();
    }

    ProcessContext pc;
    for (auto &s : current) {
        s->process(pc);
    }

    return pc;
}