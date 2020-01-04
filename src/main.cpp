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

int main(int argc, char* argv[]){
	string configPath = argc >= 2 ? argv[1] : "config.rtc";
	if(!c.load(configPath)){
		cerr << "Loading config failed!" << endl;
		return -1;
	}
    
	unsigned seed = Random::SEED_NOT_SET;
	if(argc > 2){
		seed = atoi(argv[2]);
	}

	if(!Window::open("RPForest", c)){
        return -1;
    }

	Globals::init(c);
	Random::init(seed);
	Assets::init();
	Materials::init();	
	
	scene = Scene::create(c);

	if(c.debugMode){		
		Input::init();
		Input::onKeyPressed(GLFW_KEY_P, takePhoto);
		Input::onKeyPressed(GLFW_KEY_M, printCameraPosition);
		Input::onKeyPressed(GLFW_KEY_L, debugRay);

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


