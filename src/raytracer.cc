#include <string>
#include <fstream>
#include <raytracer.h>
#include <geometry.h>
#include <sphere.h>
#include <light.h>

#define WIDTH 1280
#define HEIGHT 720
#define SCREEN_SIZE (WIDTH * HEIGHT)
#define FOV (M_PI / 2.0)
#define PPM_COLUMNS 3
#define BACKGROUND_COLOR Vec3f(0.1, 0.2, 0.5);

float Raytracer::dot_product(const Vec3f& vector_one, const Vec3f& vector_two) {
	return vector_one * vector_two;
}

Vec3f Raytracer::reflect(const Vec3f& I, const Vec3f& normal) {
	return I - normal * 2.0f * (dot_product(I, normal));
}

Vec3f Raytracer::cast_ray(const Vec3f& ray_origin, const Vec3f& direction, const std::vector<Sphere>& objects, const std::vector<Light>& lights) {
	Vec3f point;
	Vec3f normal;
	Material material;

	if(!scene_intersect(ray_origin, direction, objects, point, normal, material)) return BACKGROUND_COLOR;

	float diffuse_light_intensity = 0;
	float specular_light_intensity = 0;
	for (Light light : lights) {
		Vec3f light_direction = (light.get_position() - point).normalize();
		diffuse_light_intensity += light.get_intensity() * std::max(0.0f, dot_product(light_direction, normal));
		Vec3f reflected = -reflect(-light_direction, normal);
		float amount = dot_product(reflected, direction);
		specular_light_intensity += powf(std::max(0.0f,  amount), material.get_specular_exponent());
	}
	return material.get_diffuse_color() * diffuse_light_intensity * material.get_albedo().x +
			(Vec3f(1.0f, 1.0f, 1.0f) * specular_light_intensity * material.get_albedo().y);
}

bool Raytracer::scene_intersect(const Vec3f& ray_origin, const Vec3f& direction, const std::vector<Sphere>& spheres, Vec3f& hit, Vec3f& normal, Material& material) {
	float farthest_objects_distance = std::numeric_limits<float>::max();
	for (Sphere sphere : spheres) {
		float current_object_distance;
		bool object_is_rendered = sphere.ray_intersect(ray_origin, direction, current_object_distance);
		if (object_is_rendered && current_object_distance < farthest_objects_distance) {
			farthest_objects_distance = current_object_distance;
			hit = ray_origin + (direction * current_object_distance);
			normal = (hit - sphere.get_center()).normalize();
			material = sphere.get_material();
		}
	}
	return farthest_objects_distance < std::numeric_limits<float>::max();
}

void Raytracer::render(const std::vector<Sphere>& objects, const std::vector<Light>& lights) {
	std::vector<Vec3f> framebuffer(SCREEN_SIZE);
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			float ray_x = (2 * (j + 0.5) / (float) WIDTH - 1) * tan(FOV / 2.0) * WIDTH / (float) HEIGHT;
			float ray_y = -(2 * (i + 0.5) / (float) HEIGHT - 1) * tan(FOV / 2.0);

			Vec3f direction = Vec3f(ray_x, ray_y, -1).normalize();
			Vec3f color_result = cast_ray(Vec3f(0, 0, 0), direction, objects, lights);
			framebuffer[j + (i * WIDTH)] = color_result;
		}
	}
	write_to_file(framebuffer);
}

void Raytracer::write_to_file(std::vector<Vec3f> framebuffer) {
	std::ofstream out("output.ppm");
	out << "P6\n" << WIDTH << " " << HEIGHT << "\n255\n";
	for (int i = 0; i < SCREEN_SIZE; i++) {
		Vec3f& c = framebuffer[i];
		float max = std::max(c.x, std::max(c.y, c.z));
		if (max > 1) c = c * (1.0f / max);
		for (int j = 0; j < PPM_COLUMNS; j++) {
			out << (char) (255 * std::max(0.0f, std::min(1.0f, framebuffer[i][j])));
		}
	}
	out.close();
}
