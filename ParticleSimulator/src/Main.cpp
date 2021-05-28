#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <vector>

#include "Renderer.h"
#include "Shader.h"
#include "Texture.h"

#include "Entity.h"
#include "Rect.h"
#include "Particle.h"

int main(void)
{
    GLFWwindow* window;

    {
        /* Initialize the library */
        if (!glfwInit())
            return -1;

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        /* Create a windowed mode window and its OpenGL context */
        window = glfwCreateWindow(1920, 1080, "Hello World", NULL, NULL);
        if (!window)
        {
            glfwTerminate();
            return -1;
        }

        /* Make the window's context current */
        glfwMakeContextCurrent(window);

        glfwSwapInterval(1);

        if (glewInit() != GLEW_OK) {
            std::cout << "Error!" << std::endl;
        }

        std::cout << glGetString(GL_VERSION) << std::endl;

        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        Renderer renderer;
        Shader shader("res/shaders/Basic.shader");

        std::vector<Entity*> entities;
        
        for (int i = 75; i < 1920; i+=100) {
            /*Entity* rectEntity = new Rect({ 0.0f + i, 1080.0f }, 75);            
            entities.push_back(rectEntity);*/
            Entity* particleEntity = new Particle({ 0.0f + i }, 50);
            entities.push_back(particleEntity);
        }

        /*Rect rect1(renderer, {150.0f, 150.0f}, 175, 100);
        Rect rect2(renderer, {700.0f, 400.0f}, 200);

        Entity* entityRect1 = &rect1;
        Entity* entityRect2 = &rect2;

        entities.push_back(entityRect1);
        entities.push_back(entityRect2);*/

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
            renderer.Clear();

            for (unsigned int i = 0; i < entities.size(); i++) {
                entities[i]->Move(Direction::Down);
                entities[i]->Render(renderer, shader);
            }

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }
    }
    glfwTerminate();
    return 0;
}