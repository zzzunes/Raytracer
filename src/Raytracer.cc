#include <string>
#include <Raytracer.hh>
#include <Geometry.hh>
#include <Sphere.hh>
#include <fstream>

#define WIDTH 1024
#define HEIGHT 768
#define FOV (M_PI / 2.0)
#define BACKGROUND_COLOR Vec3f(0.2, 0.7, 0.8)
#define GREEN Vec3f(0, 1, 0)

Vec3f Raytracer::cast_ray(const Vec3f& ray_origin, const Vec3f& direction, const Sphere& object) {
	float object_distance = std::numeric_limits<float>::max();
	if (!object.ray_intersect(ray_origin, direction, object_distance)) {
		return BACKGROUND_COLOR;
	}
	return GREEN;
}

void Raytracer::render(const Sphere& object) {
	std::vector<Vec3f> framebuffer(WIDTH * HEIGHT);
	for (size_t i = 0; i < HEIGHT; i++) {
		for (size_t j = 0; j < WIDTH; j++) {
			float x = (2 * (j + 0.5) / (float) WIDTH - 1) * tan(FOV / 2.0)
						* WIDTH / (float) HEIGHT;
			float y = -(2 * (i + 0.5) / (float) HEIGHT - 1) * tan(FOV / 2.0);
			Vec3f direction = Vec3f(x, y, -1).normalize();
			framebuffer[j + (i * WIDTH)] = cast_ray(Vec3f(0, 0, 0), direction, object);
		}
	}
	write_to_file(framebuffer);
}

void Raytracer::write_to_file(std::vector<Vec3f> framebuffer) {
	std::ofstream out("output.ppm");
	out << "P6\n" << WIDTH << " " << HEIGHT << "\n255\n";
	for (size_t i = 0; i < WIDTH * HEIGHT; i++) {
		for (size_t j = 0; j < 3; j++) {
			out << (char) (255 * std::max(0.0f, std::min(1.0f, framebuffer[i][j])));
		}
	}
	out.close();
}
