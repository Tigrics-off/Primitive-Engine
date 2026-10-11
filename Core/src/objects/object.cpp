#include "object.hpp"
#include "glm/ext/vector_float3.hpp"

glm::vec3 object::pos() const
    {return _pos;}
glm::vec3 object::rot() const
    {return _rot;}
glm::vec3 object::scale() const
    {return _scale;}

void object::set_pos(const glm::vec3& pos)
    {_pos = pos;}
void object::set_rot(const glm::vec3& rot)
    {_rot = rot;}
void object::set_scale(const glm::vec3& scale)
    {_scale = scale;}

void object::set_pos(float x, float y, float z)
    {_pos = glm::vec3(x, y, z);}
void object::set_rot(float x, float y, float z)
    {_rot = glm::vec3(x, y, z);}
void object::set_scale(float x, float y, float z)
    {_scale = glm::vec3(x, y, z);}

void object::translate(const glm::vec3& pos)
    {_pos += pos;}
void object::rotate(const glm::vec3& rot)
    {_rot += rot;}
void object::size(const glm::vec3& scale)
    {_scale += scale;}

void object::translate(float x, float y, float z)
    {_pos += glm::vec3(x, y, z);}
void object::rotate(float x, float y, float z)
    {_rot += glm::vec3(x, y, z);}
void object::size(float x, float y, float z)
    {_scale += glm::vec3(x, y, z);}