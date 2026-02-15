#include "light.hpp"

class point_light : public light
{
private:

public:
    point_light(float r = 1.0, float g = 1.0, float b = 1.0, float strength = 1.0);
    void enable(unsigned int shader_prog) override;
};