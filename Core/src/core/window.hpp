#pragma once
#include "GLFW/glfw3.h"
#include "utils/placeholders.hpp"
#include <cstdint>
#include <string>
#include <glm/glm.hpp>

class window
{
private:
    int _width, _height;
    std::string _title;
    bool _fullscreen, _vsync;
    GLFWwindow* _win;
    std::string _icon;
public:
    window
    (
        int width = 800, int height = 600, 
        std::string title = "Whoever reads is gay",
        bool fullscreen = false, bool vsync = false,
        std::string icon_path = PLACEHOLDER_AVATAR
    );
    ~window();

    window(const window&) = delete;
    window& operator=(const window&) = delete;

    bool should_close();
    void close();

    void clear(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha = 255);
    void update();

    int width() const;
    int height() const;
    std::string title() const;
    bool fullscreen() const;
    bool vsync() const;
    std::string icon() const;
    GLFWwindow* win() const;

    void set_size(int width, int height);
    void set_title(std::string title);
    void set_fullscreen(bool fullscreen);
    void set_vsync(bool vsync);
    void set_icon(std::string path);
};