#pragma once
#include <glad/glad.h>
#include <vector>
#include <string>
#include "core/object.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "utils/debug.hpp"

class shape : public object
{
protected:
    unsigned int vao, vbo, ebo;
    GLuint texture;
    std::vector<float> vertices;
    std::vector<unsigned int> queue;

    glm::mat4 model = glm::mat4(1.0f);
public:
    void translate(float x, float y, float z) override;
    void rotate(float x, float y, float z) override;
    void scale(float x, float y, float z) override;
    
    void set_texture(std::string texture_path);
    void setup();
    void draw(unsigned int shader_prog);

    ~shape();
};