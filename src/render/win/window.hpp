#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "config/config.hpp"

namespace window
{
    GLFWwindow *init(custom::config conf);
    void destroy(GLFWwindow *win);
}