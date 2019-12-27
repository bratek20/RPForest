#include "ConfigParser.h"

#include <iostream>

using namespace std;

int ConfigParser::lastTypeId = 0;
unordered_map<int, function<void(ifstream&, void*)>> ConfigParser::typeParsers = {
    { getTypeId<bool>(), parseField<bool>},
    { getTypeId<int>(), parseField<int>},
    { getTypeId<float>(), parseField<float>},
    { getTypeId<string>(), parseField<string>},
    { getTypeId<glm::vec2>(), parseVec2},
    { getTypeId<glm::vec3>(), parseVec3}
};

bool ConfigParser::load(const string &path) {
    this->path = path;
    
    ifstream file(path);
    if (!file.is_open()) {
        cerr << "File: " << path << " not opened!";
        return false;
    }

    string name;
    while (file >> name) {
        if(customParsers.find(name) != customParsers.end()){
            customParsers[name](file);
            continue;
        }
        
        auto it = infos.find(name);
        if(it == infos.end()) {
            cerr << "Parsing of " << name << " not supported!" << endl;
            return false;
        }
        ParserTypeInfo info = it->second;
        typeParsers[info.typeId](file, info.field);
    }

    return true;
}

void ConfigParser::parseVec2(ifstream& file, void* field) {
    glm::vec2& v = *static_cast<glm::vec2*>(field);
    file >> v.x >> v.y;
}

void ConfigParser::parseVec3(ifstream& file, void* field) {
    glm::vec3& v = *static_cast<glm::vec3*>(field);
    file >> v.x >> v.y >> v.z;
}