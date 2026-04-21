#pragma once
#include <vector>
#include <array>

struct Vec2 {
    double x, y;
};

struct Trail {
    int ptsTrailMax;
    std::vector<Vec2> points;

    Trail(int max = 1000)
        : ptsTrailMax(max), points(max) {}
};

struct Obj {
    double mass, radius;
    Vec2 pos, pos_prev, vel, acc;
    std::array<float,3> colorRGB;
    Trail trail;
};
