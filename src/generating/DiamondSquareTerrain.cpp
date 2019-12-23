#include "DiamondSquareTerrain.h"
#include "Random.h"

using namespace std;

DiamondSquareTerrain::DiamondSquareTerrain(int n,
                                           float meshSize,
                                           float spread,
                                           float spreadReduction) {
    generateHeights(n, spread, spreadReduction);
    generateMesh(meshSize);
}

MeshPtr DiamondSquareTerrain::getMesh() const {
    return mesh;
}

void DiamondSquareTerrain::generateHeights(int n,
                                           float spread,
                                           float spreadReduction) {
    int size = (1 << n) + 1;
    heights.resize(size, vector<float>(size));
    heights[0][0] = calcRandomHeight(spread);
    heights[size - 1][0] = calcRandomHeight(spread);
    heights[0][size - 1] = calcRandomHeight(spread);
    heights[size - 1][size - 1] = calcRandomHeight(spread);

    for (int step = 1 << n; step > 1; step /= 2) {
        spread *= spreadReduction;

        for (int i = 0; i + step < size; i += step) {
            for (int j = 0; j + step < size; j += step) {
                diamondStepFor(i, j, step, spread);
            }
        }

        for (int i = 0; i + step < size; i += step / 2) {
            int j = i % step == 0 ? step / 2 : 0;
            for (; j + step < size; j += step) {
                squareStepFor(i, j, step / 2, size, spread);
            }
        }
    }
}

float DiamondSquareTerrain::calcRandomHeight(float spread) {
    return Random::uniform(-spread, spread);
}

void DiamondSquareTerrain::diamondStepFor(int i,
                                          int j,
                                          int step,
                                          float spread) {
    float height = 0;
    for (int ki = 0; ki <= 1; ki++) {
        for (int kj = 0; kj <= 1; kj++) {
            height += heights[i + ki * step][j + kj * step];
        }
    }
    heights[i + step / 2][j + step / 2] = height / 4 + calcRandomHeight(spread);
}

void DiamondSquareTerrain::squareStepFor(int i,
                                         int j,
                                         int halfStep,
                                         int size,
                                         float spread) {
    static int di[] = {1, -1, 0, 0};
    static int dj[] = {0, 0, 1, -1};
    auto checkRange = [size](int x) { return x >= 0 && x < size; };

    float height = 0;
    int num = 0;
    for (int k = 0; k < 4; k++) {
        int ni = i + di[k] * halfStep;
        int nj = j + dj[k] * halfStep;
        if (checkRange(ni) && checkRange(nj)) {
            height += heights[ni][nj];
            num++;
        }
    }
    heights[i][j] = height / num + calcRandomHeight(spread);
}

void DiamondSquareTerrain::generateMesh(float meshSize) {
    int size = heights.size();
    float x = -meshSize / 2;
    float y = x;
    float step = meshSize / (size - 1);

    vector<Vertex> vertices;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            vertices.push_back(
                Vertex({x + step * i, heights[i][j], y + step * j}));
        }
    }

    vector<unsigned int> indices;
    auto calcIdx = [size](int i, int j) {return i*size + j; };
    for (int i = 1; i < size; i++) {
        for (int j = 0; j + 1 < size; j++) {
            indices.push_back(calcIdx(i, j));
            indices.push_back(calcIdx(i-1, j));
            indices.push_back(calcIdx(i-1, j+1));

            indices.push_back(calcIdx(i, j));
            indices.push_back(calcIdx(i-1, j+1));
            indices.push_back(calcIdx(i, j+1));
        }
    }

    mesh = Mesh::New(vertices, indices, true, Materials::GROUND);
}