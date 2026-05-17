# Modular Physics Engine for N-Body Simulation

This project builds a modular and extensible physics engine to simulate the evolution of gravitational N-body systems. It is designed to visualise complex dynamics using efficient numerical methods within a clean and adaptable codebase. The engine is based on the Verlet integration method and uses GLFW together with OpenGL for real-time visualisation.

## Features

- Real-time N-body gravitational simulation
- Energy tracking (kinetic, potential, and total energy error)
- Trail rendering for visualising trajectories
- OpenGL-based 2D rendering
- GLFW-based window and context management

## Dependencies

- OpenGL
- GLFW
- C++ compiler (C++17 or later)

## Structure

The main directory is divided into two parts. The **external** folder contains the GLFW library, which is used to handle window creation and OpenGL context management for rendering the simulation.

Rendering is implemented using the OpenGL compatibility profile (fixed-function pipeline), without the use of shaders.

The **src** folder contains the core engine and follows the structure below:

- `/core`
- `/physics`
- `/render`
- `/simulator`
- `main.cpp`

### /core

Defines the fundamental data structure representing a gravitational body in the N-body system.

### /physics

Implements the physical model of the system. The *gravity* module computes the acceleration of each body according to Newton’s law of gravitation.

The *verlet* module implements the Verlet integration method used to evolve particle trajectories under a given force (or acceleration).

### /render

Defines custom drawing functions for rendering circular bodies and their trajectory trails.

### /simulator

Implements the simulation engine. The `Simulation` class binds together the particle container and physics system, defines global parameters (such as the gravitational constant *G*, timestep, and total system energy), and provides the main interface to run simulations.

Main methods:

- `init(iNBodies)`: initialises the simulation with the given initial conditions stored in `iNBodies`.
- `step(cont)`: performs one integration step and updates the state of the entire system.

Initial conditions are defined in a separate file, `scenarios.cpp`, which contains multiple predefined configurations:

- `createThreeBody(double G)`: three-body system
- `createFourBody(double G)`: four-body system
- `createSixBody(double G)`: six-body system
- `random(double G, int N)`: random initial configuration with `N` bodies

### main.cpp

This file connects all components:

- Sets up the OpenGL window and rendering context
- Defines the `Simulation` with the chosen parameters
- Initialises the system using a selected scenario
- Advances the simulation using `step(iteration)`
- Renders the current positions of all bodies
- Renders historical trajectories

The design is modular, allowing different simulations to be executed simply by instantiating a new `Simulation` object with the desired parameters and initial conditions.

## Notes

The simulation uses the Verlet integration method with a fixed timestep.

For simplicity, rendering is performed using the OpenGL fixed-function pipeline. 

The simulation frame rate is coupled to the computation time per iteration, rather than to the *physical* time of the system.
