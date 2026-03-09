#pragma once

#include <glm/glm.hpp>
#include "graphics/mesh.hpp"

class physics
{
private:
    std::vector<shape*> passive_objects;
    std::vector<shape*> active_objects;
public:
    void add_obj(shape* obj)

    struct bound_box
    {
        glm::vec3 min, max;
        
        bool intersects(const bound_box &other) const;
    };
};