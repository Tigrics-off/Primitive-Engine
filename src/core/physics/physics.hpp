#pragma once
#include "glm/ext/vector_float3.hpp"
#include <glm/glm.hpp>
#include <vector>

class shape;

class physics
{
private:
    std::vector<shape*> active_object;
    std::vector<shape*> passive_object;

    glm::vec3 gravity;
    float time_scale;
    float restitution;
    float friction;
    bool collisions;

public:
    physics
    (
        float g = 9.81,
        float time = 1.0, 
        float res = 0.5, 
        float f = 0.5,
        bool col = true
    );
    void set_gravity(float x, float y, float z);
    void set_gravity_x(float value);
    void set_gravity_y(float value);
    void set_gravity_z(float value);

    void set_time(float value);
    void set_restitution(float value);
    void set_friction(float value);
    void set_collisions(bool value);

    glm::vec3 get_gravity();

    float get_time();
    float get_restitution();
    float get_friction();
    bool get_collision();

    void add_object(shape *obj);

    struct collision
    {
        struct col_cube
        {
            glm::vec3 min, max;
        };
        std::vector<col_cube> cubes;

        bool intersect(const collision col) const;
    };
    
    bool check_collision(shape *a, shape *b);

    void render(float delta);
};