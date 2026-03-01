#include "spot.hpp"
#include <glad/glad.h>

void spot_light::set_min_angle(float value) { min_angle = value; }
void spot_light::set_max_angle(float value) { max_angle = value; }

float spot_light::get_min_angle() { return min_angle; }
float spot_light::get_max_angle() { return max_angle; }

spot_light::spot_light(float r, float g, float b, float strength) : light(r, g, b, strength)
{ }

void spot_light::enable(unsigned int shader_prog)
{
    #define rad glm::radians
    unsigned int spot_light_pos_loc = glGetUniformLocation(shader_prog, "spot_light_pos");
    unsigned int spot_light_strength_loc = glGetUniformLocation(shader_prog, "spot_light_strength");
    unsigned int spot_light_color_loc = glGetUniformLocation(shader_prog, "spot_light_color");
    unsigned int spot_light_dir_loc = glGetUniformLocation(shader_prog, "spot_light_dir");
    unsigned int cut_off_loc = glGetUniformLocation(shader_prog, "cut_off");
    unsigned int out_cut_off_loc = glGetUniformLocation(shader_prog, "out_cut_off");

    glUniform3f(spot_light_pos_loc, position.x, position.y, position.z);
    glUniform3f(spot_light_color_loc, get_color().x, get_color().y, get_color().z);
    glUniform3f(spot_light_dir_loc, get_direction().x, get_direction().y, get_direction().z);

    glUniform1f(spot_light_strength_loc, get_strength());
    glUniform1f(cut_off_loc, glm::cos(rad(min_angle)));
    glUniform1f(out_cut_off_loc, glm::cos(rad(max_angle)));
}