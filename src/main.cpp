#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <cstdlib>

#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_opengl3.h"

#include "debug/debug.hpp"

using namespace std::string_literals;

bool dark_mode = true;

GLFWwindow *win;

void load_arg(int argc, char const *argv[])
{
    for(int i = 1; i <= argc; i++)
    {
        if (argv[i] == "--light") dark_mode = false;
        if (argv[i] == "--dark") dark_mode = true;
        if (argv[i] == "--nocolor") debug::no_color(true);
    }
}

void open_link(std::string link)
{
    #ifdef __WIN32__
        system(("start " + link).c_str());
    #elifdef __APPLE__
        system(("open " + link).c_str());
    #elifdef __linux__
        system(("xdg-open " + link).c_str());
    #else
        debug::error("Unknown sysyem (who are you, warrior?)")
    #endif
}

void input()
{
    bool ctrl = glfwGetKey(win, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS || glfwGetKey(win, GLFW_KEY_RIGHT_CONTROL);
    bool shift = glfwGetKey(win, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS || glfwGetKey(win, GLFW_KEY_RIGHT_SHIFT);
    bool alt = glfwGetKey(win, GLFW_KEY_LEFT_ALT) == GLFW_PRESS || glfwGetKey(win, GLFW_KEY_RIGHT_ALT);

    if(ctrl && glfwGetKey(win, GLFW_KEY_W) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(win, true);
    }
}

void draw_gui()
{
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);

    if (ImGui::Begin(
        "Primitive Engine", 
        nullptr, 
        ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_MenuBar
    ))
        {
        if (ImGui::BeginMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                if (ImGui::MenuItem("New", "Ctrl+N"));
                if (ImGui::MenuItem("Close", "Ctrl+W"))
                {
                    glfwSetWindowShouldClose(win, true);
                }
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("Edit"))
            {
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("Help"))
            {
                if (ImGui::MenuItem("Github"))
                {
                    open_link("https://github.com/Tigrics-off/Primitive-Engine");
                }
                ImGui::EndMenu();
            }
            ImGui::EndMenuBar();
        }

        ImGui::SetWindowPos(ImVec2(0, 340));
        ImGui::SetWindowSize(ImVec2(200, 300));
        if (ImGui::Begin("Properties", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize))
        {
            ImGui::End();
        }
        ImGui::End();
    }
}

int main(int argc, char const *argv[])
{
    load_arg(argc, argv);
    if (!glfwInit())
    {
        debug::error("fail init glfw");
        return 1;
    }

    win = glfwCreateWindow(800, 600, "Primitive Engine", nullptr, nullptr);
    glfwMakeContextCurrent(win);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        debug::error("fail init glad");
        return 1;
    }

    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(win, true);
    ImGui_ImplOpenGL3_Init("#version 330");
    if (dark_mode) ImGui::StyleColorsDark();
    else ImGui::StyleColorsLight();

    while (!glfwWindowShouldClose(win))
    {
        glClearColor(0.1f, 0.1f, 0.1f, 0.1f);
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        draw_gui();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        input();

        glfwSwapBuffers(win);
        glfwPollEvents();
    }
    
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(win);
    glfwTerminate();
    return 0;
}