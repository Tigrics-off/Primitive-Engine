#pragma once
#include "light.hpp"

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
    void enable(unsigned int shader_prog) override;
};