#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "config/config.hpp"
#include "render/shaders/shader.hpp"

namespace window
{
    GLFWwindow *init(custom::config conf)
    {
        if (!glfwInit()) debug::error("Failed init glfw");
        GLFWwindow *win;

        conf.monitor = conf.fullscreen ? glfwGetPrimaryMonitor() : nullptr;
        win = glfwCreateWindow(conf.width, conf.height, conf.title.c_str(), conf.monitor, nullptr);
        if (!win) debug::error("failed create window");
        
        glfwMakeContextCurrent(win);
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) debug::error("Failed load glad");

        glViewport(0, 0, conf.width, conf.height);
        
        return win;
    }
    void destroy(GLFWwindow *win)
    {
        glfwSetWindowShouldClose(win, true);
    }
}