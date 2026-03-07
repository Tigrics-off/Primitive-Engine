#pragma once
#include <map>
#include "core/object.hpp"
#include <string>

class scene
{
private:
    std::map<std::string, object*> objects;
    struct proxy
    {
        object* obj;
        
        template<typename T>
        operator T*() {return dynamic_cast<T*>(obj);}
        
        template<typename T>
        operator T&() {return dynamic_cast<T&>(*obj);}
    };
public:
    scene(std::string path);
    ~scene();
    void render(unsigned int shader_prog);
    proxy operator[](const std::string& name);

};