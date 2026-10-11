#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <cstdint>
#include <filesystem>
#include "utils/debug.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "window.hpp"
#include "stb_image.h"
#include "utils/placeholders.hpp"

window::window(int width, int height, std::string title, bool fullscreen, bool vsync, std::string icon_path)
    : _width(width), _height(height), _title(title), _fullscreen(fullscreen), _vsync(vsync), _icon(icon_path)
{
    if (!glfw_init())
        debug::error("glfw not init");

    glfw_window_hint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfw_window_hint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfw_window_hint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfw_window_hint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);

    GLFWmonitor* monitor = 
    fullscreen
        ? glfw_get_primary_monitor()
        : nullptr;
    _win = glfw_create_window(width, height, title.c_str(), monitor, nullptr);

    if (!_win)
        debug::error("window not created");

    if (!std::filesystem::exists(icon_path))
    {
        debug::warn("Failed load \"{}\". He will replaced to debug icon", icon_path);
        _icon = PLACEHOLDER_AVATAR;
    }

    GLFWimage img;
    int channels;

    img.pixels = stbi_load(_icon.c_str(), &img.width, &img.height, &channels, 4);

    if (!img.pixels)
    {
        debug::error("failed load icon {}", _icon);
    }

    glfw_set_window_icon(_win, 1, &img);
    stbi_image_free(img.pixels);

    glfw_make_context_current(_win);
    glfw_swap_interval(vsync);

    if (!glad_load_gl_loader((GLADloadproc)glfw_get_proc_address))
        debug::error("glad not init");
}
window::~window()
{
    if (_win) glfw_destroy_window(_win);
    glfw_terminate();
    _win = nullptr;
}

bool window::should_close()
    {return glfw_window_should_close(_win);}
void window::close()
    {glfw_set_window_should_close(_win, true);}

void window::clear(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha)
{
    gl_clear_color((float)red/255.f, (float)green/255.f, (float)blue/255.f, (float)alpha/255.f);
    gl_clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
void window::update()
{
    glfw_swap_buffers(_win);
    glfw_poll_events();
}

int window::width() const
    {return _width;}
int window::height() const
    {return _height;}
bool window::fullscreen() const
    {return _fullscreen;}
bool window::vsync() const
    {return _vsync;}
std::string window::title() const
    {return _title;}
std::string window::icon() const
    {return _icon;}
GLFWwindow* window::win() const
    {return _win;}
void window::set_size(int width, int height)
{
    _width = width;
    _height = height;

    glfw_set_window_size(_win, width, height);
}
void window::set_title(std::string title)
{
    _title = title;

    glfw_set_window_title(_win, title.c_str());
}
void window::set_fullscreen(bool fullscreen)
{
    _fullscreen = fullscreen;

    GLFWmonitor* mon = 
    fullscreen 
        ? glfw_get_primary_monitor()
        : nullptr;
    int refresh_rate = GLFW_DONT_CARE;
    if (mon)
        refresh_rate = glfw_get_video_mode(mon)->refreshRate;

    glfw_set_window_monitor
    (
        _win, 
        mon, 
        fullscreen ? 0 : 100,
        fullscreen ? 0 : 100,
        _width, 
        _height, 
        refresh_rate
    );
}
void window::set_vsync(bool vsync)
{
    _vsync = vsync;

    glfw_swap_interval(vsync);
}
void window::set_icon(std::string icon_path)
{
    if (!std::filesystem::exists(icon_path))
    {
        debug::warn("Failed load \"{}\". He will replaced to debug icon", icon_path);
        _icon = PLACEHOLDER_AVATAR;
    }
    GLFWimage img;
    int channels;

    img.pixels = stbi_load(_icon.c_str(), &img.width, &img.height, &channels, 4);

    if (!img.pixels)
    {
        debug::error("failed load icon {}", _icon);
    }

    glfw_set_window_icon(_win, 1, &img);
    stbi_image_free(img.pixels);
}