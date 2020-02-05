#include "SkyActor.h"
#include "Assets.h"
#include "Shapes.h"

using namespace std;
using namespace glm;

SkyActor::SkyActor()
    : Actor(Model::New()),
      lightSampler(Assets::TERRAIN_CONFIG.size * sqrt(2) / 2) {}

SkyActorPtr SkyActor::create() {
    SkyActorPtr sky = SkyActorPtr(new SkyActor());
    sky->setTime(Assets::SKY_CONFIG.timeOfDay);
    return sky;
}

void SkyActor::setTime(float time) {
    lightSampler.setTime(time);
    setModel(Model::New(Shapes::genCircle(20, 10)));
    vec3 sunPos = lightSampler.getSunPos();
    getModel()->apply(Utils::getRotateGlobalMat(normalize(sunPos)));
    setPosition(sunPos);
    lightSampler.initLightSources(genFlatModel());
}

SkyLightSampler& SkyActor::getLightSampler() {
    return lightSampler;
}
