#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "Renderer.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Texture.h"
#include "Shader.h"
#include "Camera.h"
#include "Plane.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

void APIENTRY debugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam);

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, 1);

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

    glEnable(GL_DEBUG_OUTPUT);
    //glEnable(GL_TEXTURE_2D);
    glDebugMessageCallback(debugCallback, 0);

    {
        float positions[16] = {
            //Verticies    //TexCoords
             050.0f,  050.0f,  1.0f,  1.0f,   // 0 top right
            -050.0f,  050.0f,  0.0f,  1.0f,   // 1 top left
            -050.0f, -050.0f,  0.0f,  0.0f,   // 2 bot left
             050.0f, -050.0f,  1.0f,  0.0f,   // 3 bot right
        };


        unsigned int indices[] = {
            0, 1, 2,
            0, 2, 3,
        };

        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        VertexArray va;
        va.Bind();

        // VertexBuffer vb(positions, 6 * 6 * sizeof(float));
        VertexBuffer vb(positions, 4 * 4 * sizeof(float));
        vb.Bind();
        IndexBuffer ib(indices, 6);
        ib.Bind();

        VertexBufferLayout layout;
        layout.Push<float>(2);
        layout.Push<float>(2);
        // layout.Push<float>(3);

        va.AddBuffer(vb, layout);

        Shader shader("res/shaders/test.shader");
        shader.Bind();

        Texture texture("res/textures/PogO.png");
        texture.Bind();
        shader.SetUniform1i("u_Texture", 0);

        shader.SetUniform4f("u_Color", .0f, .0f, .5f, 1.f);

        Renderer renderer;

        va.Unbind();
        vb.Unbind();
        ib.Unbind();
        shader.Unbind();

        glEnable(GL_DEPTH_TEST);
        glPatchParameteri(GL_PATCH_VERTICES, 4);

        // Variables that help the rotation
        float rotation = 0.0f;
        double prevTime = glfwGetTime();

        Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));

        while (!glfwWindowShouldClose(window))
        {
            glClearColor(.0f, .0f, .0f, 1.f);
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
            camera.Matrix(45.0f, 0.1f, 100.0f, shader, "camMatrix", 0);

             renderer.Draw(va, ib, shader);
            // glDrawElements(GL_PATCHES, ib.GetCount(), GL_UNSIGNED_INT, 0);
            // 20 = rez = resolution value found in Plane.cpp
            //glDrawArrays(GL_PATCHES, 0, 4 * 20 * 20);

            glfwSwapBuffers(window);
            glfwPollEvents();
        }
    }

    glfwTerminate();
    return 0;
}

void APIENTRY debugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {
    // Log or print the debug message details
    // Example: Print the message to stderr
    std::cerr << "OpenGL debug message: " << message << std::endl;
}
