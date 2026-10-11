#include "point.hpp"

point_light::point_light(uint8_t red, uint8_t green, uint8_t blue, float min, float max, float power)
	: _min_dis(min), _max_dis(max), _power(power)
{
	light::set_color(red, green, blue);
}

float point_light::min_dis() const { return _min_dis; }
float point_light::max_dis() const { return _max_dis; }
float point_light::power() const { return _power; }

void point_light::set_min_dis(float val) { _min_dis = val; }
void point_light::set_max_dis(float val) { _max_dis = val; }
void point_light::set_power(float val) { _power = val; }

void point_light::render(shaders& shader)
{
	shader.set_vec3("pt_color", _color);
	shader.set_vec3("pt_pos", _pos);

	shader.set_float("pt_min_dis", _min_dis);
	shader.set_float("pt_max_dis", _max_dis);
	shader.set_float("pt_power", _power);
}