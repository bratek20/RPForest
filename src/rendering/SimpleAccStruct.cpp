#include "SimpleAccStruct.h"
#include "Utils.h"

using namespace std;

SimpleAccStruct::SimpleAccStruct(const vector<TrianglePtr>& triangles) : TrianglesAccStruct(triangles) {}

HitData SimpleAccStruct::cast(Ray r, float maxDistance){
    HitData ans;
    ans.distance = Utils::INF;
    
    for (auto tri : triangles) {
        HitData data = intersect(r, tri);
        if (data.intersects() && data.distance < ans.distance && data.distance > 0 && data.distance < maxDistance) {
            ans = data;
        }
    }
    return ans;
}