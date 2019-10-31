#include "Model.h"
#include "Assets.h"

using namespace std;

ModelPtr Model::create(const Config& c) {
    return ModelPtr(new Model(c));
}

ModelPtr Model::createEmpty() {
    return ModelPtr(new Model());
}

Model::Model(const Config& c) {
    for(auto& lc : c.lights) {
        meshes.push_back(lc.createMesh());
    }
    createTriangles();
}

void Model::addMesh(const Mesh& mesh, bool rebuild) {
    meshes.push_back(mesh);
    if(rebuild) {
        createTriangles();
    }
}

void Model::clearMeshes() {
    meshes.clear();
}


// draws the model, and thus all its meshes
void Model::draw(Shader shader) {
    for (unsigned int i = 0; i < meshes.size(); i++){
        meshes[i].draw(shader);
    }
}

void Model::createTriangles() {
    triangles.clear();
    for (auto &mesh : meshes) {
        auto &mTris = mesh.getTriangles();
        for (auto &tri : mTris) {
            triangles.push_back(&tri);
        }
    }
}

const vector<TrianglePtr> &Model::getTriangles() const { return triangles; }
const vector<LightConfig> &Model::getLights() const { return lights; }
const vector<Mesh> &Model::getMeshes() const { return meshes; }

