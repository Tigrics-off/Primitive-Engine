#pragma once
#include "light.hpp"

class point_light : public light
{
protected:
	float _min_dis = 0.1f, _max_dis = 10.f, _power = 1;
public:
	point_light
	(
		uint8_t red = 0,
		uint8_t green = 0,
		uint8_t blue = 0,
		float min = 0.1,
		float max = 10,
		float power = 1
	);

	float min_dis() const;
	float max_dis() const;
	float power() const;

	void set_min_dis(float val);
	void set_max_dis(float val);
	void set_power(float val);

	void render(shaders& shader) override;
};