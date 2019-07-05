#ifndef RAYTRACER_SPHERE_H
#define RAYTRACER_SPHERE_H

#include <geometry.h>
#include <material.h>

class Sphere {
	Vec3f center;
	float radius;
	Material material;
public:
	Sphere(const Vec3f& center, const float& radius, const Material& material)
		: center(center), radius(radius), material(material) {}
	bool ray_intersect(const Vec3f& ray_origin, const Vec3f& direction, float& object_distance) const;
	Vec3f& get_center();
	Material& get_material();
};

#endif /*RAYTRACER_SPHERE_H*/
