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

Vec3f Raytracer::scale_vector(const Vec3f& vector, const float& scalar) {
	return vector * scalar;
}

Vec3f Raytracer::reflect(const Vec3f& surface_to_light, const Vec3f& surface_normal) {
	float alignment_light_direction_surface_normal = dot_product(surface_to_light, surface_normal);
	Vec3f reflection_direction = scale_vector(surface_normal, (2.0f * alignment_light_direction_surface_normal));
	reflection_direction = surface_to_light - reflection_direction;
	return reflection_direction;
}

Vec3f Raytracer::cast_ray(const Vec3f& ray_origin, const Vec3f& direction, const std::vector<Sphere>& spheres, const std::vector<Light>& lights) {
	Vec3f point;
	Vec3f normal;
	Material material;

	if (!scene_intersect(ray_origin, direction, spheres, point, normal, material)) return BACKGROUND_COLOR;

	float diffuse_light_intensity = 0;
	float specular_light_intensity = 0;
	for (Light light : lights) {
		Vec3f light_direction = (light.get_position() - point).normalize();
		diffuse_light_intensity += light.get_intensity() * std::max(0.0f, dot_product(light_direction, normal));
		Vec3f reflected_direction = reflect(light_direction, normal);
		float reflection_amount = dot_product(reflected_direction, direction);
		specular_light_intensity += powf(std::max(0.0f, reflection_amount), material.get_specular_exponent()) * light.get_intensity();
	}
	Vec3f diffused_lighting = material.get_diffuse_color();
	diffused_lighting = scale_vector(diffused_lighting, diffuse_light_intensity);
	diffused_lighting = scale_vector(diffused_lighting, material.get_albedo().x);
	Vec3f specular_lighting(1.0f, 1.0f, 1.0f);
	specular_lighting = scale_vector(specular_lighting, specular_light_intensity);
	specular_lighting = scale_vector(specular_lighting, material.get_albedo().y);
	return diffused_lighting + specular_lighting;
}

bool Raytracer::scene_intersect(const Vec3f& ray_origin, const Vec3f& direction, const std::vector<Sphere>& spheres, Vec3f& hit, Vec3f& normal, Material& material) {
	float farthest_objects_distance = std::numeric_limits<float>::max();
	for (Sphere sphere : spheres) {
		float current_object_distance;
		bool object_is_rendered = sphere.ray_intersect(ray_origin, direction, current_object_distance);
		if (object_is_rendered && current_object_distance < farthest_objects_distance) {
			farthest_objects_distance = current_object_distance;
			hit = ray_origin + (scale_vector(direction, current_object_distance));
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

			Vec3f ray_origin(0, 0, 0);
			Vec3f direction = Vec3f(ray_x, ray_y, -1).normalize();
			Vec3f color_result = cast_ray(ray_origin, direction, objects, lights);
			framebuffer[j + (i * WIDTH)] = color_result;
		}
	}
	write_to_file(framebuffer);
}

void Raytracer::adjust_color_intensity(Vec3f& color_values) {
	float strongest_color = std::max(color_values.x, std::max(color_values.y, color_values.z));
	if (strongest_color > 1) color_values = color_values * (1.0f / strongest_color);
}

void Raytracer::write_to_file(std::vector<Vec3f>& framebuffer) {
	std::ofstream out("output.ppm");
	out << "P6\n" << WIDTH << " " << HEIGHT << "\n255\n";
	for (int i = 0; i < SCREEN_SIZE; i++) {
		adjust_color_intensity(framebuffer[i]);
		for (int j = 0; j < PPM_COLUMNS; j++) {
			out << (char) (255 * std::max(0.0f, std::min(1.0f, framebuffer[i][j])));
		}
	}
	out.close();
}
