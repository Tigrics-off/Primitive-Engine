#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class camera
{
public:
    glm::mat4 proj = glm::mat4(1.0);
    glm::mat4 view = glm::mat4(1.0);
    
    void hand_matrix(unsigned int shader_prog);
    
    camera(int width, int height, float fov = 60.f, float min = 0.01f, float max = 500.f);
    void translate(float x, float y, float z);
    void rotate(float x, float y, float z);
    glm::vec3 get_pos();
    glm::vec3 get_rotate();
    glm::vec3 get_direction();
private:
    glm::vec3 position = glm::vec3(0);
    glm::vec3 rotation = glm::vec3(0);
    glm::vec3 direction = glm::vec3(0);
    void update_view();
};