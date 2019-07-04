#ifndef RAYTRACER_RAYTRACER_HH
#define RAYTRACER_RAYTRACER_HH

#include <Sphere.hh>

class Raytracer {
private:
	static Vec3f cast_ray(const Vec3f& orig, const Vec3f& dir, const Sphere& sphere);
	static void write_to_file(std::vector<Vec3f> framebuffer);
public:
	Raytracer() = default;
	void render(const Sphere& object);
};

#endif /* RAYTRACER_RAYTRACER_HH */
