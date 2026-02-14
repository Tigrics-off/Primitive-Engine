#pragma once
#include <glad/glad.h>
#include <vector>
#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "debug/debug.hpp"

class shape
{
protected:
    unsigned int vao, vbo, ebo;
    GLuint texture;
    std::vector<float> vertices;
    std::vector<unsigned int> queue;

    glm::mat4 model = glm::mat4(1.0f);

    glm::vec3 position = glm::vec3(0);
    glm::vec3 rotation = glm::vec3(0);
    glm::vec3 size = glm::vec3(0);
public:
    void set_texture(std::string texture_path);
    void setup();
    void draw(unsigned int shader_prog);
    void translate(float x, float y, float z);
    void rotate(float x, float y, float z);
    void scale(float x, float y, float z);

    glm::vec3 get_pos();
    glm::vec3 get_rotate();
    glm::vec3 get_scale();

    ~shape();
};