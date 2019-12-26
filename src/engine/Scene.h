#ifndef SCENE_H
#define SCENE_H

#include "Camera.h"
#include "Light.h"
#include "Config.h"
#include "SkyLightSampler.h"
#include "DiamondSquareTerrain.h"
#include "Spawner.h"
#include "SkyActor.h"

class Scene;
using ScenePtr = std::shared_ptr<Scene>;

class Scene : public Actor {
    CameraPtr camera;
    SkyActorPtr sky;
    DiamondSquareTerrain terrain;
    Spawner treesSpawner;
    Spawner plantsSpawner;

public:
    static ScenePtr create(const Config& c);
    void render();

    CameraPtr getCamera() const;
    void takePhotoPathTracing(const Config& c);
    void debugRay(const Config& c);

protected:
    Scene(ModelPtr sceneModel, float size);

private:
    void spawn(Spawner& spawner, int elems);
};
#endif