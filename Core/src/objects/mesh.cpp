#include <glad/glad.h>
#include "mesh.hpp"
#include "graphics/shader.hpp"
#include "object.hpp"

#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <filesystem>
#include <stb_image.h>
#include <cmath>
#include <algorithm>
#include "utils/debug.hpp"
#include "utils/placeholders.hpp"

mesh::~mesh()
{
    if (vao) gl_delete_vertex_arrays(1, &vao);
    if (vbo) gl_delete_buffers(1, &vbo);
    if (ibo) gl_delete_buffers(1, &ibo);
    if (tex_id) gl_delete_textures(1, &tex_id);
}

void mesh::set_texture(const std::string& texture_path, bool flip)
{
    std::string path;
    if (std::filesystem::exists(texture_path))
        path = texture_path;
    else
    {
        debug::warn("failed load \"{}\". He will replaced to debug texture", texture_path);
        path = PLACEHOLDER_TEXTURE;
    }

    int width, height, channels;
    stbi_set_flip_vertically_on_load(flip);

    unsigned char* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
    if (!data)
        debug::error("Failed load \"{}\"", path);

    GLenum int_format = GL_RGB8;
    GLenum dat_format = GL_RGB;

    if (channels == 1)
    {
        int_format = GL_R8;
        dat_format = GL_RED;
    }
    else if (channels == 3)
    {
        int_format = GL_RGB8;
        dat_format = GL_RGB;
    }
    else if (channels == 4)
    {
        int_format = GL_RGBA8;
        dat_format = GL_RGBA;
    }

    gl_create_textures(GL_TEXTURE_2D, 1, &tex_id);

    gl_texture_parameteri(tex_id, GL_TEXTURE_WRAP_S, GL_REPEAT);
    gl_texture_parameteri(tex_id, GL_TEXTURE_WRAP_T, GL_REPEAT);
    gl_texture_parameteri(tex_id, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    gl_texture_parameteri(tex_id, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    int mip = 1 + static_cast<int>(std::floor(std::log2(std::max(width, height))));
    gl_texture_storage2_d(tex_id, mip, int_format, width, height);
    gl_texture_sub_image2_d(tex_id, 0, 0, 0, width, height, dat_format, GL_UNSIGNED_BYTE, data);
    gl_generate_texture_mipmap(tex_id);

    stbi_image_free(data);
}

void mesh::update_model()
{
    model = glm::mat4(1.0f);
    model = glm::translate(model, _pos);
    model = glm::rotate(model, glm::radians(_rot.x), glm::vec3(1, 0, 0));
    model = glm::rotate(model, glm::radians(_rot.y), glm::vec3(0, 1, 0));
    model = glm::rotate(model, glm::radians(_rot.z), glm::vec3(0, 0, 1));
    model = glm::scale(model, _scale);
}
void mesh::set_buff()
{
    const int stride = 5 * sizeof(float);
    
    gl_create_buffers(1, &vbo);
    gl_named_buffer_storage
    (
        vbo, 
        vert.size() * sizeof(float), 
        vert.data(), 
        GL_DYNAMIC_STORAGE_BIT
    );

    gl_create_buffers(1, &ibo);
    gl_named_buffer_storage
    (
        ibo, 
        idx.size() * sizeof(unsigned int), 
        idx.data(), 
        GL_DYNAMIC_STORAGE_BIT
    );

    gl_create_vertex_arrays(1, &vao);
    gl_vertex_array_vertex_buffer(vao, 0, vbo, 0, stride);
    gl_vertex_array_element_buffer(vao, ibo);

    gl_enable_vertex_array_attrib(vao, 0);
    gl_vertex_array_attrib_format(vao, 0, 3, GL_FLOAT, false, 0);
    gl_vertex_array_attrib_binding(vao, 0, 0);
    
    gl_enable_vertex_array_attrib(vao, 1);
    gl_vertex_array_attrib_format(vao, 1, 2, GL_FLOAT, false, 3*sizeof(float));
    gl_vertex_array_attrib_binding(vao, 1, 0);

}

void mesh::set_pos(const glm::vec3& pos)
{
    object::set_pos(pos);
    update_model();
}
void mesh::set_pos(float x, float y, float z)
{
    object::set_pos(x, y, z);
    update_model();
}

void mesh::translate(const glm::vec3& pos)
{
    object::translate(pos);
    update_model();
}
void mesh::translate(float x, float y, float z)
{
    object::translate(x, y, z);
    update_model();
}

void mesh::set_rot(const glm::vec3& rot)
{
    object::set_rot(rot);
    update_model();
}
void mesh::set_rot(float x, float y, float z)
{
    object::set_rot(x, y, z);
    update_model();
}

void mesh::rotate(const glm::vec3& rot)
{
    object::rotate(rot);
    update_model();
}
void mesh::rotate(float x, float y, float z)
{
    object::rotate(x, y, z);
    update_model();
}

void mesh::set_scale(const glm::vec3& scale)
{
    object::set_scale(scale);
    update_model();
}
void mesh::set_scale(float x, float y, float z)
{
    object::set_scale(x, y, z);
    update_model();
}

void mesh::size(const glm::vec3& scale)
{
    object::size(scale);
    update_model();
}
void mesh::size(float x, float y, float z)
{
    object::size(x, y, z);
    update_model();
}

void mesh::render(shaders& shader)
{
    shader.set_mat4("u_model", model);

    if (tex_id)
        gl_bind_texture_unit(0, tex_id);

    gl_bind_vertex_array(vao);
    gl_draw_elements(GL_TRIANGLES, idx.size(), GL_UNSIGNED_INT, nullptr);
}