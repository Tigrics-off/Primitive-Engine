#include "point.hpp"
#include <glad/glad.h>

point_light::point_light(float r, float g, float b, float strength) : light(r, g, b, strength)
{
    set_color(r, g, b);
    set_strength(strength);
}

void point_light::enable(unsigned int shader_prog)
{
    unsigned int point_light_pos_loc = glGetUniformLocation(shader_prog, "point_light_pos");
    unsigned int point_light_strength_loc = glGetUniformLocation(shader_prog, "point_light_strength");
    unsigned int point_light_color_loc = glGetUniformLocation(shader_prog, "point_light_color");

    glUniform3f(point_light_pos_loc, position.x, position.y, position.z);
    
    glUniform1f(point_light_strength_loc, get_strength());
    
    glm::vec3 col = get_color();
    glUniform3f(point_light_color_loc, col.x, col.y, col.z);
}