#pragma once
#include "graphics/mesh.hpp"
#include <string>

class quad : public shape
{
public:
    quad(std::string path)
    {
        vertices = {
            -0.5, +0.5, 0.0,    0, 0,
            -0.5, -0.5, 0.0,    0, 1,
            +0.5, +0.5, 0.0,    1, 0,
            +0.5, -0.5, 0.0,    1, 1
        };

        queue = {0, 1, 2,  1, 3, 2};

        setup();
        set_texture(path);
    }
};