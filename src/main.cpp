#include <iostream>
#define GL_SILENCE_DEPRECATION
#include <GLFW/glfw3.h>
#include <cmath>
#include <vector>

#include "simulator/simulation.h"
#include "render/draws.h"
#include "simulator/scenarios.h"


int main(void)
{
    int winWidth = 800;
    int winHeight = 800;

    float dt = 0.001;
    double G = 0.0005;
    
    
    Simulation sim(G, dt);
    sim.init(random(G, 100));
    
    double E_tot = sim.Ek + sim.Ep;
    
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(winWidth, winHeight, "3BodyProblem", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-3, 3, -3, 3, -1, 1);
    
    std::cout << "OpenGL Version: "
              << glGetString(GL_VERSION) << std::endl;

    std::cout << "GLSL Version: "
              << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;


    
    unsigned int cont = 2;
    
    /* Loop until the user closes the window */
    
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
            
        sim.step(cont);
        
        for (const auto& b : sim.bodies)
        {
            drawCircle(b.pos.x, b.pos.y, b.radius, 20, b.colorRGB);
            drawTrail(b.trail.points, cont, b.trail.ptsTrailMax, b.colorRGB);
        }
        
        /*Local relative error display*/
        std::cout << "E_tot = " << E_tot << "\t E_step = " << sim.Ek + sim.Ep << "\t loc_rel_err = " << abs((E_tot-sim.Ek - sim.Ep )/E_tot) << std::endl;
        
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
        
        cont++;
    }

    glfwTerminate();
  
    return cont;
}
