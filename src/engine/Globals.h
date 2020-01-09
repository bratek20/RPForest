#ifndef GLOBALS_H
#define GLOBALS_H

#include <memory>

class Globals{
public:
    static float previousFrameTime;
    static float currentFrameTime;
    static float deltaTime;

    static bool debug;

    static void init();
    static void updateTime();

    static float random(float a = 0.0f, float b = 1.0f);    
};

#endif