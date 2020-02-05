#ifndef SKY_ACTOR_H
#define SKY_ACTOR_H

#include "Actor.h"
#include "SkyLightSampler.h"

class SkyActor;
using SkyActorPtr = std::shared_ptr<SkyActor>;

class SkyActor : public Actor {
    SkyLightSampler lightSampler;
public:
    static SkyActorPtr create();
    
    void setTime(float time);
    SkyLightSampler& getLightSampler();

protected:
    SkyActor();
};
#endif