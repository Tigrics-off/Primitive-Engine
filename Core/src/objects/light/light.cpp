#include "light.hpp"

light::light(uint8_t red, uint8_t green, uint8_t blue)
	: _color(glm::vec3(red / 255.f, green / 255.f, blue / 255.f))
{}

glm::vec3 light::color() const { return _color; }

void light::set_color(uint8_t red, uint8_t green, uint8_t blue)
{
	_color = glm::vec3(red / 255.f, green / 255.f, blue / 255.f);
}

void light::render(shaders& shader)
{
	shader.set_vec3("am_color", _color);
}