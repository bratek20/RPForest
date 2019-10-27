#include "Scene.h"
#include "Assets.h"
#include "Color.h"
#include "KDTree.h"
#include "PhotoSaver.h"
#include "RayTracer.h"
#include "SimpleAccStruct.h"
#include "Timer.h"
#include "PathTracer.h"
#include "LightSampler.h"
#include "EmbreeWrapper.h"
#include "DebugActor.h"

#include "bitmap_image.h"

#define USE_EMBREE 1

using namespace std;

Scene::Scene(ModelPtr sceneModel) : Actor(sceneModel) {}

ScenePtr Scene::create(const Config &c) {
    Timer::start("Creating scene");
    DebugActorPtr debugActor = DebugActor::create();
    ScenePtr scene = ScenePtr(new Scene(Model::create(c)));
    scene->addChild(debugActor);

    scene->lightSampler = LightSampler(scene->getModel()->getTriangles());
    scene->camera = Camera::create(c.camera);
    scene->addChild(scene->camera);
    //scene->camera->addChild(Light::create());
    Light::loadLights(scene->getModel()->getTriangles());
    Timer::stop();
    return scene;
}

void Scene::render() {
    Assets::program.setViewMat(camera->getViewMat());
    Assets::program.setProjectionMat(camera->getProjectionMat());

    Light::applyLights(Assets::program);
    Actor::render(glm::mat4(1.0f));
}

CameraPtr Scene::getCamera() const { return camera; }


void Scene::takePhotoRayTracing(const Config& c){
    Ray::setEpsilon(c.rayEpsilon);

    cout << "Taking photo..." << endl;
    bitmap_image photo(c.xRes, c.yRes);

    glm::vec3 origin = camera->getWorldPosition();
    cout << "Camera position: " << origin.x << ", " << origin.y << ", "
         << origin.z << endl;
    auto &triangles = getModel()->getTriangles();
    cout << "Triangles number: " << triangles.size() << endl;

    Timer::start("Building accStruct");
    KDTree accStruct(triangles);
    Timer::stop();

    Timer::start("Raytracing");
    glm::vec3 leftTop = camera->getLeftTop();
    glm::vec3 leftBottom = camera->getLeftBottom();
    glm::vec3 rightTop = camera->getRightTop();
    for (int x = 0; x < c.xRes; x++) {
        for (int y = 0; y < c.yRes; y++) {
            float xShift = static_cast<float>(x) / c.xRes;
            float yShift = static_cast<float>(y) / c.yRes;
            glm::vec3 pos = -leftTop + glm::mix(leftTop, rightTop, xShift) +
                            glm::mix(leftTop, leftBottom, yShift);
            glm::vec3 direction = glm::normalize(pos - origin);
            auto hit = RayTracer::cast(c.k, Ray(origin, direction), accStruct,
                                       Light::getLights());
            Color color = hit.first ? hit.second : c.background;
            photo.set_pixel(x, y, color.r * 255, color.g * 255, color.b * 255);
        }

        int progress = 100 * x / c.xRes;
        cout << "\rProgress: " << progress << "%";
    }
    cout << endl;
    Timer::stop();

    string photoSavePath = Assets::photoSavePath(c.photoName);
    photo.save_image(photoSavePath);
    cout << "Photo taken and saved to: " << photoSavePath << endl;
}

void Scene::takePhotoPathTracing(const Config &c) {
    Ray::setEpsilon(c.rayEpsilon);

    cout << "Taking photo..." << endl;
    PhotoSaver photo(c.xRes, c.yRes);

    glm::vec3 origin = camera->getWorldPosition();
    cout << "Camera position: " << origin << endl;
    auto &triangles = getModel()->getTriangles();
    auto &meshes = getModel()->getMeshes();
    cout << "Triangles number: " << triangles.size() << endl;
    cout << "Resolution: " << c.xRes << " x " << c.yRes << endl;
    cout << "Samples per pixel: " << c.samplesNum << endl;
    
    Timer::start("Building accStruct");
    #ifdef USE_EMBREE
    EmbreeWrapper accStruct(meshes);
    #else
    KDTree accStruct(triangles);
    #endif
    Timer::stop();

    Timer::start("Path tracing");
    glm::vec3 leftTop = camera->getLeftTop();
    glm::vec3 leftBottom = camera->getLeftBottom();
    glm::vec3 rightTop = camera->getRightTop();
    for (int x = 0; x < c.xRes; x++) {
        for (int y = 0; y < c.yRes; y++) {
            float xShift = static_cast<float>(x) / c.xRes;
            float yShift = static_cast<float>(y) / c.yRes;
            
            glm::vec3 pos = -leftTop + glm::mix(leftTop, rightTop, xShift) +
                            glm::mix(leftTop, leftBottom, yShift);
            glm::vec3 direction = glm::normalize(pos - origin);
            Ray r(origin, direction);

            glm::vec3 color = glm::vec3(0);
            glm::vec3 emittance = glm::vec3(0);
            for(int i=0;i<c.samplesNum;i++){
                PathTracer::CastData data = PathTracer::cast(r, c.k, accStruct, lightSampler);
                glm::vec3 sampleC = data.hit ? data.emittance : c.background.asVec3(); 
                
                color += sampleC;
                emittance += data.emittance;
            }
            
            color /= c.samplesNum;
            emittance /= c.samplesNum;
             
            photo.setPixel(x, y, color);
            
            int progress = 100 * (x*c.yRes + y) / (c.xRes * c.yRes);
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
    DebugActor::get()->getModel()->clearMeshes();
    Ray::setEpsilon(c.rayEpsilon);

    auto &meshes = getModel()->getMeshes();
    EmbreeWrapper accStruct(meshes);

    glm::vec3 origin = camera->getWorldPosition();
    glm::vec3 leftTop = camera->getLeftTop();
    glm::vec3 leftBottom = camera->getLeftBottom();
    glm::vec3 rightTop = camera->getRightTop();

    glm::vec3 pos = -leftTop + glm::mix(leftTop, rightTop, 0.5f) +
                    glm::mix(leftTop, leftBottom, 0.5f);
    glm::vec3 direction = glm::normalize(pos - origin);
    Ray r(origin, direction);

    for(int i=0;i<c.samplesNum;i++){
        PathTracer::CastData data = PathTracer::cast(r, c.k, accStruct, lightSampler);
    }           

    PathTracer::drawLines = false;
}