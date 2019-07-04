#ifndef RAYTRACER_RAYTRACER_HH
#define RAYTRACER_RAYTRACER_HH

#include <Sphere.hh>

class Raytracer {
private:
	static Vec3f cast_ray(const Vec3f& ray_origin, const Vec3f& direction, const std::vector<Sphere>& objects);
	static bool scene_intersect(const Vec3f& ray_origin, const Vec3f& direction, const std::vector<Sphere>& objects, Vec3f& hit, Vec3f& normal, Material& material);
	static void write_to_file(std::vector<Vec3f> framebuffer);
public:
	Raytracer() = default;
	void render(const std::vector<Sphere>& objects);
};

#endif /* RAYTRACER_RAYTRACER_HH */
