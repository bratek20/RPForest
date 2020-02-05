#include "Scene.h"
#include "Assets.h"
#include "Color.h"
#include "DebugActor.h"
#include "EmbreeWrapper.h"
#include "Family.h"
#include "Honda.h"
#include "LSysGenerator.h"
#include "PathTracer.h"
#include "PhotoSaver.h"
#include "Shapes.h"
#include "SimpleAccStruct.h"
#include "SkyLightSampler.h"
#include "SpawnerActor.h"
#include "Ternary.h"
#include "Timer.h"

using namespace std;
using namespace glm;

Scene::Scene() : Actor(nullptr) {}

ScenePtr Scene::create() {
    Timer::start("Creating scene");

    ScenePtr scene = ScenePtr(new Scene());

    DebugActorPtr debugActor = DebugActor::create();
    scene->addChild(debugActor);

    scene->createWorld();
    // scene->debug();
    Timer::stop();
    return scene;
}

void Scene::createWorld() {
    camera = Camera::create(terrain);
    addChild(camera);

    sky = SkyActor::create();
    addChild(sky);

    addChild(Actor::create(Model::New(terrain.getMesh())));

    vec3 cameraPos = camera->getWorldPosition();
    for (auto& spawnerConfig : Assets::SPAWNER_CONFIGS) {
        addChild(SpawnerActor::create(spawnerConfig, terrain, cameraPos));
    }
}

void Scene::render() {
    Assets::PROGRAM_3D.setViewMat(camera->getViewMat());
    Assets::PROGRAM_3D.setProjectionMat(camera->getProjectionMat());

    Light::applyLights(Assets::PROGRAM_3D);
    Actor::render(mat4(1.0f));
}

CameraPtr Scene::getCamera() const {
    return camera;
}

void Scene::takePhotoPathTracing() {
    cout << "Taking photo..." << endl;

    const PathTracerConfig& c = Assets::PATH_TRACER_CONFIG;
    float xRes = c.resolution.x;
    float yRes = c.resolution.y;

    vec3 origin = camera->getWorldPosition();
    cout << "Camera position: " << origin << endl;
    auto model = genFlatModel();
    auto& triangles = model->getTriangles();
    auto& meshes = model->getMeshes();
    cout << "Triangles number: " << triangles.size() << endl;
    cout << "Resolution: " << xRes << " x " << yRes << endl;
    cout << "Samples per pixel: " << c.samples << endl;

    Timer::start("Building accStruct");
    EmbreeWrapper accStruct(meshes);
    Timer::stop();

    if(c.animationFrames <= 1){
        makePhoto(c.photoName, accStruct);
    }
    else{
        float interval = (c.animationEndTime - c.animationStartTime) / (c.animationFrames - 1);
        for(int frame = 1; frame <= c.animationFrames; frame++){
            float time = c.animationStartTime + interval * (frame - 1);
            cout << "Time of a day: " << time << endl;
            sky->setTime(time);
            string frameName = calcFrameName(frame);
            makePhoto(frameName, accStruct);
        }
    }

}

string Scene::calcFrameName(int frame) {
    string prefix = "";
    if(frame < 10) {
        prefix += "0";
    }
    if(frame < 100) {
        prefix += "0";
    }
    return "frame" + prefix + to_string(frame);
}

void Scene::makePhoto(const std::string& name, EmbreeWrapper& accStruct) {
    Timer::start("Make photo " + name);

    const PathTracerConfig& c = Assets::PATH_TRACER_CONFIG;
    float xRes = c.resolution.x;
    float yRes = c.resolution.y;
    PhotoSaver photo(xRes, yRes);
    
    
    vec3 origin = camera->getWorldPosition();
    vec3 leftTop = camera->getLeftTop();
    vec3 leftBottom = camera->getLeftBottom();
    vec3 rightTop = camera->getRightTop();
    for (int x = 0; x < xRes; x++) {
        for (int y = 0; y < yRes; y++) {
            float xShift = x / xRes;
            float yShift = y / yRes;

            vec3 pos = -leftTop + mix(leftTop, rightTop, xShift) +
                       mix(leftTop, leftBottom, yShift);
            vec3 direction = normalize(pos - origin);
            Ray r(origin, direction);

            vec3 color = vec3(0);
            for (int i = 0; i < c.samples; i++) {
                PathTracer::CastData data = PathTracer::cast(
                    r, c.maxRayBounces, accStruct, sky->getLightSampler());
                vec3 sampleC = data.hit ? data.emittance : vec3(0);
                color += sampleC;
            }

            color /= c.samples;
            photo.setPixel(x, y, color);

            int progress = 100 * (x * yRes + y) / (xRes * yRes);
            cout << "\rProgress: " << progress << "%";
        }
    }
    cout << endl;
    Timer::stop();

    string photoSavePath = Assets::photoSavePath(name);
    photo.save(photoSavePath);
    cout << "Photo made and saved to: " << photoSavePath << endl;
}

void Scene::debugRay() {
    const PathTracerConfig& c = Assets::PATH_TRACER_CONFIG;
    
    PathTracer::drawLines = true;
    DebugActor::get()->getModel()->clear();

    auto model = genFlatModel(mat4(1.0f));
    auto& meshes = model->getMeshes();
    EmbreeWrapper accStruct(meshes);

    vec3 origin = camera->getWorldPosition();
    vec3 leftTop = camera->getLeftTop();
    vec3 leftBottom = camera->getLeftBottom();
    vec3 rightTop = camera->getRightTop();

    vec3 pos = -leftTop + mix(leftTop, rightTop, 0.5f) +
               mix(leftTop, leftBottom, 0.5f);
    vec3 direction = normalize(pos - origin);
    Ray r(origin, direction);

    for (int i = 0; i < c.samples; i++) {
        PathTracer::cast(r, c.maxRayBounces, accStruct, sky->getLightSampler());
    }

    PathTracer::drawLines = false;
}