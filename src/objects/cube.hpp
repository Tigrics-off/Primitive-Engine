#pragma once
#include "core/physics/physics.hpp"
#include "graphics/mesh.hpp"
#include <string>

class cube : public shape
{
public:
    cube(std::string path, bool is_passive = false, float mass = 0.1)
    {
        vertices = {
            -0.5f, -0.5f, -0.5f,   0.0f, 0.0f,
            +0.5f, -0.5f, -0.5f,   1.0f, 0.0f,
            +0.5f, +0.5f, -0.5f,   1.0f, 1.0f,
            -0.5f, +0.5f, -0.5f,   0.0f, 1.0f,
            
            -0.5f, -0.5f, +0.5f,   0.0f, 0.0f,
            +0.5f, -0.5f, +0.5f,   1.0f, 0.0f,
            +0.5f, +0.5f, +0.5f,   1.0f, 1.0f,
            -0.5f, +0.5f, +0.5f,   0.0f, 1.0f,
            
            -0.5f, -0.5f, +0.5f,   0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f,   1.0f, 0.0f,
            -0.5f, +0.5f, -0.5f,   1.0f, 1.0f,
            -0.5f, +0.5f, +0.5f,   0.0f, 1.0f,
            
            +0.5f, -0.5f, +0.5f,   0.0f, 0.0f,
            +0.5f, -0.5f, -0.5f,   1.0f, 0.0f,
            +0.5f, +0.5f, -0.5f,   1.0f, 1.0f,
            +0.5f, +0.5f, +0.5f,   0.0f, 1.0f,
            
            -0.5f, +0.5f, +0.5f,   0.0f, 0.0f,
            +0.5f, +0.5f, +0.5f,   1.0f, 0.0f,
            +0.5f, +0.5f, -0.5f,   1.0f, 1.0f, 
            -0.5f, +0.5f, -0.5f,   0.0f, 1.0f,
            
            -0.5f, -0.5f, +0.5f,   0.0f, 0.0f,
            +0.5f, -0.5f, +0.5f,   1.0f, 0.0f,
            +0.5f, -0.5f, -0.5f,   1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,   0.0f, 1.0f
        };

        queue = {
            // Back
            0, 1, 2,   2, 3, 0,
            // Front
            4, 5, 6,   6, 7, 4,
            // Left
            8, 9, 10,  10, 11, 8,
            // Right
            12, 13, 14, 14, 15, 12,
            // Up
            16, 17, 18, 18, 19, 16,
            // Down
            20, 21, 22, 22, 23, 20
        };

        physics::collision::col_cube collision;
        collision.min = glm::vec3(-1, -1, -1);
        collision.max = glm::vec3(+1, +1, +1);

        col.cubes.push_back(collision);

        setup();
        set_texture(path);
            
        set_passive(is_passive);
        set_mass(mass);
    }
};