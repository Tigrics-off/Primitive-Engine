#pragma once
#include <glad/glad.h>
#include <vector>
#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "utils/debug.hpp"

class object
{
protected:
    glm::vec3 position = glm::vec3(0);
    glm::vec3 rotation = glm::vec3(0);
    glm::vec3 size = glm::vec3(0);
public:
    virtual void translate(float x, float y, float z);
    virtual void rotate(float x, float y, float z);
    virtual void scale(float x, float y, float z);

    glm::vec3 get_pos();
    glm::vec3 get_rotate();
    glm::vec3 get_scale();
};