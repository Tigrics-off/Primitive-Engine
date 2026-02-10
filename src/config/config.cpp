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
    void parse_config(config &conf)
    {
        std::string text = file::read("assets/config.json");

        json config = json::parse(text);

        conf.width = config["resolution"][0].get<int>();
        conf.height = config["resolution"][1].get<int>();

        conf.title = config["title"].get<std::string>();
        conf.fullscreen = config["fullscreen"].get<bool>();
        conf.psx_style = config["psx_style"].get<bool>();

        conf.bg[0] = config["bg_color"][0].get<double>()/255.0;
        conf.bg[1] = config["bg_color"][1].get<double>()/255.0;
        conf.bg[2] = config["bg_color"][2].get<double>()/255.0;
    }
}