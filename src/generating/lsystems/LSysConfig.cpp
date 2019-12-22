#include "LSysConfig.h"

#include <fstream>
#include <iostream>

using namespace std;

bool LSysConfig::load(const string &path) {
    ifstream file(path);
    if (!file.is_open()) {
        cerr << "File: " << path << " not opened!";
        return false;
    }
    file >> n;
    file >> angle;
    file >> height;

    file >> axiom;
    
    string symbol;
    while(file >> symbol){
        string arrow, production;
        file >> arrow >> production;
        productions[symbol[0]] = production;
    }

    return true;
}