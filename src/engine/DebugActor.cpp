#include "DebugActor.h"

using namespace std;
using namespace glm;

DebugActorPtr DebugActor::instance = nullptr;

DebugActor::DebugActor() : Actor(Model::New()) {}

DebugActorPtr DebugActor::create() {
    instance = DebugActorPtr(new DebugActor());
    return instance;
}

DebugActorPtr DebugActor::get() {
    return instance;
}

void DebugActor::drawLine(vec3 v1, vec3 v2) {
    MeshPtr mesh = Mesh::New(vector<vec3>{v1, v2});
    getModel()->add(mesh);
}
