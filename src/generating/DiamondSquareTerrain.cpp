#include "DiamondSquareTerrain.h"
#include "Assets.h"
#include "Random.h"

#include <algorithm>

using namespace std;
using namespace glm;

DiamondSquareTerrain::DiamondSquareTerrain() {
    generateHeights(Assets::TERRAIN_CONFIG.n, Assets::TERRAIN_CONFIG.initHeight,
                    Assets::TERRAIN_CONFIG.spread,
                    Assets::TERRAIN_CONFIG.spreadReductionRate);
    generateMesh(Assets::TERRAIN_CONFIG.size);
    heightSampler.init({mesh});
}

MeshPtr DiamondSquareTerrain::getMesh() const {
    return mesh;
}

float DiamondSquareTerrain::calcHeight(float x, float z) {
    static const float MAX_HEIGHT = 1e4;
    Ray r({x, MAX_HEIGHT, z}, {0, -1, 0});
    HitData hit = heightSampler.cast(r);
    return hit.pos.y;
}

vec3 DiamondSquareTerrain::calcBestCameraPos() {
    float size = Assets::TERRAIN_CONFIG.size;
    const CameraConfig& conf = Assets::CAMERA_CONFIG;
    
    auto checkOffset = [&](float val) {
        return size / 2 - abs(val) > conf.edgeMinOffset;
    };

    vec3 ans = vec3(0);
    float error = Utils::INF;
    for (auto& v : mesh->getVertices()){
        auto& pos = v.position;
        if(!checkOffset(pos.x) || !checkOffset(pos.z)) {
            continue;
        }
        
        float heightError = abs(pos.y - conf.expectedPositionY);
        if(heightError < error) {
            error = heightError;
            ans = pos;
        }
    } 
    return ans;
}

void DiamondSquareTerrain::generateHeights(int n,
                                           float initHeight,
                                           float spread,
                                           float spreadReductionRate) {
    int size = (1 << n) + 1;
    heights.resize(size, vector<float>(size));
    heights[0][0] = calcRandomHeight(initHeight);
    heights[size - 1][0] = calcRandomHeight(initHeight);
    heights[0][size - 1] = calcRandomHeight(initHeight);
    heights[size - 1][size - 1] = calcRandomHeight(initHeight);

    for (int step = 1 << n; step > 1; step /= 2) {
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
        spread *= spreadReductionRate;
    }

    float minHeight = Utils::INF;
    for(auto& heightsRow : heights) {
        for(float height : heightsRow) {
            minHeight = std::min(minHeight, height);
        }
    }
    for(auto& heightsRow : heights) {
        for(auto& height : heightsRow) {
            height -= minHeight;
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
    float height = calcRandomHeight(spread);
    for (int ki = 0; ki <= 1; ki++) {
        for (int kj = 0; kj <= 1; kj++) {
            height += heights[i + ki * step][j + kj * step];
        }
    }
    heights[i + step / 2][j + step / 2] = height / 4;
}

void DiamondSquareTerrain::squareStepFor(int i,
                                         int j,
                                         int halfStep,
                                         int size,
                                         float spread) {
    static int di[] = {1, -1, 0, 0};
    static int dj[] = {0, 0, 1, -1};
    auto checkRange = [size](int x) { return x >= 0 && x < size; };

    float height = calcRandomHeight(spread);
    int num = 0;
    for (int k = 0; k < 4; k++) {
        int ni = i + di[k] * halfStep;
        int nj = j + dj[k] * halfStep;
        if (checkRange(ni) && checkRange(nj)) {
            height += heights[ni][nj];
            num++;
        }
    }
    heights[i][j] = height / num;
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
    auto calcIdx = [size](int i, int j) { return i * size + j; };
    for (int i = 1; i < size; i++) {
        for (int j = 0; j + 1 < size; j++) {
            indices.push_back(calcIdx(i, j));
            indices.push_back(calcIdx(i - 1, j));
            indices.push_back(calcIdx(i - 1, j + 1));

            indices.push_back(calcIdx(i, j));
            indices.push_back(calcIdx(i - 1, j + 1));
            indices.push_back(calcIdx(i, j + 1));
        }
    }

    mesh = Mesh::New(vertices, indices, true, Materials::TERRAIN);
}