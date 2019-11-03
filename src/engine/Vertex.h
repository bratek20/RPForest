

#ifndef VERTEX_H
#define VERTEX_H

#include <glm/glm.hpp>

struct Vertex {
    static const glm::vec3 NORMAL_NOT_SET;

    glm::vec3 position;
    glm::vec3 normal;

    Vertex() = default;
    Vertex(glm::vec3 position);
    Vertex(glm::vec3 position, glm::vec3 normal);

    void apply(const glm::mat4& m);
    bool hasNormal() const;

    void debug();
};


#endif

