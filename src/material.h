#ifndef RAYTRACER_MATERIAL_H
#define RAYTRACER_MATERIAL_H

#include <geometry.h>

class Material {
	Vec3f diffuse_color;
public:
	Material(const Vec3f& color) : diffuse_color(color) {}
	Material() : diffuse_color() {}
	Vec3f& get_diffuse_color() {
		return this->diffuse_color;
	}
};

#endif /*RAYTRACER_MATERIAL_H*/
