#include "glad/glad.h"
#include "loop.hpp"
#include "GLFW/glfw3.h"
#include "core/window.hpp"
#include <cstdint>
#include <functional>

game_loop::game_loop(window& win, uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha)
    : _win(win), _red(red), _green(green), _blue(blue), _alpha(alpha)
{}
void game_loop::run(std::function<void()> gameplay)
{
    gl_enable(GL_DEPTH_TEST);
    float last_time = glfw_get_time();
    while (!_win.should_close())
    {
        float cur_time = glfw_get_time();
        _delta_time = cur_time - last_time;
        last_time = cur_time;

        _win.clear(_red, _green, _blue, _alpha);
        gameplay();
        _win.update();
    }
}

float game_loop::delta_time() const
    {return _delta_time;}