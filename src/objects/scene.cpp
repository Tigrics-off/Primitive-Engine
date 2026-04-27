#include "scene.hpp"
#include "core/light/light.hpp"
#include "glm/ext/vector_float3.hpp"
#include "shapes.hpp"
#include "utils/file.hpp"
#include "utils/config.hpp"

#include <string>

#include <nlohmann/json.hpp>
using json = nlohmann::json;

template<typename T>
T get(const json& j, const std::string& path, const T& reserve = T{})
{
    try 
    {
        return j.at(json::json_pointer(path)).get<T>();
    } 
    catch (...) 
    {
        return reserve;
    }
}

void apply_transform(object* obj, const json& data)
{
    glm::vec3 pos, rot, scale;
    
    pos = glm::vec3(
        get<float>(data, "/transform/position/0"),
        get<float>(data, "/transform/position/1"),
        get<float>(data, "/transform/position/2")
    );
    rot = glm::vec3(
        get<float>(data, "/transform/rotation/0"),
        get<float>(data, "/transform/rotation/1"),
        get<float>(data, "/transform/rotation/2")
    );
    scale = glm::vec3(
        get<float>(data, "/transform/scale/0", 1.0f),
        get<float>(data, "/transform/scale/1", 1.0f),
        get<float>(data, "/transform/scale/2", 1.0f)
    );
    
    obj->translate(pos.x, pos.y, pos.z);
    obj->rotate(rot.x, rot.y, rot.z);
    obj->scale(scale.x, scale.y, scale.z);
}

scene::scene(std::string path)
{
    json file = json::parse(file::read(path));

    for (auto& [name, data]: file.items())
    {
        std::string type = data["type"];

        if (type == "model")
        {
            objects[name] = new model
            (
                get<std::string>(data, "/paths/model"),
                get<std::string>(data, "/paths/col"),
                get<std::string>(data, "/paths/texture"),
                get<bool>(data, "/physics/passive"),
                get<float>(data, "/physics/mass")
            );
            
            apply_transform(objects[name], data);
        }
        if (type == "ambient")
        {
            objects[name] = new light::light
            (
                get<float>(data, "/settings/color/0"),
                get<float>(data, "/settings/color/1"),
                get<float>(data, "/settings/color/2"),
                get<float>(data, "/settings/strength")
            );
        }
        if (type == "point_light")
        {
            objects[name] = new light::point_light
            (
                get<float>(data, "/settings/color/0"),
                get<float>(data, "/settings/color/1"),
                get<float>(data, "/settings/color/2"),
                get<float>(data, "/settings/strength")
            );

            apply_transform(objects[name], data);
        }
        if (type == "spot_light")
        {
            objects[name] = new light::spot_light
            (
                get<float>(data, "/settings/color/0"),
                get<float>(data, "/settings/color/1"),
                get<float>(data, "/settings/color/2"),
                get<float>(data, "/settings/strength")
            );

            apply_transform(objects[name], data);
        }
        if (type == "cube")
        {
            objects[name] = new cube
            (
                get<std::string>(data, "/paths/texture"),
                get<bool>(data, "/physics/passive"),
                get<float>(data, "/physics/mass")
            );
            apply_transform(objects[name], data);
        }
        if (type == "camera")
        {
            custom::config conf = custom::parse_config();
            objects[name] = new camera
            (
                conf.width,
                conf.height,
                get<float>(data, "/settings/fov"),
                get<float>(data, "/settings/min"),
                get<float>(data, "/settings/max")
            );

            apply_transform(objects[name], data);
        }
    }
    if (file.contains("ph_engine"))
    {
        auto& data = file["ph_engine"];
        physics_engine = physics(
            get<float>(data, "/g"),
            get<float>(data, "/time"),
            get<float>(data, "/rest"),
            get<float>(data, "/fric"),
            get<bool>(data, "/collisions")
        );

        for (auto& [name, obj] : objects)
        {
            if (auto* shape_obj = dynamic_cast<shape*>(obj))
                physics_engine.add_object(shape_obj);
        }
    }
}

void scene::render(unsigned int shader_prog, float dt)
{
    for (auto& [name, obj]: objects)
        if (dynamic_cast<camera*>(obj))
            obj->render(shader_prog);

    for (auto& [name, obj]: objects)
        if (!dynamic_cast<camera*>(obj))
            obj->render(shader_prog);

    physics_engine.render(dt);
}

scene::proxy scene::operator[](const std::string& name)
{
    return {objects[name]};
}

scene::~scene()
{
    for (auto& [name, obj] : objects)
        delete obj;
}