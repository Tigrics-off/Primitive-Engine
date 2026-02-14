#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <functional>

#include "config/config.hpp"

namespace loop
{
    void run(GLFWwindow* win, unsigned int shader_prog, custom::config &conf, std::function<void()> update)
    {
        unsigned int psx_loc = glGetUniformLocation(shader_prog, "psx");
        
        glEnable(GL_DEPTH_TEST);
        while (!glfwWindowShouldClose(win))
        {
            glClearColor(conf.bg[0], conf.bg[1], conf.bg[2], 1.0);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glUseProgram(shader_prog);
            glUniform1i(psx_loc, conf.psx_style);
            
            update();

            glfwSwapBuffers(win);
            glfwPollEvents();
        }
    }
}