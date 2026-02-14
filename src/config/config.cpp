#include <GLFW/glfw3.h>
#include <string>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

#include <chrono>
#include <ctime>
#include <string_view>

#include "file/file.hpp"
#include "debug/debug.hpp"

void check_days()
{
    using namespace std::chrono;
    
    auto now = system_clock::now();
    std::time_t now_date = system_clock::to_time_t(now);
    std::tm *date = std::localtime(&now_date);
    
    int code = date->tm_mon * 100 + date->tm_mday;
    
    // Code = [mouth - 1][day]
    switch (code) {
        case 931:  // 31.09
            debug::info("Happy Halloween");
            break;
        case 1124: // 24.12
            debug::info("Merry Christmas");
            break;
        case 1131: // 31.12
            debug::info("Happy new Year");
            break;
        case 301:  // 1.04
            debug::warn("ERROR 0x4a757374206b696464696e670a. Unknown Entity hacked engine");
            debug::warn("Please, DELETE ENGINE IF YOU WANT LIFE");
            break;
        case 208:  // 8.03
            debug::info("Don`t forget congratulate your mom");
            break;
        default:
            debug::warn("Funny is not available in your country");
    };
}

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
    void load_arg(int argc, char *argv[], config &conf)
    {
        std::vector<std::string> args(argv + 1, argv + argc);
        
        for (const auto arg : args)
        {
            if (arg == "--no-psx")
            {
                conf.psx_style = false;
            }
            if (arg == "--no-color")
            {
                debug::no_color(true);
            }
            if (arg == "--funny")
            {
                check_days();
            }
            if (arg == "--help")
            {
                debug::info("--no-psx - off psx style");
                debug::info("--no-color - off colored loging");
                debug::info("--funny - in development");
            }
        }
    }
}