#include "scene.hpp"
#include "shapes.hpp"
#include "utils/file.hpp"
#include <nlohmann/json.hpp>
using json = nlohmann::json;

void apply_transform(object* obj, const json& data)
{
    glm::vec3 pos, rot, scale;
    
    pos = glm::vec3(
        data["transform"]["position"][0],
        data["transform"]["position"][1],
        data["transform"]["position"][2]
    );
    rot = glm::vec3(
        data["transform"]["rotation"][0],
        data["transform"]["rotation"][1],
        data["transform"]["rotation"][2]
    );
    scale = glm::vec3(
        data["transform"]["scale"][0],
        data["transform"]["scale"][1],
        data["transform"]["scale"][2]
    );
    
    obj->translate(pos.x, pos.y, pos.z);
    obj->rotate(rot.x, rot.y, rot.z);
    obj->scale(scale.x, scale.y, scale.z);
}

scene::scene(std::string path)
{
    json file = json::parse(file::read(path));

    for (auto& [type, data]: file.items())
    {
        std::string name = data["name"];

        if (type == "model")
        {
            objects[name] = new model
            (
                data["paths"]["glb"],
                data["paths"]["texture"]
            );

            apply_transform(objects[name], data);
        }
        if (type == "ambient")
        {
            objects[name] = new light::light
            (
                data["light_settings"]["color"][0],
                data["light_settings"]["color"][1],
                data["light_settings"]["color"][2],
                data["light_settings"]["strength"]
            );
        }
        if (type == "point_light")
        {
            objects[name] = new light::point_light
            (
                data["light_settings"]["color"][0],
                data["light_settings"]["color"][1],
                data["light_settings"]["color"][2],
                data["light_settings"]["strength"]
            );

            apply_transform(objects[name], data);
        }
        if (type == "spot_light")
        {
            objects[name] = new light::point_light
            (
                data["light_settings"]["color"][0],
                data["light_settings"]["color"][1],
                data["light_settings"]["color"][2],
                data["light_settings"]["strength"]
            );

            apply_transform(objects[name], data);
        }
        if (type == "cube")
        {
            objects[name] = new cube(
                data["texture"]
            );
            apply_transform(objects[name], data);
        }
    }
}

void scene::render(unsigned int shader_prog)
{
    for (auto& [name, obj]: objects)
    {
        
    }
}