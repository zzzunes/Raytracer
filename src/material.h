#ifndef RAYTRACER_MATERIAL_H
#define RAYTRACER_MATERIAL_H

#include <geometry.h>

class Material {
	Vec3f diffuse_color;
	Vec3f albedo;
	float specular_exponent;
public:
	Material(const Vec3f& color, const Vec3f& albedo, const float& specular_exponent)
				: diffuse_color(color), albedo(albedo), specular_exponent(specular_exponent) {}
	Material() : diffuse_color(), albedo(1, 0, 0), specular_exponent() {}

	Vec3f& get_diffuse_color() {
		return this->diffuse_color;
	}
	Vec3f& get_albedo() {
		return this->albedo;
	}
	float& get_specular_exponent() {
		return this->specular_exponent;
	}
};

#endif /*RAYTRACER_MATERIAL_H*/
