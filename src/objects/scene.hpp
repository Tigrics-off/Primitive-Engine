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
        
        glm::vec3 get_pos() { return obj->get_pos(); }
        glm::vec3 get_rotate() { return obj->get_rotate(); }
        glm::vec3 get_scale() { return obj->get_scale(); }
        
        void translate(float x, float y, float z) { obj->translate(x, y, z); }
        void rotate(float x, float y, float z) { obj->rotate(x, y, z); }
        void scale(float x, float y, float z) { obj->scale(x, y, z); }
        
        void render(unsigned int shader) { obj->render(shader); }
        
        template<typename T>
        T* as() { return dynamic_cast<T*>(obj); }
    };
public:
    scene(std::string path);
    ~scene();
    void render(unsigned int shader_prog);
    proxy operator[](const std::string& name);

};