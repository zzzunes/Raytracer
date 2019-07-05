#include <geometry.h>
#include <sphere.h>

bool Sphere::ray_intersect(const Vec3f& ray_origin, const Vec3f& direction, float& object_distance) const {
	Vec3f ray_origin_to_object_center = this->center - ray_origin;
	float hypotenuse_squared = ray_origin_to_object_center * ray_origin_to_object_center;
	float distance_line = ray_origin_to_object_center * direction;
	float distance_squared = distance_line * distance_line;
	float distance_from_ray_to_object = sqrtf(hypotenuse_squared - distance_squared);

	if (distance_from_ray_to_object > this->radius) return false;

	float hit_distance_from_center = this->radius - distance_from_ray_to_object;
	float hit_point_distance = distance_line - hit_distance_from_center;
	object_distance = hit_point_distance;
	float inside_point = distance_line + hit_distance_from_center;
	if (object_distance < 0) object_distance = inside_point;
	return object_distance > 0;
}

Vec3f& Sphere::get_center() {
	return this->center;
}

Material& Sphere::get_material() {
	return this->material;
}
