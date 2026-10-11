#pragma once
#include "mesh.hpp"
#include <string>

class triangle : public mesh
{
public:
    triangle(std::string texture_path = "")
    {
        set_figure();
        set_buff();
        set_texture(texture_path);
    }
    void set_figure() override
    {
        vert = 
        {
            -0.5f, -0.5f, 0.0f,    0.0f, 0.0f,
            0.5f, -0.5f, 0.0f,    1.0f, 0.0f,
            0.0f,  0.5f, 0.0f,    0.5f, 1.0f
        };
        idx = {0, 1, 2};
    }
};