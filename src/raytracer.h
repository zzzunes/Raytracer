#ifndef RAYTRACER_RAYTRACER_H
#define RAYTRACER_RAYTRACER_H

#include <sphere.h>
#include <light.h>
#include <intersection.h>
#include <ray.h>

extern std::vector<Sphere> objects;
extern std::vector<Light> lights;

class Raytracer {
private:
	static Vec3f reflect(const Vec3f& surface_to_light, const Vec3f& surface_normal);
	static Vec3f cast_ray(Ray& ray, int depth);
	static bool is_shadowed(Light& light, Intersection& intersection, const std::vector<Sphere>& spheres);
	static bool scene_intersect(Ray& ray, Intersection& intersection, const std::vector<Sphere>& spheres);
	static void adjust_color_intensity(Vec3f& color_values);
	static void write_to_file(std::vector<Vec3f>& framebuffer);
public:
	Raytracer() = default;
	static void* find_color(void* args);
	static void render();
	static float dot_product(const Vec3f& vector_one, const Vec3f& vector_two);
	static Vec3f scale_vector(const Vec3f& vector, float scalar);
};

#endif /*RAYTRACER_RAYTRACER_H*/
