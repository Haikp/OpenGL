#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <sstream>

#include "Renderer.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Texture.h"
#include "Shader.h"
#include "Camera.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  

    static int width = 800;
    static int height = 800;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(width, height, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }


    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    //syncs up window swapping with monitor refresh rate
    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK)
    {
        std::cout << "Error glewInit()" << std::endl;
    }

    std::cout << glGetString(GL_VERSION) << std::endl;

    {
        float positions[] =
        {
            -0.5f, 0.0f,  0.5f,     1.00f, 0.70f, 0.44f,	0.0f, 0.0f,
            -0.5f, 0.0f, -0.5f,     0.83f, 1.00f, 0.44f,	5.0f, 0.0f,
             0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 1.00f,	0.0f, 0.0f,
             0.5f, 0.0f,  0.5f,     1.00f, 1.00f, 0.44f,	5.0f, 0.0f,
             0.0f, 0.8f,  0.0f,     1.00f, 0.86f, 1.00f,	2.5f, 5.0f
        };

        unsigned int indicies[18] =
        {
            0, 1, 2,
            0, 2, 3,
            0, 1, 4,
            1, 2, 4,
            2, 3, 4,
            3, 0, 4
        };

        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        VertexArray va;
        va.Bind();

        VertexBuffer vb(positions, 5 * 8 * sizeof(float));
        vb.Bind();
        IndexBuffer ib(indicies, 18);
        ib.Bind();

        VertexBufferLayout layout;
        layout.Push<float>(3);
        layout.Push<float>(3);
        layout.Push<float>(2);

        va.AddBuffer(vb, layout);

        Shader shader("res/shaders/Basic.shader");
        shader.Bind();

        Renderer renderer;

        va.Unbind();
        vb.Unbind();
        ib.Unbind();
        shader.Unbind();

        glEnable(GL_DEPTH_TEST);

        // Variables that help the rotation of the pyramid
        float rotation = 0.0f;
        double prevTime = glfwGetTime();

        Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));

        while (!glfwWindowShouldClose(window))
        {
            glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            double crntTime = glfwGetTime();
            if (crntTime - prevTime >= 1 / 60)
            {
                rotation += 0.5f;
                prevTime = crntTime;
            }

            shader.Bind();
            va.Bind();

            camera.Inputs(window);
            camera.Matrix(45.0f, 0.1f, 100.0f, shader, "camMatrix", rotation);

            renderer.Draw(va, ib, shader);

            glfwSwapBuffers(window);
            glfwPollEvents();
        }
    }

    glfwTerminate();
    return 0;
}
