#pragma once
#include "glm/ext/matrix_float4x4.hpp"
#include "graphics/shader.hpp"
#include "objects/object.hpp"

class camera: public object
{
private:
    glm::mat4 view{1}, proj{1};

    float _fov{90}, _aspect{16.f/9.f}, _near{0.1}, _far{100};

    void update_mat();
public:
    camera(float fov = 90, float aspect = 16.f/9.f, float near = 0.1, float far = 100);

    float fov() const;
    float aspect() const;
    float near() const;
    float far() const;

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

    void set_fov(float fov);
    void set_aspect(float x, float y);
    void set_near(float near);
    void set_far(float far);

    void render(shaders& shader) override;
};