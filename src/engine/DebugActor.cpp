#include "DebugActor.h"

DebugActorPtr DebugActor::instance = nullptr;

DebugActor::DebugActor() : Actor(Model::New()) {}

DebugActorPtr DebugActor::create() {
    instance = DebugActorPtr(new DebugActor());
    return instance;
}

DebugActorPtr DebugActor::get() {
    return instance;
}

void DebugActor::drawLine(glm::vec3 v1, glm::vec3 v2) {
    MeshPtr mesh = Mesh::New(std::vector<Vertex>{v1, v2}, std::vector<unsigned int>{0, 1});
    getModel()->addMesh(mesh, false);
}
