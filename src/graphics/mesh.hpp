#pragma once
#include <glad/glad.h>
#include <vector>
#include <string>
#include "core/object.hpp"
#include "core/physics/physics.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class shape : public object
{
protected:
    std::string texture_path;
    unsigned int vao, vbo, ebo;
    GLuint texture;
    std::vector<float> vertices;
    std::vector<unsigned int> queue;

    glm::mat4 model = glm::mat4(1.0f);

    bool passive = false;
    float mass = 1;
    physics::bound_box bound_box;
public:
    void translate(float x, float y, float z) override;
    void rotate(float x, float y, float z) override;
    void scale(float x, float y, float z) override;

    void set_mass(float value);
    void set_passive(bool value);
    void set_texture(std::string texture_path);
    
    std::string get_texture();
    bool get_passive();
    float get_mass();
    physics::bound_box get_bound() const;
    
    void setup();
    void render(unsigned int shader_prog) override;

    ~shape();
};