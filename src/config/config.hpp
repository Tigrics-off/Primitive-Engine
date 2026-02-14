#pragma once
#include <GLFW/glfw3.h>
#include <string>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

#include "../file/file.hpp"

namespace custom
{
    struct config
    {
        int width, height;
        std::string title;
        bool fullscreen = false;
        bool psx_style = true;
        GLFWmonitor *monitor = nullptr;
        double bg[3] = {0.1, 0.1, 0.1};
    };
    void parse_config(config &conf);
    void load_arg(int argc, char *argv[], config &conf);
}