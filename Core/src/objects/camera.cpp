#include "camera.hpp"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/vector_float3.hpp"
#include "glm/trigonometric.hpp"
#include "graphics/shader.hpp"
#include "object.hpp"

void camera::update_mat()
{
    glm::mat4 new_view{1}, new_proj{1};

    new_view = glm::rotate(new_view, glm::radians(-_rot.x), glm::vec3(1, 0, 0));
    new_view = glm::rotate(new_view, glm::radians(-_rot.y), glm::vec3(0, 1, 0));
    new_view = glm::rotate(new_view, glm::radians(-_rot.z), glm::vec3(0, 0, 1));

    new_view = glm::translate(new_view, -_pos);

    view = new_view;
    proj = glm::perspective(glm::radians(_fov), _aspect, _near, _far);
}

camera::camera(float fov, float aspect, float near, float far)
    : _fov(fov), _aspect(aspect), _near(near), _far(far)
{
    this->set_pos(0, 0, 3);
}

float camera::fov() const
    {return _fov;}
float camera::aspect() const
    {return _aspect;}
float camera::near() const
    {return _near;}
float camera::far() const
    {return _far;}


void camera::set_pos(const glm::vec3& pos)
{
    object::set_pos(pos);
    update_mat();
}
void camera::set_pos(float x, float y, float z)
{
    object::set_pos(x, y, z);
    update_mat();
}
void camera::translate(const glm::vec3& pos)
{
    object::translate(pos);
    update_mat();
}
void camera::translate(float x, float y, float z)
{
    object::translate(x, y, z);
    update_mat();
}
void camera::set_rot(const glm::vec3& rot)
{
    object::set_rot(rot);
    update_mat();
}
void camera::set_rot(float x, float y, float z)
{
    object::set_rot(x, y, z);
    update_mat();
}
void camera::rotate(const glm::vec3& rot)
{
    object::rotate(rot);
    update_mat();
}
void camera::rotate(float x, float y, float z)
{
    object::rotate(x, y, z);
    update_mat();
}
void camera::set_scale(const glm::vec3& scale)
{
    object::set_scale(scale);
    update_mat();
}
void camera::set_scale(float x, float y, float z)
{
    object::set_scale(x, y, z);
    update_mat();
}
void camera::size(const glm::vec3& scale)
{
    object::size(scale);
    update_mat();
}
void camera::size(float x, float y, float z)
{
    object::size(x, y, z);
    update_mat();
}

void camera::set_fov(float fov)
{
    _fov = fov;
    update_mat();
}
void camera::set_aspect(float x, float y)
{
    _aspect = x/y;
    update_mat();
}
void camera::set_near(float near)
{
    _near = near;
    update_mat();
}
void camera::set_far(float far)
{
    _far = far;
    update_mat();
}

void camera::render(shaders& shader)
{
    shader.set_mat4("u_view", view);
    shader.set_mat4("u_proj", proj);
}