#include "physics.hpp"
#include "glm/ext/vector_float3.hpp"
#include "graphics/mesh.hpp"
#include <vector>
#include "utils/debug.hpp"

physics::physics(float g, float time, float res, float f, bool col)
{
    gravity = glm::vec3(0, -g, 0);
    time_scale = time;
    restitution = res;
    friction = f;
    collisions = col;
}

void physics::set_gravity(float x, float y, float z)
{
    gravity = glm::vec3(x, -y, z);
}
void physics::set_gravity_x(float value)
{
    gravity.x = value;
}
void physics::set_gravity_y(float value)
{
    gravity.y = -value;
}
void physics::set_gravity_z(float value)
{
    gravity.z = value;
}

void physics::set_time(float value)
{
    time_scale = value;
}
void physics::set_restitution(float value)
{
    restitution = value;
}
void physics::set_friction(float value)
{
    friction = value;
}
void physics::set_collisions(bool value)
{
    collisions = value;
}

bool physics::collision::intersect(const collision col) const
{
    for (auto &a : cubes)
    {
        for (auto &b : col.cubes)
        {
            if 
            (
                a.min.x <= b.max.x && a.max.x >= b.min.x &&
                a.min.y <= b.max.y && a.max.y >= b.min.y &&
                a.min.z <= b.max.z && a.max.z >= b.min.z
            )
            {
                return true;
            }
        }
    }
    return false;
}

bool physics::check_collision(shape *a, shape *b)
{
    if (a == b) return false;

    return a->get_col().intersect(b->get_col());
}

glm::vec3 physics::get_gravity() { return gravity; }
float physics::get_time() { return time_scale; }
float physics::get_restitution() { return restitution; }
float physics::get_friction() { return friction; }
bool physics::get_collision() { return collisions; }

void physics::add_object(shape *obj)
{
    if (obj->get_passive())
        passive_object.push_back(obj);
    else
        active_object.push_back(obj);
}
void physics::render(float delta)
{
    std::vector<shape*> objects;
    objects.reserve(active_object.size() + passive_object.size());
    objects.insert(objects.end(), active_object.begin(), active_object.end());
    objects.insert(objects.end(), passive_object.begin(), passive_object.end());

    for (auto* active : active_object)
    {
        bool collided = false;
        
        for (auto* obj : objects)
        {
            if (check_collision(active, obj))
            {
                collided = true;
                break;
            }
        }
        
        if (!collided)
        {
            glm::vec3 vel = active->get_velocity();
            vel += gravity * delta;
            active->set_velocity(vel.x, vel.y, vel.z);
            
            active->translate(vel.x * delta, vel.y * delta, vel.z * delta);
        }
    }
}