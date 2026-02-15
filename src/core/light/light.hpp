#include "core/object.hpp"

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

    virtual void enable(unsigned int shader_prog);
};