

#include "Mesh.h"
#include "Utils.h"
#include "Globals.h"

#include <iostream>

using namespace std;

const glm::vec3 Vertex::NORMAL_NOT_SET = glm::vec3(0);
const glm::vec2 Vertex::UV_NOT_SET = glm::vec2(-4, -2);

Vertex::Vertex(aiMesh *mesh, int idx) {
    position = toVec3(mesh->mVertices, idx, glm::vec3(0));
    normal = toVec3(mesh->mNormals, idx, NORMAL_NOT_SET);
    uv = toVec2(mesh->mTextureCoords[0], idx, UV_NOT_SET);
}

Vertex::Vertex(glm::vec3 position) {
    this->position = position;
    normal = NORMAL_NOT_SET;
    uv = UV_NOT_SET;
}

glm::vec3 Vertex::toVec3(aiVector3D *vectors, int idx, glm::vec3 defaultVec) {
    if (vectors != NULL) {
        return glm::vec3(vectors[idx].x, vectors[idx].y, vectors[idx].z);
    }
    return defaultVec;
}

glm::vec2 Vertex::toVec2(aiVector3D *vectors, int idx, glm::vec2 defaultVec) {
    if (vectors != NULL) {
        return glm::vec2(vectors[idx].x, vectors[idx].y);
    }
    return defaultVec;
}

bool Vertex::hasNormal() const { return normal != NORMAL_NOT_SET; }
bool Vertex::hasUV() const { return uv != UV_NOT_SET;}

const glm::vec3 Bounds::MIN_NOT_SET = glm::vec3(Utils::INF);;
const glm::vec3 Bounds::MAX_NOT_SET = glm::vec3(-Utils::INF);

Bounds::Bounds()
    : pMin(MIN_NOT_SET),
      pMax(MAX_NOT_SET) {}

Bounds::Bounds(const vector<glm::vec3> &poses) {
    for (auto axis : Utils::AXES) {
        float minVal = Utils::findBest(poses, axis, Utils::CmpType::MIN);
        float maxVal = Utils::findBest(poses, axis, Utils::CmpType::MAX);
        pMin[axis] = minVal;
        pMax[axis] = maxVal;
    }
}

Bounds Bounds::merge(const Bounds &other) const {
    vector<glm::vec3> poses;
    if(this->isValid()){
        poses.push_back(pMin);
        poses.push_back(pMax);
    }
    if(other.isValid()){
        poses.push_back(other.pMin);
        poses.push_back(other.pMax);
    }
    return Bounds(poses);
}

pair<Bounds, Bounds> Bounds::split(Utils::Axis axis, float value) const {
    pair<Bounds, Bounds> ans = {*this, *this};
    ans.first.pMax[axis] = ans.second.pMin[axis] = value;
    return ans; 
}

bool Bounds::isValid() const {
    return pMin != MIN_NOT_SET && pMax != MAX_NOT_SET;
}

glm::vec3 Bounds::diagonal() const { return pMax - pMin; }

float Bounds::surfaceArea() const {
    glm::vec3 d = diagonal();
    return 2 * (d.x * d.y + d.x * d.z + d.y * d.z);
}

Utils::Axis Bounds::maximumExtent() const {
    glm::vec3 d = diagonal();
    if (d.x > d.y && d.x > d.z) {
        return Utils::Axis::X;
    }

    else if (d.y > d.z) {
        return Utils::Axis::Y;
    }

    else {
        return Utils::Axis::Z;
    }
}

Triangle::Triangle(Vertex& v1, Vertex& v2, Vertex& v3)    
    : v1(v1), v2(v2), v3(v3) {
    static int nextId = 1;
    id = nextId++;
    auto poses = getPositions();
    bounds = Bounds(poses);
}

Triangle::Triangle(Vertex &v1, Vertex &v2, Vertex &v3, const Material &mat)
    : Triangle(v1, v2, v3) {
    this->mat = mat;
}

float Triangle::calcArea() const {
    return cross(getEdge12(), getEdge13()).length() / 2;
}

