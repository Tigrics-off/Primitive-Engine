#pragma once
#include <objects/object.hpp>
#include <cstdint>

class light : public object
{
protected:
	glm::vec3 _color{ 0, 0, 0 };
public:
	light(uint8_t red = 0, uint8_t green = 0, uint8_t blue = 0);

	glm::vec3 color() const;
	void set_color(uint8_t red = 0, uint8_t green = 0, uint8_t blue = 0);

	void render(shaders& shader) override;
};
