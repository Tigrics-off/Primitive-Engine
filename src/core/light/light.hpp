#pragma once
#include "core/object.hpp"

namespace light
{
    class light : public object
    {
    private:
        glm::vec3 color{1.0}, direction{0, 0, -1};
        float strength = 0.1;
    public:
        light(float r, float g, float b, float strength);

        void set_color(float x, float y, float z);
        void set_strength(float value);

        void rotate(float x, float y, float z) override;

        glm::vec3 get_color();
        glm::vec3 get_direction();
        float get_strength();

        void render(unsigned int shader_prog) override;
    };

    class point_light : public light
    {
    public:
        point_light(float r = 1.0, float g = 1.0, float b = 1.0, float strength = 1.0);
        void render(unsigned int shader_prog) override;
    };

    class spot_light : public light
    {
    private:
        float min_angle = 30, max_angle = 60;
    public:
        void set_min_angle(float value);
        void set_max_angle(float value);

        float get_min_angle();
        float get_max_angle();

        spot_light(float r = 1.0, float g = 1.0, float b = 1.0, float strength = 1.0);
        void render(unsigned int shader_prog);
    };
}