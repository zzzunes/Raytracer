#ifndef RAYTRACER_LIGHT_HH
#define RAYTRACER_LIGHT_HH

#include <Geometry.hh>

class Light {
private:
	Vec3f position;
	float intensity;
public:
	Light(const Vec3f& position, const float& intensity) : position(position), intensity(intensity) {}
	Vec3f& get_position() {
		return this->position;
	}
	float& get_intensity() {
		return this->intensity;
	}
};

#endif /* RAYTRACER_LIGHT_HH */
