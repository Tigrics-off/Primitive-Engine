#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "utils/config.hpp"

namespace window
{
    GLFWwindow *init(custom::config conf);
    void destroy(GLFWwindow *win);
}