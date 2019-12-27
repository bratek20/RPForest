#include "Window.h"
#include "Input.h"
#include "Globals.h"
#include "Scene.h"
#include "Color.h"
#include "Assets.h"
#include "Config.h"

#include <iostream>
#include <algorithm>
#include <iomanip>

#include "Random.h"
#include "Turtle.h"
#include "Shapes.h"
using namespace std;

ScenePtr scene;
Config c;
Turtle t;

void printCameraPosition(){
	cout << "Camera pos: " << scene->getCamera()->getWorldPosition() << endl;
}

void takePhoto(){
	scene->takePhotoPathTracing(c);

}

void debugRay() {
	scene->debugRay(c);
}

void debugRot(){
	scene->getModel()->clear();
	auto mesh = Shapes::genCone(0.02, 0.01, 0.5);
	mesh->apply(t.getWorldMat());
	scene->getModel()->add(mesh);
}

int main(int argc, char* argv[]){
	string configPath = argc >= 2 ? argv[1] : "config.rtc";
	if(!c.load(configPath)){
		cerr << "Loading config failed!" << endl;
		return -1;
	}
    if(!Window::open("RPForest", c)){
        return -1;
    }

	Globals::init(c);
	Random::init();
	Assets::init();
	Materials::init();
	
	scene = Scene::create(c);

	if(c.debugMode){		
		Input::init();
		Input::onKeyPressed(GLFW_KEY_P, takePhoto);
		Input::onKeyPressed(GLFW_KEY_M, printCameraPosition);
		Input::onKeyPressed(GLFW_KEY_L, debugRay);

		float angle = 30;
		Input::onKeyPressed(GLFW_KEY_KP_4, [&](){t.rotateUp(angle);});
		Input::onKeyPressed(GLFW_KEY_KP_6, [&](){t.rotateUp(-angle);});
		Input::onKeyPressed(GLFW_KEY_KP_8, [&](){t.rotateLeft(angle);});
		Input::onKeyPressed(GLFW_KEY_KP_5, [&](){t.rotateLeft(-angle);});
		Input::onKeyPressed(GLFW_KEY_KP_7, [&](){t.rotateFront(-angle);});
		Input::onKeyPressed(GLFW_KEY_KP_9, [&](){t.rotateFront(angle);});
		Input::onKeyPressed(GLFW_KEY_KP_0, debugRot);

		while(!Window::shouldClose()){
			Input::handle();

			scene->update();

			Window::clear();
			scene->render();
			Window::swapBuffers();

			Globals::updateTime();
		}	
		Assets::clear();
	}
	else{
		takePhoto();
	}	
	
	Window::close();
	return 0;
}


