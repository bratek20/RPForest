

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
    bool dirty = false;

  public:
    Model() = default;
    Model(MeshPtr mesh);

    void add(MeshPtr mesh);
    void add(ModelPtr model);
    void clear();

    ModelPtr copy();
    
    void apply(const glm::mat4& m);
    
    void draw(Shader shader);

    void matchHeight(float height);
    
    const std::vector<TrianglePtr> &getTriangles();
    const std::vector<MeshPtr> &getMeshes() const;

    void debug();

  private:
    void createTriangles();
};
#endif
