#include "Assets.h"
#include "Color.h"
#include "Globals.h"
#include "Input.h"
#include "Scene.h"
#include "Window.h"

#include <algorithm>
#include <iomanip>
#include <iostream>

#include "Random.h"
#include "Shapes.h"
#include "Turtle.h"
using namespace std;

ScenePtr scene;
Turtle t;

void takePhoto() {
    scene->takePhotoPathTracing();
}

void debugRay() {
    scene->debugRay();
}

int main(int argc, char* argv[]) {
    try {
        if (argc < 2) {
            cerr << "Config path not provided. Example program execution: "
                    "./rpforest.exe ../configs/default"
                 << endl;
            return -1;
        }
        string configFolder = argv[1];
        unsigned seed = argc > 2 ? atoi(argv[2]) : Random::SEED_NOT_SET;

        Random::init(seed);
        Assets::init(configFolder);
        Globals::init();

        if (!Window::open("RPForest")) {
            return -1;
        }

        Assets::loadProgram3D();
        Materials::init();
        scene = Scene::create();

        if (Globals::debug) {
            Input::init();
            Input::onKeyPressed(GLFW_KEY_P, takePhoto);
            // Input::onKeyPressed(GLFW_KEY_L, debugRay);

            while (!Window::shouldClose()) {
                Input::handle();

                scene->update();

                Window::clear();
                scene->render();
                Window::swapBuffers();

                Globals::updateTime();
            }
            Assets::clear();
        } else {
            takePhoto();
        }

        Window::close();
    } catch (exception e) {
        cerr << "Exception cought: " << e.what() << endl;
    }
    return 0;
}