bool Triangle::isInside(glm::vec3 point) const{
    float area = calcArea();
    float alpha = cross(v2.position - point, v3.position - point).length() / (2 * area);
    float beta = cross(v3.position - point, v1.position - point).length() / (2 * area);
    float gamma = 1 - alpha - beta;
    
    static auto check = [](float value){
        return value >= 0 && value <= 1;
    };
    return check(alpha) && check(beta) && check(gamma); 
}

glm::vec3 Triangle::getEdge12() const{
    return v2.position - v1.position;
}

glm::vec3 Triangle::getEdge13() const{
    return v3.position - v1.position;
}

glm::vec3 Triangle::getNormal(glm::vec2 baryPos) const {
    if (v1.hasNormal() && v2.hasNormal() && v3.hasNormal()) {
        return (1 - baryPos.x - baryPos.y) * v1.normal + baryPos.x * v2.normal +
               baryPos.y * v3.normal;
    } else {
        return getNormal();
    }
}

glm::vec2 Triangle::getUV(glm::vec2 baryPos) const {
    if (v1.hasUV() && v2.hasUV() && v3.hasUV()) {
        return (1 - baryPos.x - baryPos.y) * v1.uv + baryPos.x * v2.uv +
               baryPos.y * v3.uv;
    } else {
        return glm::vec2(0);
    }
}

glm::vec3 Triangle::getNormal() const {
    return glm::normalize(
        glm::cross(v2.position - v1.position, v3.position - v1.position));
}

vector<glm::vec3> Triangle::getPositions() const {
    return {v1.position, v2.position, v3.position};
}

Bounds Triangle::getBounds() const {
    return bounds;
}

glm::vec3 Triangle::getCenter() const {
    return (v1.position + v2.position + v3.position) / 3.0f;
}

Mesh::Mesh(vector<Vertex> vertices, vector<unsigned int> indices, const Material &material)
    : vertices(move(vertices)), indices(move(indices)),
      material(material){
    // now that we have all the required data, set the vertex buffers and its
    // attribute pointers.
    setupMesh();
}

void Mesh::draw(Shader &shader) {
    material.apply(shader);

    // draw mesh
    glBindVertexArray(VAO);
    if(indices.size() < 3){
        glDrawElements(GL_LINES, indices.size(), GL_UNSIGNED_INT, 0);
    }
    else {
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    }
    glBindVertexArray(0);

    // always good practice to set everything back to defaults once configured.
    glActiveTexture(GL_TEXTURE0);
}
void Mesh::setupMesh() {
    triangles.clear();
    if(indices.size() > 2) {
        for (unsigned i = 0; i < indices.size(); i += 3) {
            triangles.emplace_back(vertices[indices[i]], vertices[indices[i + 1]],
                                    vertices[indices[i + 2]], material);
        }
    }

    if(!Globals::debug){
        return;
    }
    // create buffers/arrays
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    // load data into vertex buffers
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // A great thing about structs is that their memory layout is sequential for
    // all its items. The effect is that we can simply pass a pointer to the
    // struct and it translates perfectly to a glm::vec3/2 array which again
    // translates to 3/2 floats which translates to a byte array.
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex),
                 &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int),
                 &indices[0], GL_STATIC_DRAW);

    // set the vertex attribute pointers
    // vertex Positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)0);
    // vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          (void *)offsetof(Vertex, normal));

    // vertex texture coords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          (void *)offsetof(Vertex, uv));
    // // vertex tangent
    // glEnableVertexAttribArray(3);
    // glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
    // (void*)offsetof(Vertex, tangent));
    // // vertex bitangent
    // glEnableVertexAttribArray(4);
    // glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
    // (void*)offsetof(Vertex, bitangent));

    glBindVertexArray(0);
}

const vector<Triangle> &Mesh::getTriangles() const { return triangles; }

TrianglePtr Mesh::getTriangle(int idx) const{
    return &triangles[idx];
}
