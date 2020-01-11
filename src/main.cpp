#include "Window.h"
#include "Input.h"
#include "Globals.h"
#include "Scene.h"
#include "Color.h"
#include "Assets.h"

#include <iostream>
#include <algorithm>
#include <iomanip>

#include "Random.h"
#include "Turtle.h"
#include "Shapes.h"
using namespace std;

ScenePtr scene;
Turtle t;

void takePhoto(){
	scene->takePhotoPathTracing();
}

void debugRay() {
	scene->debugRay();
}

int main(int argc, char* argv[]){
	string configFolder = argc >= 2 ? argv[1] : "default";    
	unsigned seed = argc > 2 ? atoi(argv[2]) : Random::SEED_NOT_SET;
	
	Random::init(seed);
	Assets::init(configFolder);
	Globals::init();
	
	if(!Window::open("RPForest")){
        return -1;
    }

	Assets::loadProgram3D();
	Materials::init();	
	scene = Scene::create();

	if(Globals::debug){		
		Input::init();
		Input::onKeyPressed(GLFW_KEY_P, takePhoto);
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


