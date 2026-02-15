#include "object.hpp"

void object::translate(float x, float y, float z)
{
    position += glm::vec3(x, y, z);
}
void object::rotate(float x, float y, float z)
{
    rotation += glm::vec3(x, y, z);
}
void object::scale(float x, float y, float z)
{
    size *= glm::vec3(x, y, z);
}

glm::vec3 object::get_pos() { return position; }
glm::vec3 object::get_rotate() { return rotation; }
glm::vec3 object::get_scale() { return size; }