

#ifndef MODEL_H
#define MODEL_H

#include "Config.h"
#include "Mesh.h"
#include "Shader.h"

#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

class Model;
using ModelPtr = std::shared_ptr<Model>;

class Model : public Ptr<Model, ModelPtr> {
    std::vector<Material> materials;
    std::vector<MeshPtr> meshes;
    std::vector<TrianglePtr> triangles;
    std::vector<LightConfig> lights;

  public:
    Model() = default;
    Model(const Config &c);

    void addMesh(MeshPtr mesh, bool rebuild);
    void clearMeshes();

    void apply(const glm::mat4& m);
    
    void draw(Shader shader);
    const std::vector<TrianglePtr> &getTriangles() const;
    const std::vector<LightConfig> &getLights() const;
    const std::vector<MeshPtr> &getMeshes() const;

    void debug();

  private:
    void createTriangles();
};
#endif
