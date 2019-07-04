#include <string>
#include <Raytracer.hh>
#include <Geometry.hh>
#include <Sphere.hh>
#include <fstream>

#define WIDTH 1280
#define HEIGHT 720
#define SCREEN_SIZE (WIDTH * HEIGHT)
#define FOV (M_PI / 2.0)
#define BACKGROUND_COLOR Vec3f(0.2, 0.7, 0.8)
#define GREEN Vec3f(0, 1, 0)
#define PPM_COLUMNS 3

Vec3f Raytracer::cast_ray(const Vec3f& ray_origin, const Vec3f& direction, const Sphere& object) {
	float object_distance = std::numeric_limits<float>::max();
	if (!object.ray_intersect(ray_origin, direction, object_distance)) {
		return BACKGROUND_COLOR;
	}
	return GREEN;
}

void Raytracer::render(const Sphere& object) {
	std::vector<Vec3f> framebuffer(SCREEN_SIZE);
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			float ray_x = (2 * (j + 0.5) / (float) WIDTH - 1) * tan(FOV / 2.0) * WIDTH / (float) HEIGHT;
			float ray_y = -(2 * (i + 0.5) / (float) HEIGHT - 1) * tan(FOV / 2.0);

			Vec3f direction = Vec3f(ray_x, ray_y, -1).normalize();
			Vec3f color_result = cast_ray(Vec3f(0, 0, 0), direction, object);
			framebuffer[j + (i * WIDTH)] = color_result;
		}
	}
	write_to_file(framebuffer);
}

void Raytracer::write_to_file(std::vector<Vec3f> framebuffer) {
	std::ofstream out("output.ppm");
	out << "P6\n" << WIDTH << " " << HEIGHT << "\n255\n";
	for (int i = 0; i < SCREEN_SIZE; i++) {
		for (int j = 0; j < PPM_COLUMNS; j++) {
			out << (char) (255 * std::max(0.0f, std::min(1.0f, framebuffer[i][j])));
		}
	}
	out.close();
}
