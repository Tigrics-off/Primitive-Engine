#pragma once
#include "graphics/mesh.hpp"
#include "utils/more.hpp"
#include "utils/file.hpp"

#include <nlohmann/json.hpp>
using json = nlohmann::json;

#include <vector>

class model : public shape
{
private:

public:
    model(std::string model_path, std::string texture_path = "assets/textures/debug/coconutvtf.jpg")
    {
        std::vector<char> file = file::read_bin(model_path);

        uint32_t json_len = *(uint32_t*)(file.data() + 12);
        uint32_t bin_len = *(uint32_t*)(file.data() + 12 + 8 + json_len);

        std::string json_data(file.data() + 20, json_len);
        json metadata = json::parse(json_data);
        
        char *bin_start = file.data() + 20 + json_len + 8;
        
        std::vector<float> pos, uv;

        for (auto& mesh : metadata["meshes"])
        {
            for (auto& prim : mesh["primitives"])
            {
                int pos_idx = prim["attributes"]["POSITION"];
                int uv_idx = prim["attributes"]["TEXCOORD_0"];
                int idx_idx = prim["indices"];
                
                auto pos_acc = metadata["accessors"][pos_idx];
                auto uv_acc = metadata["accessors"][uv_idx];
                auto idx_acc = metadata["accessors"][idx_idx];
                
                int pos_view = pos_acc["bufferView"];
                int pos_offset = metadata["bufferViews"][pos_view]["byteOffset"];
                int pos_count = pos_acc["count"];
                float* pos_src = (float*)(bin_start + pos_offset);
                
                int uv_view = uv_acc["bufferView"];
                int uv_offset = metadata["bufferViews"][uv_view]["byteOffset"];
                int uv_count = uv_acc["count"];
                float* uv_src = (float*)(bin_start + uv_offset);
                
                int idx_view = idx_acc["bufferView"];
                int idx_offset = metadata["bufferViews"][idx_view]["byteOffset"];
                int idx_count = idx_acc["count"];
                uint16_t* idx_src = (uint16_t*)(bin_start + idx_offset);
                
                for (int i = 0; i < idx_count; i += 3)
                {
                    for (int j = 0; j < 3; j++)
                    {
                        int id = idx_src[i + j];
                        vertices.push_back(pos_src[id * 3]);
                        vertices.push_back(pos_src[id * 3 + 1]);
                        vertices.push_back(pos_src[id * 3 + 2]);
                        vertices.push_back(uv_src[id * 2]);
                        vertices.push_back(uv_src[id * 2 + 1]);
                        queue.push_back(queue.size());
                    }
                }
            }
        }

        setup();
        set_texture(texture_path);
    }
};