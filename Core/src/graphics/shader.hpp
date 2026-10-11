#pragma once
#include "glm/ext/matrix_float4x4.hpp"
#include <string>

class shaders
{
public:
    unsigned int program;
    
    shaders(const std::string& vertex_path, const std::string& fragment_path);
    ~shaders();
    
    void use();
    void set_mat4(const std::string& name, const glm::mat4& mat) const;
    void set_float(const std::string& name, float value) const;
    void set_bool(const std::string& name, bool value) const;
    void set_vec3(const std::string& name, const glm::vec3& vec) const;
};