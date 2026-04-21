#include "scenarios.h"
#include <cmath>
#include <random>

// 3Body motion

std::vector<Obj> createThreeBody(double G)
{
    Obj p1, p2, p3;

    // P1
    p1.mass = 35;
    p1.radius = 0.1;
    p1.colorRGB = {1.0, 0.0, 0.0};
    p1.pos = {-0.8, 0.0};
    p1.vel = {0.0, -1.0};

    // P2
    p2.mass = 40;
    p2.radius = 0.1;
    p2.colorRGB = {1.0, 0.0, 0.0};
    p2.pos = {1.0, 0.0};
    p2.vel = {0.0, 1.0};

    // P3
    p3.mass = 0.02;
    p3.radius = 0.05;
    p3.colorRGB = {1.0, 0.0, 0.0};
    p3.pos = {0.5, 0.0};
    p3.vel = {0.0, -0.2 + sqrt(G * p2.mass / 0.4)};

    return {p1, p2, p3};
}

// 4Body motion

std::vector<Obj> createFourBody(double G)
{
    Obj p1, p2, p3, p4;

    // P1
    p1.mass = 40;
    p1.radius = 0.1;
    p1.colorRGB = {0.8, 0.3, 0.5};
    p1.pos = {-1.0, 0.0};
    p1.vel = {0.0, -1.0};

    // P2
    p2.mass = 40;
    p2.radius = 0.1;
    p2.colorRGB = {1.0, 0.7, 0.5};
    p2.pos = {1.0, 0.0};
    p2.vel = {0.0, 1.0};

    // P3
    p3.mass = 0.02;
    p3.radius = 0.05;
    p3.colorRGB = {1.0, 0.8, 0.5};
    p3.pos = {0.5, 0.0};
    p3.vel = {0.0, -0.2 + sqrt(G * p2.mass / 0.4)};

    // P4
    p4.mass = 0.02;
    p4.radius = 0.05;
    p4.colorRGB = {1.0, 0.5, 1.0};
    p4.pos = {-0.5, 0.0};
    p4.vel = {0.0, 0.2 - sqrt(G * p2.mass / 0.4)};


    return {p1, p2, p3, p4};
}

//6Body motion

std::vector<Obj> createSixBody(double G)
{
    Obj p1, p2, p3, p4, p5, p6;

    // P1
    p1.mass = 40;
    p1.radius = 0.1;
    p1.colorRGB = {1.0, 0.0, 0.0};
    p1.pos = {-1.0, 0.0};
    p1.vel = {0.0, -1.0};

    // P2
    p2.mass = 40;
    p2.radius = 0.1;
    p2.colorRGB = {1.0, 0.0, 0.0};
    p2.pos = {1.0, 0.0};
    p2.vel = {0.0, 1.0};

    // P3
    p3.mass = 0.02;
    p3.radius = 0.05;
    p3.colorRGB = {1.0, 0.0, 0.0};
    p3.pos = {0.5, 0.0};
    p3.vel = {0.0, -0.2 + sqrt(G * p2.mass / 0.4)};

    // P4
    p4.mass = 0.02;
    p4.radius = 0.05;
    p4.colorRGB = {1.0, 0.0, 0.0};
    p4.pos = {-0.5, 0.0};
    p4.vel = {0.0, 0.2 - sqrt(G * p2.mass / 0.4)};

    // P5
    p5.mass = 30;
    p5.radius = 0.1;
    p5.colorRGB = {1.0, 0.0, 0.0};
    p5.pos = {0.0, 2.0};
    p5.vel = {-2.0, 0.0};

    // P6
    p6.mass = 0.02;
    p6.radius = 0.05;
    p6.colorRGB = {1.0, 0.0, 0.0};
    p6.pos = {0.0, 1.5};
    p6.vel = {0.2 - sqrt(G * p2.mass / 0.4), 0.0};

    return {p1, p2, p3, p4, p5, p6};
}



// random number of bodies

std::mt19937 gen(std::random_device{}());

double randDouble(double min, double max)
{
    std::uniform_real_distribution <> dis(min, max);
    return dis(gen);
}

std::vector<Obj> random(double G, int N)
{
    std::vector<Obj> bodies;
    bodies.reserve(N);

    for (int i = 0; i < N; i++)
    {
        Obj b;

        // mass
        b.mass = randDouble(10., 50.0);

        // radius proportional to mass
        b.radius = 0.02 + 0.08 * (b.mass / 50.0);

        // position
        b.pos = {
            randDouble(-2.0, 2.0),
            randDouble(-2.0, 2.0)
        };

        // velocity
        b.vel = {
            randDouble(-2.0, 2.0),
            randDouble(-2.0, 2.0)
        };

        // color
        b.colorRGB = {
            (float)randDouble(0.2, 1.0),
            (float)randDouble(0.2, 1.0),
            (float)randDouble(0.2, 1.0)
        };

        bodies.push_back(b);
    }

    // set velocity of the Mass Centre to zero
    double vx_cm = 0.0, vy_cm = 0.0, M = 0.0;

    for (const auto& b : bodies) {
        vx_cm += b.mass * b.vel.x;
        vy_cm += b.mass * b.vel.y;
        M += b.mass;
    }

    vx_cm /= M;
    vy_cm /= M;

    for (auto& b : bodies) {
        b.vel.x -= vx_cm;
        b.vel.y -= vy_cm;
    }

    return bodies;
}
