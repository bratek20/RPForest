#ifndef DIAMOND_SQUARE_TERRAIN_H
#define DIAMOND_SQUARE_TERRAIN_H

#include "Mesh.h"

class DiamondSquareTerrain {
    std::vector<std::vector<float>> heights;   
    MeshPtr mesh;

public:
    DiamondSquareTerrain(int n, float meshSize, float initHeight, float spread, float spreadReduction);

    MeshPtr getMesh() const;
    
private:
    void generateHeights(int n, float initHeight, float spread, float spreadReduction);
    void diamondStepFor(int i, int j, int step, float spread);
    void squareStepFor(int i, int j, int halfStep, int size, float spread);

    float calcRandomHeight(float spread);

    void generateMesh(float meshSize);
};

#endif