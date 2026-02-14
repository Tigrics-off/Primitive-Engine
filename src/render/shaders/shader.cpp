#include <glad/glad.h>
#include <string>

#include "debug/debug.hpp"
#include "file/file.hpp"

namespace shader
{
    void load(unsigned int &shader_prog)
    {
        unsigned int vert = glCreateShader(GL_VERTEX_SHADER);
        unsigned int frag = glCreateShader(GL_FRAGMENT_SHADER);

        std::string vert_str = file::read("assets/shader/v.vert");
        std::string frag_str = file::read("assets/shader/f.frag");
        const char *vert_source = vert_str.c_str();
        const char *frag_source = frag_str.c_str();

        glShaderSource(vert, 1, &vert_source, nullptr);
        glShaderSource(frag, 1, &frag_source, nullptr);

        glCompileShader(vert);
        glCompileShader(frag);

        int good;
        char log[512];
        glGetShaderiv(vert, GL_COMPILE_STATUS, &good);
        if (!good)
        {
            glGetShaderInfoLog(vert, 512, nullptr, log);
            debug::error("Failed compile vertex shader\n" + std::string(log));
        }
        glGetShaderiv(frag, GL_COMPILE_STATUS, &good);
        if (!good)
        {
            glGetShaderInfoLog(frag, 512, nullptr, log);
            debug::error("Failed compile vertex shader\n" + std::string(log));
        }
        
        shader_prog = glCreateProgram();

        glAttachShader(shader_prog, vert);
        glAttachShader(shader_prog, frag);

        glLinkProgram(shader_prog);
        
        glGetProgramiv(shader_prog, GL_LINK_STATUS, &good);
        if (!good)
        {
            glGetProgramInfoLog(shader_prog, 512, nullptr, log);
            debug::error("Failed link shader program\n" + std::string(log));
        }

        glDeleteShader(vert);
        glDeleteShader(frag);
    }
}