#ifndef RAYTRACER_SPHERE_HH
#define RAYTRACER_SPHERE_HH

#include <Geometry.hh>
#include <IWorldObject.hh>
#include <Material.hh>

class Sphere : IWorldObject {
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

#endif /* RAYTRACER_SPHERE_HH */
