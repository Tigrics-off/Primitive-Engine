#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "config/config.hpp"
#include "debug/debug.hpp"
#include "file/file.hpp"

GLFWwindow *win;
custom::config conf;

unsigned int vao, vbo, shader_program;

float verticles[] = {
    +0.0, +0.5, 0.0,      0.1, 0.1, 0.1,
    +0.5, -0.5, 0.0,      0.1, 0.1, 0.1,
    -0.5, -0.5, 0.0,      0.1, 0.1, 0.1,

};

void format_verticles()
{
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticles), verticles, GL_STATIC_DRAW);
    
}

int main(int argc, char const *argv[])
{
    custom::parse_config(conf);
    if (!glfwInit()) debug::error("Failed init glfw");

    conf.monitor = conf.fullscreen ? glfwGetPrimaryMonitor() : nullptr;
    win = glfwCreateWindow(conf.width, conf.height, conf.title.c_str(), conf.monitor, nullptr);
    if (!win) debug::error("failed create window");
    
    glfwMakeContextCurrent(win);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) debug::error("Failed load glad");

    while (!glfwWindowShouldClose(win))
    {
        glClearColor(conf.bg[0], conf.bg[1], conf.bg[2], 1.0);
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(win);

        glfwPollEvents();
    }
    
    return 0;
}
