#include "light.hpp"
#include <glad/glad.h>

#include <glm/gtc/type_ptr.hpp>

light::light(float r = 1.0, float g = 1.0, float b = 1.0, float strength = 1.0)
{
    set_color(r, g, b);
    set_strength(strength);
}

void light::set_color(float r, float g, float b)
{
    color = glm::vec3(r, g, b);
}
void light::set_strength(float value)
{
    strength = value;
}

void light::rotate(float x, float y, float z)
{
    object::rotate(x, y, z);
    direction = glm::vec3(
        cos(rotation.y) * cos(rotation.x),
        sin(rotation.x),
        sin(rotation.y) * cos(rotation.x)
    );
}

glm::vec3 light::get_color() { return color; }
glm::vec3 light::get_direction() { return direction; }
float light::get_strength() { return strength; }

void light::enable(unsigned int shader_prog)
{
    unsigned int light_loc = glGetUniformLocation(shader_prog, "ambient_light");

    glm::vec3 result = color * strength;
    glUniform3f(light_loc, result.x, result.y, result.z);
}