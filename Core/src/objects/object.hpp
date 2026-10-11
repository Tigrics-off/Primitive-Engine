#pragma once
#include "glm/ext/vector_float3.hpp"
#include "graphics/shader.hpp"

class object
{
protected:
    glm::vec3 _pos{0}, _rot{0}, _scale{1};
public:
    virtual ~object() = default;
    
    glm::vec3 pos() const;
    glm::vec3 rot() const;
    glm::vec3 scale() const;

    virtual void set_pos(const glm::vec3& pos);
    virtual void set_pos(float x = 0, float y = 0, float z = 0);
    
    virtual void translate(const glm::vec3& pos);
    virtual void translate(float x = 0, float y = 0, float z = 0);

    virtual void set_rot(const glm::vec3& rot);
    virtual void set_rot(float x = 0, float y = 0, float z = 0);
    
    virtual void rotate(const glm::vec3& rot);
    virtual void rotate(float x = 0, float y = 0, float z = 0);

    virtual void set_scale(const glm::vec3& scale);
    virtual void set_scale(float x = 1, float y = 1, float z = 1);

    virtual void size(const glm::vec3& scale);
    virtual void size(float x = 0, float y = 0, float z = 0);

    virtual void render(shaders& shader) = 0;
};