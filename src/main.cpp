#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "debug/debug.hpp"

#include <sstream>
#include <fstream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

GLFWwindow *win;

float verticles[] = {
    //position              color
    -0.5f, +0.5f, +0.0f,    0.4f, 0.6f, 0.2f,
    -0.5f, -0.5f, +0.0f,    0.2f, 0.8f, 0.0f,
    +0.5f, -0.5f, +0.0f,    0.0f, 0.0f, 0.0f,

};

glm::mat4 transform(1.0f);

unsigned int vao, vbo;
unsigned int vert, frag, shader_program;

bool psx_style = true;

void load_arg(int argc, const char *argv[])
{
    for (int i = 0; i <= argc; i++)
    {
        if (argv[i] == "--nocolor")
        {
            debug::no_color(true);
        }
        if (argv[i] == "--no-psx")
        {
            psx_style = false;
        }
    }
}

std::string read_file(std::string name)
{
    std::ifstream file{name};

    std::stringstream buffer;

    buffer << file.rdbuf();

    return buffer.str();
}

void format_verticles()
{
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticles), verticles, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);
}

void load_shaders()
{
    std::string vert_source, frag_source;
    const char *vert_code, *frag_code;

    vert_source = read_file("assets/shaders/v.vert");
    frag_source = read_file("assets/shaders/f.frag");

    vert_code = vert_source.c_str();
    frag_code = frag_source.c_str();

    int good;
    char log[512];

    // Vertex
    vert = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vert, 1, &vert_code, nullptr);
    glCompileShader(vert);

    glGetShaderiv(vert, GL_COMPILE_STATUS, &good);
    if (!good)
    {
        glGetShaderInfoLog(vert, 512, nullptr, log);
        debug::error("fail compile vertex shader\n\n" + std::string(log));
    }

    // Fragment
    frag = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(frag, 1, &frag_code, nullptr);
    glCompileShader(frag);

    glGetShaderiv(frag, GL_COMPILE_STATUS, &good);
    if (!good)
    {
        glGetShaderInfoLog(frag, 512, nullptr, log);
        debug::error("fail compile fragment shader\n\n" + std::string(log));
    }

    // Program
    shader_program = glCreateProgram();
    glAttachShader(shader_program, vert);
    glAttachShader(shader_program, frag);
    glLinkProgram(shader_program);

    glGetShaderiv(shader_program, GL_LINK_STATUS, &good);
    if (!good)
    {
        glGetShaderInfoLog(shader_program, 512, nullptr, log);
        debug::error("fail compile shader program\n\n" + std::string(log));
    }
    
    glDeleteShader(vert);
    glDeleteShader(frag);
}

void rotate(glm::mat4x4 *matrix, float angle, unsigned int direction)
{
    glm::vec3 vec;
    
    switch (direction)
    {
        case 0: vec = glm::vec3(1, 0, 0); break;
        case 1: vec = glm::vec3(0, 1, 0); break;
        case 2: vec = glm::vec3(0, 0, 1); break;
        default: return;
    }

    float timed_angle = glfwGetTime() * glm::radians(angle);
    *matrix = glm::rotate(glm::mat4(1.0), timed_angle, vec);
}

int main(int argc, const char *argv[])
{
    if (!glfwInit())
    {
        debug::error("fail init glfw");
        return 1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    win = glfwCreateWindow(800, 600, "Primitive Engine Prototipe", nullptr, nullptr);
    glfwMakeContextCurrent(win);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        debug::error("fail init glad");
        return 1;
    }

    format_verticles();
    load_shaders();

    unsigned int psx_loc;
    glUniform1i(psx_loc, psx_style);
    while (!glfwWindowShouldClose(win))
    {
        float t = glfwGetTime();
        
        glClearColor(45.f/255.f, 180.f/255.f, 200.f/255.f, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shader_program);

        rotate(&transform, 45.f, 2);

        unsigned int transform_loc = glGetUniformLocation(shader_program, "Transform");
        glUniformMatrix4fv(transform_loc, 1, GL_FALSE, glm::value_ptr(transform));

        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(win);
        glfwPollEvents();
    }
}