#ifndef RAYTRACER_SPHERE_HH
#define RAYTRACER_SPHERE_HH

#include "Geometry.hh"
#include "IWorldObject.hh"

class Sphere : IWorldObject {
	Vec3f center;
	float radius;
public:
	Sphere(const Vec3f& center, const float& radius) : center(center), radius(radius) {}

	bool ray_intersect(const Vec3f& ray_origin, const Vec3f& direction, float& t0) const {
		Vec3f ray_to_sphere = this->get_center() - ray_origin;
		float tca = ray_to_sphere * direction;
		float d2 = ray_to_sphere * ray_to_sphere - tca * tca;
		if (d2 > radius * radius) return false;
		float thc = sqrtf(radius * radius - d2);
		t0 = tca - thc;
		float t1 = tca + thc;
		if (t0 < 0) {
			t0 = t1;
			return false;
		}
		return true;
	}
	const Vec3f &get_center() const {
		return this->center;
	}
	void set_center(const Vec3f& new_center) {
		this->center = new_center;
	}
	float get_radius() const {
		return this->radius;
	}
	void set_radius(float new_radius) {
		this->radius = new_radius;
	}
};

#endif /* RAYTRACER_SPHERE_HH */
