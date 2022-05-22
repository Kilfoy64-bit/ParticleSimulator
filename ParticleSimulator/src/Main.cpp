#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <chrono>

#include "SimulationSystem/Simulator/Simulator.h"
#include "PhysicsEngine/RandomNumberGenerator/RandomNumberGenerator.h"

RandomNumberGenerator RandomNumberGenerator::s_Instance;

long getTimeMS()
{
    auto now = std::chrono::system_clock::now();
    auto now_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(now);
    auto epoch = now_ms.time_since_epoch();
    auto value = std::chrono::duration_cast<std::chrono::milliseconds>(epoch);
    long duration = value.count();
    return duration;
}

int main(void)
{
    const int SCREEN_WIDTH = 1920;
    const int SCREEN_HEIGHT = 1080;
    const char* SCREEN_TITLE = "Particle Simulator";

    GLFWwindow* window;

    {
        /* Initialize the library */
        if (!glfwInit())
            return -1;

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        /* Create a windowed mode window and its OpenGL context */
        window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE, NULL, NULL);
        if (!window)
        {
            glfwTerminate();
            return -1;
        }

        /* Make the window's context current */
        glfwMakeContextCurrent(window);

        glfwSwapInterval(0);

        if (glewInit() != GLEW_OK)
        {
            std::cout << "Error!" << std::endl;
        }

        std::cout << glGetString(GL_VERSION) << std::endl;

        Simulator simulator(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE);

        long newTime = getTimeMS();
        long oldTime;
        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            oldTime = newTime;
            newTime = getTimeMS();

            /* Render here */
            simulator.playStep(newTime - oldTime);

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }
    }


    glfwTerminate();
    return 0;
}