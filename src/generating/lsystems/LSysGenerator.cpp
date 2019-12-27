#include "LSysGenerator.h"
#include "StrSymbol.h"

using namespace std;

LSysGenerator::LSysGenerator(GeneratorConfigPtr config) 
: Generator(generateAxiom(static_cast<const LSysConfig&>(*config)), config) {}

SymbolPtr LSysGenerator::generateAxiom(const LSysConfig& config) {
    auto& prods = config.productions;
    string symbols = config.axiom;
    for(int i=0;i<config.lSysN;i++){
        string newSymbols = "";
        for(char s : symbols) {
            auto it = prods.find(s); 
            if(it != prods.end()) {
                newSymbols += it->second;
            }
            else {
                newSymbols += s;
            }
        }
        symbols = newSymbols;
    } 
    return Symbol::S<StrSymbol>(move(symbols), config);
}