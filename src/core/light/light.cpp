#include "light.hpp"
#include <glad/glad.h>

#include <glm/gtc/type_ptr.hpp>

light::light::light(float r, float g, float b, float strength)
{
    set_color(r/255.0, g/255.0, b/255.0);
    set_strength(strength);
}

void light::light::set_color(float r, float g, float b)
{
    color = glm::vec3(r, g, b);
}
void light::light::set_strength(float value)
{
    strength = value;
}

void light::light::rotate(float x, float y, float z)
{
    object::rotate(x, y, z);
    direction = glm::vec3(
        cos(rotation.y) * cos(rotation.x),
        sin(rotation.x),
        -sin(rotation.y) * cos(rotation.x)
    );
}

glm::vec3 light::light::get_color() { return color; }
glm::vec3 light::light::get_direction() { return direction; }
float light::light::get_strength() { return strength; }

void light::light::render(unsigned int shader_prog)
{
    unsigned int light_loc = glGetUniformLocation(shader_prog, "ambient_light");

    glm::vec3 result = color * strength;
    glUniform3f(light_loc, result.x, result.y, result.z);
}