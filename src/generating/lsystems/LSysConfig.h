#ifndef L_SYS_CONFIG_H
#define L_SYS_CONFIG_H

#include <unordered_map>
#include <string>

struct LSysConfig {
    int n;
    float angle;
    char axiom;
    std::unordered_map<char, std::string> productions;

    bool load(const std::string &path);
};

#endif