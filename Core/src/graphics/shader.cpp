#include "shader.hpp"
#include <glad/glad.h>
#include "glm/gtc/type_ptr.hpp"
#include "utils/debug.hpp"
#include "utils/file.hpp"
#include <string>

shaders::shaders(const std::string& vertex_path, const std::string& fragment_path)
{
    std::string vert_src = files::get_text(vertex_path);
    std::string frag_src = files::get_text(fragment_path);

    const char* vert_code = vert_src.c_str();
    const char* frag_code = frag_src.c_str();

    unsigned int vert, frag;
    int good;
    char log[255];

    vert = gl_create_shader(GL_VERTEX_SHADER);
    gl_shader_source(vert, 1, &vert_code, nullptr);
    gl_compile_shader(vert);

    gl_get_shaderiv(vert, GL_COMPILE_STATUS, &good);
    if (!good)
    {
        gl_get_shader_info_log(vert, 255, nullptr, log);
        debug::error("failed to load vert shader: {}", log);
    }
    
    frag = gl_create_shader(GL_FRAGMENT_SHADER);
    gl_shader_source(frag, 1, &frag_code, nullptr);
    gl_compile_shader(frag);

    gl_get_shaderiv(frag, GL_COMPILE_STATUS, &good);
    if (!good)
    {
        gl_get_shader_info_log(frag, 255, nullptr, log);
        debug::error("failed to load frag shader: {}", log);
    }

    program = gl_create_program();
    gl_attach_shader(program, vert);
    gl_attach_shader(program, frag);
    gl_link_program(program);
    
    gl_get_programiv(program, GL_LINK_STATUS, &good);
    if (!good)
    {
        gl_get_program_info_log(program, 255, nullptr, log);
        debug::error("Failed to create program: {}", log);
    }

    gl_delete_shader(vert);
    gl_delete_shader(frag);
}
shaders::~shaders()
    {gl_delete_program(program);}
void shaders::use()
    {gl_use_program(program);}

void shaders::set_mat4(const std::string& name, const glm::mat4& mat) const
{
    int loc = gl_get_uniform_location(program, name.c_str());
    if (loc != -1)
        gl_uniform_matrix4fv(loc, 1, false, glm::value_ptr(mat));
}
void shaders::set_float(const std::string &name, float value) const
{
    int loc = gl_get_uniform_location(program, name.c_str());
    if (loc != -1)
        gl_uniform1f(loc, value);
}
void shaders::set_bool(const std::string& name, bool value) const
{
    int loc = gl_get_uniform_location(program, name.c_str());
    if (loc != -1)
        gl_uniform1i(loc, value);
}
void shaders::set_vec3(const std::string& name, const glm::vec3& vec) const
{
    int loc = gl_get_uniform_location(program, name.c_str());
    if (loc != -1)
        gl_uniform3f(loc, vec.x, vec.y, vec.z);
}