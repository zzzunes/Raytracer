#ifndef RAYTRACER_RAYTRACER_H
#define RAYTRACER_RAYTRACER_H

#include <sphere.h>
#include <light.h>

class Raytracer {
private:
	static Vec3f reflect(const Vec3f& surface_to_light, const Vec3f& surface_normal);
	static Vec3f cast_ray(const Vec3f& ray_origin, const Vec3f& direction, const std::vector<Sphere>& objects,  const std::vector<Light>& lights);
	static bool scene_intersect(const Vec3f& ray_origin, const Vec3f& direction, const std::vector<Sphere>& objects, Vec3f& hit, Vec3f& normal, Material& material);
	static void adjust_color_intensity(Vec3f& color_values);
	static void write_to_file(std::vector<Vec3f>& framebuffer);
public:
	Raytracer() = default;
	static void render(const std::vector<Sphere>& objects, const std::vector<Light>& lights);
	static float dot_product(const Vec3f& vector_one, const Vec3f& vector_two);
	static Vec3f scale_vector(const Vec3f& vector, const float& scalar);
};

#endif /*RAYTRACER_RAYTRACER_H*/
