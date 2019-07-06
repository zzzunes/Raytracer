#include <geometry.h>
#include <sphere.h>
#include <raytracer.h>

bool Sphere::ray_intersect(const Vec3f& ray_origin, const Vec3f& direction, float& sphere_distance) const {
	Vec3f ray_origin_to_sphere_center = this->center - ray_origin;
	float distance = Raytracer::dot_product(ray_origin_to_sphere_center, direction);

	float hypotenuse_squared = Raytracer::dot_product(ray_origin_to_sphere_center, ray_origin_to_sphere_center);
	float distance_squared = distance * distance;
	float distance_from_ray_to_object_center = sqrtf(hypotenuse_squared - distance_squared);

	if (distance_from_ray_to_object_center > this->radius) return false;

	float distance_to_outside_of_the_sphere = this->radius - distance_from_ray_to_object_center;
	float front_hit_point = distance - distance_to_outside_of_the_sphere;
	float exit_hit_point = distance + distance_to_outside_of_the_sphere;

	sphere_distance = front_hit_point;
	bool front_hit_point_is_behind_ray = sphere_distance < 0;
	if (front_hit_point_is_behind_ray) sphere_distance = exit_hit_point;
	bool hit_point_is_in_front_of_ray = sphere_distance > 0;
	return hit_point_is_in_front_of_ray;
}

Vec3f& Sphere::get_center() {
	return this->center;
}

Material& Sphere::get_material() {
	return this->material;
}
