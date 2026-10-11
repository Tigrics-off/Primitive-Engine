#pragma once
#include "glm/ext/matrix_float4x4.hpp"
#include "glm/ext/vector_float3.hpp"
#include "graphics/shader.hpp"
#include "object.hpp"
#include <string>
#include <vector>

class mesh : public object
{
protected:
    unsigned int vao{1}, vbo{1}, ibo{1}, tex_id{1};
    glm::mat4 model{1.0f};
    std::vector<float> vert;
    std::vector<unsigned int> idx;


    void set_buff();
    void update_model();
public:
    ~mesh();
    mesh() = default;

    void set_texture(const std::string& path, bool flip = true);
    virtual void set_figure() = 0;

    void set_pos(const glm::vec3& pos) override;
    void set_pos(float x, float y, float z) override;

    void translate(const glm::vec3& pos) override;
    void translate(float x, float y, float z) override;

    void set_rot(const glm::vec3& rot) override;
    void set_rot(float x, float y, float z) override;

    void rotate(const glm::vec3& rot) override;
    void rotate(float x, float y, float z) override;

    void set_scale(const glm::vec3& scale) override;
    void set_scale(float x , float y, float z) override;

    void size(const glm::vec3& scale) override;
    void size(float x = 0, float y = 0, float z = 0) override;

    void render(shaders& shader) override;
};