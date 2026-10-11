#pragma once
#include "mesh.hpp"
#include <utils/debug.hpp>
#include <utils/placeholders.hpp>
#include <string>
#define TINYOBJLOADER_DISABLE_FAST_FLOAT
#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>
#include <vector>
#include <filesystem>

class custom_mesh : public mesh
{
private:
    std::string model_p;
public:
    custom_mesh(std::string model_path = "", std::string texture_path = "")
    {
        model_p = model_path;
        set_figure();
        set_buff();
        set_texture(texture_path);
    }
    void set_figure() override
    {
        if (!std::filesystem::exists(model_p))
        {
            debug::warn("Failed load model \"{}\". He will replaced to debug model", model_p);
            if (std::filesystem::exists(PLACEHOLDER_MODEL))
                model_p = PLACEHOLDER_MODEL;
            else
                debug::error("Failed load debug model");
        }
        tinyobj::attrib_t attr;
        std::vector<tinyobj::shape_t> shapes;
        std::vector<tinyobj::material_t> mats;
        std::string  errs;
        if (!tinyobj::LoadObj(&attr, &shapes, &mats, &errs, model_p.c_str()))
            debug::error("{}", errs);



        for (tinyobj::shape_t &shape : shapes)
        {
            tinyobj::mesh_t &mesh = shape.mesh;
            for (tinyobj::index_t i : mesh.indices)
            {
                vert.push_back(attr.vertices[i.vertex_index * 3]);
                vert.push_back(attr.vertices[i.vertex_index * 3 + 1]);
                vert.push_back(attr.vertices[i.vertex_index * 3 + 2]);

                if (i.texcoord_index >= 0)
                {
                    vert.push_back(attr.texcoords[i.texcoord_index * 2]);
                    vert.push_back(attr.texcoords[i.texcoord_index * 2 + 1]);
                } 
                else 
                {
                    vert.push_back(0.0f);
                    vert.push_back(0.0f);
                }
            
                idx.push_back(static_cast<unsigned int>(idx.size()));
            }
        }

    }
};