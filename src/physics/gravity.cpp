#include "gravity.h"
#include <cmath>

void computeAcc(std::vector<Obj>& bodies, double& Epot, double G)
{
    for (auto& b : bodies) {
        b.acc = {0.0, 0.0};
    }
    
    for (size_t i = 0; i < bodies.size(); ++i) {
        for (size_t j = i + 1; j < bodies.size(); ++j) {

            double dx = bodies[j].pos.x - bodies[i].pos.x;
            double dy = bodies[j].pos.y - bodies[i].pos.y;

            double dist = sqrt(dx*dx + dy*dy);
            double invDist3 = 1.0 / (dist * dist * dist);
            
            Epot -= G * bodies[i].mass * bodies[j].mass / dist;

            double f = bodies[j].mass * invDist3;

            bodies[i].acc.x += G * f * dx;
            bodies[i].acc.y += G * f * dy;

            bodies[j].acc.x -= G * bodies[i].mass * invDist3 * dx;
            bodies[j].acc.y -= G * bodies[i].mass * invDist3 * dy;
        }
    }
    
}
