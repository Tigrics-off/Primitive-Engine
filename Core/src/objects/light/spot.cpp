#include "spot.hpp"
#include <glm/glm.hpp>

spot_light::spot_light(uint8_t red, uint8_t green, uint8_t blue, float min_dis, float max_dis, float angle, float power)
	: light(red, green, blue), _min_dis(min_dis), _max_dis(max_dis), _angle(angle), _power(power)
{
	update_dir();
}

float spot_light::min_dis() const { return _min_dis; }
float spot_light::max_dis() const { return _max_dis; }
float spot_light::angle() const { return _angle; }
float spot_light::power() const { return _power; }
glm::vec3 spot_light::dir() const { return _dir; }

void spot_light::set_min_dis(float val) { _min_dis = val; }
void spot_light::set_max_dis(float val) { _max_dis = val; }
void spot_light::set_angle(float val) { _angle = val; }
void spot_light::set_power(float val) { _power = val; }

void spot_light::update_dir()
{
	float pitch = glm::radians(_rot.x);
	float yaw = glm::radians(_rot.y);

	glm::vec3 result_dir
	{
		cosf(yaw) * cosf(pitch),
		sinf(pitch),
		sinf(yaw) * cosf(pitch)
	};

	_dir = glm::normalize(result_dir);
}

void spot_light::set_rot(const glm::vec3& rot)
{
	object::set_rot(rot);
	update_dir();
}
void spot_light::set_rot(float x, float y, float z)
{
	object::set_rot(x, y, z);
	update_dir();
}

void spot_light::rotate(const glm::vec3& rot)
{
	object::rotate(rot);
	update_dir();
}
void spot_light::rotate(float x, float y, float z)
{
	object::rotate(x, y, z);
	update_dir();
}

void spot_light::render(shaders& shader)
{
	shader.set_float("sp_min_dis", _min_dis);
	shader.set_float("sp_max_dis", _max_dis);
	shader.set_float("sp_angle", _angle);
	shader.set_float("sp_power", _power);

	shader.set_vec3("sp_pos", _pos);
	shader.set_vec3("sp_rot", _rot);
	shader.set_vec3("sp_dir", _dir);

	shader.set_vec3("sp_color", _color);
}