#include "mesh.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#include <filesystem>

void shape::set_texture(std::string texture_path)
{
    int img_width, img_height, channels;
    unsigned char *image = stbi_load(texture_path.c_str(), &img_width, &img_height, &channels, 0);
    if (!image)
    {
        debug::warn("Failed load texture " + texture_path + ". His will replaced to debug texture");
        if (std::filesystem::exists("assets/textures/debug/coconutvtf.jpg"))
            image = stbi_load("assets/textures/debug/coconutvtf.jpg", &img_width, &img_height, &channels, 0);
        else
            debug::error("Failed load debug texture (assets/textures/debug/coconutvtf.jpg)");
    }
    
    glGenTextures(1, &texture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    GLenum input_format = (channels == 4) ? GL_RGBA : GL_RGB;
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img_width, img_height, 0, input_format, GL_UNSIGNED_BYTE, image);
    
    stbi_image_free(image);
}

void shape::translate(float x, float y, float z)
{
    object::translate(x, y, z);
    model = glm::translate(model, glm::vec3(x, y, z));
}
void shape::rotate(float x, float y, float z)
{
    object::rotate(x, y, z);
    model = glm::rotate(model, glm::radians(x), glm::vec3(1, 0, 0));
    model = glm::rotate(model, glm::radians(y), glm::vec3(0, 1, 0));
    model = glm::rotate(model, glm::radians(z), glm::vec3(0, 0, 1));
}
void shape::scale(float x, float y, float z)
{
    object::scale(x, y, z);
    model = glm::scale(model, glm::vec3(x, y, z));
}

void shape::setup()
{
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);
    
    glBindVertexArray(vao);
    
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, queue.size() * sizeof(unsigned int), queue.data(), GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
void shape::draw(unsigned int shader_prog)
{
    glUseProgram(shader_prog);
    unsigned int model_loc = glGetUniformLocation(shader_prog, "model");
    glUniformMatrix4fv(model_loc, 1, GL_FALSE, glm::value_ptr(model));

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    unsigned int tex_loc = glGetUniformLocation(shader_prog, "out_texture");
    glUniform1i(tex_loc, 0);
    
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, queue.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

shape::~shape()
{
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);
    glDeleteTextures(1, &texture);
}