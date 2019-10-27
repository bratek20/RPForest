

#ifndef MODEL_H
#define MODEL_H

#include "Mesh.h"
#include "Shader.h"
#include "Config.h"
#include "Texture.h"

#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

class Model;
using ModelPtr = std::shared_ptr<Model>;

class Model {
    std::vector<TexturePtr> textures;
    std::vector<Material> materials;
    std::vector<Mesh> meshes;
    std::vector<TrianglePtr> triangles;
    std::vector<LightConfig> lights;
    std::string directory;

  public:
    static ModelPtr create(const Config& c);
    static ModelPtr createEmpty();

    void addMesh(const Mesh& mesh, bool rebuild);
    void clearMeshes();
    
    void draw(Shader shader);
    const std::vector<TrianglePtr> &getTriangles() const;
    const std::vector<LightConfig> &getLights() const;
    const std::vector<Mesh> &getMeshes() const;

  private:
    Model() = default;
    Model(const Config& c);
    bool loadModel(const std::string &path);
    void processNode(aiNode *node, const aiScene *scene);
    Mesh processMesh(aiMesh *mesh, const aiScene *scene);
    void createTriangles();

    std::vector<TexturePtr> loadMaterialTextures(aiMaterial *mat, aiTextureType type,
                                         std::string typeName);
    Material getMaterial(const aiScene *scene, unsigned int idx);
};
#endif
