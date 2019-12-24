#include "Scene.h"
#include "Assets.h"
#include "Color.h"
#include "PhotoSaver.h"
#include "SimpleAccStruct.h"
#include "Timer.h"
#include "PathTracer.h"
#include "SkyLightSampler.h"
#include "EmbreeWrapper.h"
#include "DebugActor.h"
#include "Shapes.h"
#include "Honda.h"
#include "Ternary.h"
#include "Family.h"
#include "LSysGenerator.h"
#include "Spawner.h"

using namespace std;
using namespace glm;

Scene::Scene(ModelPtr sceneModel, float worldSize) : Actor(sceneModel), lightSampler(worldSize/2), terrain(2, worldSize, 10, 5, 0.5) {}

ScenePtr Scene::create(const Config &c) {
    Timer::start("Creating scene");
    float worldSize = 10;
    DebugActorPtr debugActor = DebugActor::create();
    ScenePtr scene = ScenePtr(new Scene(Model::New(), worldSize));
    scene->addChild(debugActor);

    scene->camera = Camera::create();
    scene->addChild(scene->camera);

    scene->addChild(Actor::create(Model::New(scene->terrain.getMesh())));
    //scene->camera->addChild(Light::create());
    //Light::loadLights(scene->getModel()->getTriangles());
    
    auto gen = Honda();
    //auto res = Family().getRandom();
    //scene->getModel()->add(res);
    //scene->getModel()->add(Shapes::genCone(2, 1, 5), true);
    for(int i=0;i<4;i++){
        ActorPtr t = Actor::create(gen.get(i));
        t->move({3*i, 0, 0});
        //scene->addChild(t);
    }


    auto spawner = Spawner({}, "plants", Generator::LOW, Materials::PLANT, scene->terrain);
    //scene->getModel()->add(Mesh::New(res.vertices), true);
    scene->debug();
    Timer::stop();
    return scene;
}

void Scene::render() {
    Assets::program.setViewMat(camera->getViewMat());
    Assets::program.setProjectionMat(camera->getProjectionMat());

    Light::applyLights(Assets::program);
    Actor::render(mat4(1.0f));
}

CameraPtr Scene::getCamera() const { return camera; }

void Scene::takePhotoPathTracing(const Config &c) {
    cout << "Taking photo..." << endl;
    
    float xRes = c.resolution.x;
    float yRes = c.resolution.y;
    PhotoSaver photo(xRes, yRes);

    vec3 origin = camera->getWorldPosition();
    cout << "Camera position: " << origin << endl;
    auto model = genFlatModel(mat4(1.0f));
    auto &triangles = model->getTriangles();
    auto &meshes = model->getMeshes();
    cout << "Triangles number: " << triangles.size() << endl;
    cout << "Resolution: " << xRes << " x " << yRes << endl;
    cout << "Samples per pixel: " << c.samples << endl;
    
    Timer::start("Building accStruct");
    EmbreeWrapper accStruct(meshes);
    Timer::stop();

    Timer::start("Path tracing");
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
            vec3 emittance = vec3(0);
            for(int i=0;i<c.samples;i++){
                PathTracer::CastData data = PathTracer::cast(r, c.maxRayBounces, accStruct, lightSampler);
                vec3 sampleC = data.hit ? data.emittance : vec3(0); 
                
                color += sampleC;
                emittance += data.emittance;
            }
            
            color /= c.samples;
            emittance /= c.samples;
             
            photo.setPixel(x, y, color);
            
            int progress = 100 * (x*yRes + y) / (xRes * yRes);
            cout << "\rProgress: " << progress << "%";
        }
    }
    cout << endl;
    Timer::stop();

    string photoSavePath = Assets::photoSavePath(c.photoName);
    photo.save(photoSavePath);
    cout << "Photo taken and saved to: " << photoSavePath << endl;
}

void Scene::debugRay(const Config& c) {
    PathTracer::drawLines = true;
    DebugActor::get()->getModel()->clear();

    auto &meshes = getModel()->getMeshes();
    EmbreeWrapper accStruct(meshes);

    vec3 origin = camera->getWorldPosition();
    vec3 leftTop = camera->getLeftTop();
    vec3 leftBottom = camera->getLeftBottom();
    vec3 rightTop = camera->getRightTop();

    vec3 pos = -leftTop + mix(leftTop, rightTop, 0.5f) +
                    mix(leftTop, leftBottom, 0.5f);
    vec3 direction = normalize(pos - origin);
    Ray r(origin, direction);

    for(int i=0;i<c.samples;i++){
        PathTracer::CastData data = PathTracer::cast(r, c.maxRayBounces, accStruct, lightSampler);
    }           

    PathTracer::drawLines = false;
}