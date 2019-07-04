#ifndef RAYTRACER_SPHERE_HH
#define RAYTRACER_SPHERE_HH

#include <Geometry.hh>
#include <IWorldObject.hh>

class Sphere : IWorldObject {
	Vec3f center;
	float radius;
public:
	Sphere(const Vec3f& center, const float& radius) : center(center), radius(radius) {}
	bool ray_intersect(const Vec3f& ray_origin, const Vec3f& direction, float& object_distance) const;
};

#endif /* RAYTRACER_SPHERE_HH */
