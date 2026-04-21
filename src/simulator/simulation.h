#pragma once
#include <vector>
#include "../core/body.h"
#include "../physics/gravity.h"
#include "../physics/verlet.h"

class Simulation {
public:
    std::vector<Obj> bodies;
    double G, dt, Ek, Ep;

    Simulation(double G, double dt);

    void init(std::vector<Obj> initialBodies);                  // starts nbodies
    void step(unsigned int cont);                               // integration step
};
