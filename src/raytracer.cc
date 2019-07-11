#include <string>
#include <fstream>
#include <raytracer.h>
#include <geometry.h>
#include <sphere.h>
#include <light.h>
#include <memory>
#include <intersection.h>
#include "ray.h"

#define WIDTH 1280
#define HEIGHT 720
#define SCREEN_SIZE (WIDTH * HEIGHT)
#define FOV (M_PI / 2.0)
#define PPM_COLUMNS 3
#define BACKGROUND_COLOR Vec3f(0.1, 0.2, 0.4);

float Raytracer::dot_product(const Vec3f& vector_one, const Vec3f& vector_two) {
	return vector_one * vector_two;
}

Vec3f Raytracer::scale_vector(const Vec3f& vector, float scalar) {
	return vector * scalar;
}

Vec3f Raytracer::reflect(const Vec3f& surface_to_light, const Vec3f& surface_normal) {
	float alignment_light_direction_surface_normal = dot_product(surface_to_light, surface_normal);
	Vec3f reflection_direction = scale_vector(surface_normal, (2.0f * alignment_light_direction_surface_normal));
	reflection_direction = surface_to_light - reflection_direction;
	return reflection_direction;
}

Vec3f Raytracer::cast_ray(Ray& ray, const std::vector<Sphere>& spheres, const std::vector<Light>& lights, int depth = 0) {
    Vec3f hit_point;
	Vec3f normal;
	Material material;
    Intersection intersection(hit_point, normal, material);

	if (depth > 5 || !scene_intersect(ray, intersection, spheres)) return BACKGROUND_COLOR;

	Vec3f reflection_direction = reflect(ray.get_direction(), intersection.get_normal());
	Vec3f shifted_normal = scale_vector(intersection.get_normal(), 1e-3);
	Vec3f reflection_origin = dot_product(reflection_direction, intersection.get_normal()) < 0 ?
	        intersection.get_hit_point() - shifted_normal : intersection.get_hit_point() + shifted_normal;
	Ray reflected_ray(reflection_origin, reflection_direction);
	Vec3f reflection_color = cast_ray(reflected_ray, spheres, lights, depth + 1);

	float diffuse_light_intensity = 0;
	float specular_light_intensity = 0;
	for (Light light : lights) {
		if (is_shadowed(light, intersection, spheres)) continue;

        Vec3f light_direction = (light.get_position() - intersection.get_hit_point()).normalize();
		diffuse_light_intensity += light.get_intensity() * std::max(0.0f, dot_product(light_direction, intersection.get_normal()));
		Vec3f reflected_direction = reflect(light_direction, intersection.get_normal());
		float reflection_amount = dot_product(reflected_direction, ray.get_direction());
		specular_light_intensity += powf(std::max(0.0f, reflection_amount),
		        intersection.get_material().get_specular_exponent()) * light.get_intensity();
	}
	Vec3f diffused_lighting = intersection.get_material().get_diffuse_color();
	diffused_lighting = scale_vector(diffused_lighting, diffuse_light_intensity);
	diffused_lighting = scale_vector(diffused_lighting, intersection.get_material().get_albedo().x);
	Vec3f specular_lighting(1.0f, 1.0f, 1.0f);
	specular_lighting = scale_vector(specular_lighting, specular_light_intensity);
	specular_lighting = scale_vector(specular_lighting, intersection.get_material().get_albedo().y);
	reflection_color = scale_vector(reflection_color, intersection.get_material().get_albedo().z);
	return diffused_lighting + specular_lighting + reflection_color;
}

bool Raytracer::is_shadowed(Light& light, Intersection& intersection, const std::vector<Sphere>& spheres) {
	/* The purpose of gently shifting the origin is to avoid intersecting with our object at our origin point. */
    Vec3f light_direction = (light.get_position() - intersection.get_hit_point()).normalize();
    float light_distance = (light.get_position() - intersection.get_hit_point()).norm();

	bool light_and_normal_in_same_direction = dot_product(light_direction, intersection.get_normal()) > 0;
	Vec3f shifted_normal = scale_vector(intersection.get_normal(), 1e-3);
	Vec3f shadow_origin = light_and_normal_in_same_direction ? intersection.get_hit_point() + shifted_normal : intersection.get_hit_point() - shifted_normal;
    Ray shadow_ray(shadow_origin, light_direction);

	Vec3f shadow_point;
	Vec3f shadow_normal;
	Material tmp_material;
    Intersection shadow_hit_point(shadow_point, shadow_normal, tmp_material);
	return scene_intersect(shadow_ray, shadow_hit_point, spheres) &&
		   (shadow_hit_point.get_hit_point() - shadow_ray.get_origin()).norm() < light_distance;
}

bool Raytracer::scene_intersect(Ray& ray, Intersection& intersection, const std::vector<Sphere>& spheres) {
	float farthest_objects_distance = std::numeric_limits<float>::max();
	for (Sphere sphere : spheres) {
		float current_object_distance;
		bool object_is_rendered = sphere.ray_intersect(ray, current_object_distance);
		if (object_is_rendered && current_object_distance < farthest_objects_distance) {
			farthest_objects_distance = current_object_distance;
			intersection.set_hit_point(ray.get_origin() + (scale_vector(ray.get_direction(), current_object_distance)));
			intersection.set_normal((intersection.get_hit_point() - sphere.get_center()).normalize());
			intersection.set_material(sphere.get_material());
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
			Ray current_ray(ray_origin, direction);
			Vec3f color_result = cast_ray(current_ray, objects, lights);
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
