#include "Model.h"
#include "Assets.h"

#include <algorithm>

using namespace std;
using namespace glm;

Model::Model(MeshPtr mesh) {
    add(mesh);
}

void Model::add(MeshPtr mesh) {
    auto it = find_if(meshes.begin(), meshes.end(), [&](MeshPtr m){ return &m->getMaterial() == &mesh->getMaterial();});
    if(false && it != meshes.end()){
        (*it)->merge(mesh);
    }
    else {
        meshes.push_back(mesh);
    }
    dirty = true;
}

void Model::add(ModelPtr model){
    for(auto& mesh : model->getMeshes()){
        add(mesh);
    }
}

void Model::clear() {
    meshes.clear();
    triangles.clear();
}

ModelPtr Model::copy() {
    ModelPtr myCopy = Model::New();
    for(auto& mesh : meshes) {
        myCopy->add(mesh->copy());
    }
    return myCopy;
}

void Model::apply(const mat4& m) {
    mat3 normM = Utils::calcNormM(m);
    for(auto& mesh : meshes) {
        mesh->apply(m, normM);
    }
}

// draws the model, and thus all its meshes
void Model::draw(Shader shader) {
    for (unsigned int i = 0; i < meshes.size(); i++){
        meshes[i]->draw(shader);
    }
}

void Model::matchHeight(float height) {
    auto& tris = getTriangles();
    vector<vec3> poses(tris.size() * 3);
    for(int i=0; i < tris.size(); i++) {
        auto triPoses = tris[i]->getPositions();
        for(int k=0;k<3;k++){
            poses[3*i+k]=triPoses[k];
        }
    }
    float minY = Utils::findBest(poses, Utils::Axis::Y, Utils::CmpType::MIN);
    float maxY = Utils::findBest(poses, Utils::Axis::Y, Utils::CmpType::MAX);
    float scale = height / (maxY - minY);
    apply(Utils::getScaleMat(scale)); 
}

void Model::createTriangles() {
    triangles.clear();
    for (auto &mesh : meshes) {
        auto &mTris = mesh->getTriangles();
        for (auto &tri : mTris) {
            triangles.push_back(&tri);
        }
    }
}

const vector<TrianglePtr> &Model::getTriangles() { 
    if(dirty){
        createTriangles();
        dirty = false;
    }
    return triangles; 
}
const vector<MeshPtr> &Model::getMeshes() const { return meshes; }

void Model::debug() {
    for(auto& m : meshes) {
        m->debug();
    }
}

