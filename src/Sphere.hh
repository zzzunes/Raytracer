#ifndef RAYTRACER_SPHERE_HH
#define RAYTRACER_SPHERE_HH

#include "geometry.hh"

class Sphere {
	Vec3f center;
	float radius;
public:
	Sphere(const Vec3f& center, const float& radius) : center(center), radius(radius) {}

	bool ray_intersect(const Vec3f& origin, const Vec3f& direction, float &t0);
	const Vec3f &getCenter() const {
		return this->center;
	}
	void setCenter(const Vec3f& new_center) {
		this->center = new_center;
	}
	float getRadius() const {
		return this->radius;
	}
	void setRadius(float new_radius) {
		this->radius = new_radius;
	}
};

#endif /* RAYTRACER_SPHERE_HH */
