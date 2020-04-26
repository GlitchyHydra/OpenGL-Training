#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>

#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"


int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    std::cout << "Hee" << std::endl;
    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    std::cout << "Hee" << std::endl;
    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK) {
        std::cout << "error";
    }

    std::cout << glGetString(GL_VERSION) << std::endl;

    //vertex info (position)
    float positions[] = {
        -0.5f, -0.5f, //0
         0.5f, -0.5f, //1
         0.5f,  0.5f, //2
        -0.5f,  0.5f  //3
    };

    //triangle vertex indicies
    unsigned int indicies[] = {
        0, 1, 2,
        2, 3, 0
    };

    VertexArray va;
    VertexBuffer vb(positions, 4 * 2 * sizeof(float));
    VertexBufferLayout layout;
    layout.Push<float>(2);
    va.AddBuffer(vb, layout);
   
    IndexBuffer ib(indicies, 6);

    Shader shader("res/shaders/Basic.shader");
    shader.Bind();
    shader.SetUniform4f("u_Color", 0.6f, 0.3f, 0.8f, 1.0f);

    float r = 0.0f;
    float increment = 0.05f;
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
        shader.SetUniform4f("u_Color", r, 0.3f, 0.8f, 1.0f);
        va.Bind();
        ib.Bind();
        //what draw, number of indicies,type
        GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
        /* Swap front and back buffers */

        if (r >= 1.0f) increment = -0.05f;
        else if (r <= 0.0f) increment = 0.05f;
        r += increment;
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }
    glBindBuffer(GL_ARRAY_BUFFER, 0); // unbind VBO
    glBindVertexArray(0); // unbind VAO
    glfwTerminate();
    return 0;
}