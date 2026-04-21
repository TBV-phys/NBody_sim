#pragma once
#include "../core/body.h"

void drawCircle(float cx, float cy, float r, int segments, const std::array<float,3>& colorRGB);

void drawTrail(const std::vector<Vec2>& trail, const int& cont, const int& ptsColaMax, const std::array<float,3>& colorRGB);
