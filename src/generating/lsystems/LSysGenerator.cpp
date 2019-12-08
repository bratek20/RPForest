#include "LSysGenerator.h"
#include "StrSymbol.h"

using namespace std;

LSysGenerator::LSysGenerator(const LSysConfig& config) 
: Generator(generateAxiom(config), {Generator::EMPTY}) {}

SymbolPtr LSysGenerator::generateAxiom(const LSysConfig& config) {
    auto& prods = config.productions;
    string symbols(1, config.axiom);
    for(int i=0;i<config.n;i++){
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