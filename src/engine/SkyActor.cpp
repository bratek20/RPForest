#include "SkyActor.h"
#include "Assets.h"
#include "Shapes.h"

using namespace std;
using namespace glm;

SkyActor::SkyActor()
    : Actor(Model::New(Shapes::genCircle(20, 10))),
      lightSampler(Assets::TERRAIN_CONFIG.size * sqrt(2) / 2) {}

SkyActorPtr SkyActor::create() {
    SkyActorPtr sky = SkyActorPtr(new SkyActor());
    vec3 sunPos = sky->lightSampler.getSunPos();
    sky->getModel()->apply(Utils::getRotateGlobalMat(normalize(sunPos)));
    sky->setPosition(sunPos);
    sky->lightSampler.initLightSources(sky->genFlatModel());
    return sky;
}

SkyLightSampler& SkyActor::getLightSampler() {
    return lightSampler;
}
