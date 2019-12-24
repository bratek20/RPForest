#include "Config.h"

#include <iostream>

using namespace std;

Config::Config() {
    customParse("#", [](ifstream& file){
        string comment;
        getline(file, comment);
        (void)comment;
    });
    parse("PhotoName", &photoName);
    parse("Resolution", &resolution);
    parse("Samples", &samples);
    parse("MaxRayBounces", &maxRayBounces);
    parse("DebugMode", &debugMode);
}