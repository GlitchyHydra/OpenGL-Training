#include "OpenGL_config.h"

#include <iostream>

My_OpenGL::Config::Config()
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
}

My_OpenGL::Config::~Config()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
}

GLFWwindow* My_OpenGL::Config::GetWindow() const
{
    return window;
}
