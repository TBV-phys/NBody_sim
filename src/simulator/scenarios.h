#pragma once
#include <vector>
#include "../core/body.h"

std::vector<Obj> createThreeBody(double G);
std::vector<Obj> createFourBody(double G);
std::vector<Obj> createSixBody(double G);
std::vector<Obj> random(double G, int N);
