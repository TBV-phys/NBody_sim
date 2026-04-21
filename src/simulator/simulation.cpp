#include "simulation.h"
#include <cmath>

//

Simulation::Simulation(double GValue, double dtValue) : G(GValue), dt(dtValue), Ek(0), Ep(0)
{}

//

void Simulation::init(std::vector<Obj> initialBodies)
{
    bodies.clear();
    
    bodies = initialBodies;
        
    computeAcc(bodies, Ep, G);
  
    // init pos_prev and trail
    for (auto& b : bodies)
    {
        b.pos_prev.x = b.pos.x - b.vel.x * dt + 0.5 * b.acc.x * dt * dt;
        b.pos_prev.y = b.pos.y - b.vel.y * dt + 0.5 * b.acc.y * dt * dt;
        
        b.trail.points[0] = {b.pos_prev.x, b.pos_prev.y};
        b.trail.points[1] = {b.pos.x, b.pos.y};
        
        Ek += 0.5 * b.mass * (b.vel.x * b.vel.x + b.vel.y * b.vel.y);
    }
    
}

//

void Simulation::step(unsigned int cont)
{
    Ek = 0;
    Ep = 0;
    
    for (auto& b : bodies) {
        verlet(b.pos_prev.x, b.pos_prev.y,
               b.pos.x, b.pos.y,
               b.vel.x, b.vel.y,
               b.acc.x, b.acc.y, dt);
        
        b.trail.points[cont % b.trail.ptsTrailMax] = {b.pos.x, b.pos.y};
        
        Ek += 0.5 * b.mass * (b.vel.x * b.vel.x + b.vel.y * b.vel.y);
    }
    
    computeAcc(bodies, Ep, G);
}
