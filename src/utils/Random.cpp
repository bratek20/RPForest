#include "Random.h"
#include "Mesh.h"
#include "Utils.h"

std::default_random_engine Random::generator;

float Random::uniform(float a, float b){
    std::uniform_real_distribution<double> distribution(a, b);
    return distribution(generator);
}

bool Random::tossCoin(float winProbability){
    return uniform() < winProbability;
}

glm::vec3 Random::vectorOnHemisphereUniform(glm::vec3 normal){
    float theta = acos(1 - uniform());
    float phi = uniform(0, 2 * M_PI);
    float x = sin(theta) * cos(phi);
    float y = sin(theta) * sin(phi);
    float z = cos(theta);
    return Utils::rotateGlobal(glm::vec3(x, y, z), normal);
}

glm::vec3 Random::vectorOnHemisphereCos(glm::vec3 normal){
    float x, z;
    do{
        x = uniform(-1, 1);
        z = uniform(-1, 1);
    }while(x*x + z*z > 1);

    float y = sqrt(1-x*x-z*z);
    return Utils::rotateGlobal(glm::vec3(x, y, z), normal);
}

glm::vec3 Random::pointInTriangle(TrianglePtr triangle){
    float a,b;
    do{
        a = uniform();
        b = uniform();
    } while(a + b > 1);

    return triangle->v1.position * a + triangle->v2.position * b  + triangle->v3.position * (1-a-b); 
}
