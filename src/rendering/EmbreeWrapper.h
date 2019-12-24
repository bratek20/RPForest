#ifndef EMBREE_WRAPPER_H
#define EMBREE_WRAPPER_H

#include "AccStruct.h"
#include "Mesh.h"

#include <vector>
#include <embree3/rtcore.h>

class EmbreeWrapper : public AccStruct {
    std::vector<MeshPtr> meshes;

    RTCDevice device;
    RTCScene scene;

public:
    EmbreeWrapper(){}
    EmbreeWrapper(const std::vector<MeshPtr>& meshes);
    ~EmbreeWrapper() override;

    void init(const std::vector<MeshPtr>& meshes);
    HitData cast(Ray r, float maxDistance = Utils::INF) override;

private:
    void createMeshGeometry(MeshPtr mesh);
};

#endif