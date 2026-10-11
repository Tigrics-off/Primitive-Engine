#include "light.hpp"

class spot_light : public light
{
protected:
	float _min_dis = 0.1, _max_dis = 10, _angle = 65, _power = 1;
	glm::vec3 _dir{ 0, 0, -1 };

	void update_dir();
public:
	spot_light
	(
		uint8_t red,
		uint8_t green,
		uint8_t blue,
		float min_dis = 0.1,
		float max_dis = 10,
		float angle = 65,
		float power = 1
	);

	float min_dis() const;
	float max_dis() const;
	float angle() const;
	float power() const;
	glm::vec3 dir() const;

	void set_min_dis(float val);
	void set_max_dis(float val);
	void set_angle(float val);
	void set_power(float val);

	void set_rot(const glm::vec3& rot) override;
	void set_rot(float x = 0, float y = 0, float z = 0) override;

	void rotate(const glm::vec3& rot) override;
	void rotate(float x = 0, float y = 0, float z = 0) override;

	void render(shaders& shader) override;
};