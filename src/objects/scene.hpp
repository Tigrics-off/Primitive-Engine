#pragma once
#include <unordered_map>
#include "core/object.hpp"
#include <string>

class scene
{
private:
    std::unordered_map<std::string, object*> objects;
public:
    scene(std::string path);

    void render(unsigned int shader_prog);

    object* operator[](const std::string& name);

};