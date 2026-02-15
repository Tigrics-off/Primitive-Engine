#pragma once
#include <GLFW/glfw3.h>
#include <functional>

#include "utils/config.hpp"

namespace loop
{
    void run(GLFWwindow* win, unsigned int shader_prog, custom::config &conf, std::function<void()> update);
}