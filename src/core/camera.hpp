#pragma once
#include "core/object.hpp"

class camera : public object
{
public:
    void hand_matrix(unsigned int shader_prog); 
    camera(int width, int height, float fov = 60.f, float min = 0.01f, float max = 500.f);

    glm::vec3 get_direction();

    void translate(float x, float y, float z) override;
    void rotate(float x, float y, float z) override;
    void scale(float x, float y, float z) override;
private:
    glm::mat4 proj = glm::mat4(1.0);
    glm::mat4 view = glm::mat4(1.0);
    glm::vec3 direction = glm::vec3(0);
    void update_view();
};