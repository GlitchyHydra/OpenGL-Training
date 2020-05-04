#include "OpenGL_config.h"

#include <iostream>

namespace My_OpenGL {

    void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
    {
        // Когда пользователь нажимает ESC, мы устанавливаем свойство WindowShouldClose в true, 
        // и приложение после этого закроется
        /*if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
            glfwSetWindowShouldClose(window, GL_TRUE);*/

        if (action == GLFW_PRESS)
            scene.camera.OnKeyboard(key);
    }

    void mouse_callback(GLFWwindow* window, double xpos, double ypos)
    {
        scene.camera.OnMouse(xpos, ypos);
    }

    Config::Config()
    {
        const char* glsl_version = "#version 150";

        /* Initialize the library */
        if (!glfwInit())
            throw;

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        /* Create a windowed mode window and its OpenGL context */
        window = glfwCreateWindow(1920, 1080, "Renderer Training", NULL, NULL);
        if (!window)
        {
            glfwTerminate();
            throw;
        }

        /* Make the window's context current */
        glfwMakeContextCurrent(window);
        //vsync on
        glfwSwapInterval(1);

        if (glewInit() != GLEW_OK) {
            std::cout << "error";
        }
        std::cout << glGetString(GL_VERSION) << std::endl;

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls

        ImGui::StyleColorsDark();

        // Setup Platform/Renderer bindings
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init(glsl_version);

        /*glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        glfwSetCursorPosCallback(window, mouse_callback);
        glfwSetCursorPos(window, 960.0, 540);*/

        glfwSetKeyCallback(window, key_callback);
    }

    Config::~Config()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
        glfwTerminate();
    }

    GLFWwindow* Config::GetWindow() const
    {
        return window;
    }

    
}

