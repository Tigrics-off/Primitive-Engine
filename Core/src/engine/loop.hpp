#pragma once
#include "core/window.hpp"
#include <cstdint>
#include <functional>

class game_loop
{
private:
    float _delta_time;
    window& _win;
    uint8_t _red, _green, _blue, _alpha;
public:
    game_loop(window& win, uint8_t red = 50, uint8_t green = 50, uint8_t blue = 50, uint8_t alpha = 255);
    void run(std::function<void()> gameplay);

    float delta_time() const;
};