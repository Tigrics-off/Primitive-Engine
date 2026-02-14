#include "glad/glad.h"
#include "camera.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

void camera::hand_matrix(unsigned int shader_prog)
{
    unsigned int view_loc = glGetUniformLocation(shader_prog, "view");
    unsigned int proj_loc = glGetUniformLocation(shader_prog, "proj");

    glUniformMatrix4fv(view_loc, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(proj_loc, 1, GL_FALSE, glm::value_ptr(proj));
}

camera::camera(int width, int height, float fov, float min, float max)
{
    proj = glm::perspective(glm::radians(fov), (float)(width/height), min, max);
    position = glm::vec3(0, 0, 3);
    direction = glm::vec3(0, 0, -1);
    rotation = glm::vec3(0);
    update_view();
}

void camera::translate(float x, float y, float z)
{
    position += glm::vec3(x, y, z);
    update_view();
}
void camera::rotate(float x, float y, float z)
{;
    rotation += glm::vec3(x, y, z);

    if (rotation.x > 180) rotation.y = 180;
    if (rotation.x < 0) rotation.y = 0;

    direction = glm::vec3(
        cos(rotation.y) * cos(rotation.x),
        sin(rotation.x),
        sin(rotation.y) * cos(rotation.x)
    );

    update_view();
}

glm::vec3 camera::get_pos() { return position; }
glm::vec3 camera::get_rotate() { return rotation; }
glm::vec3 camera::get_direction() { return direction; }

void camera::update_view()
{
    view = glm::lookAt(position, position + direction, glm::vec3(0, 1, 0));
}