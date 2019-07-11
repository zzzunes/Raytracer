#ifndef RAYTRACER_INTERSECTION_H
#define RAYTRACER_INTERSECTION_H

#include <material.h>
#include <geometry.h>

class Intersection {
private:
    Vec3f hit_point;
    Vec3f normal;
    Material material;
public:
    Intersection(const Vec3f& hit_point, const Vec3f& normal, const Material& material)
        : hit_point(hit_point), normal(normal), material(material) {};
    Vec3f& get_hit_point() {
        return this->hit_point;
    }
    Vec3f& get_normal() {
        return this->normal;
    }
    Material& get_material() {
        return this->material;
    }
    void set_hit_point(const Vec3f& new_hit) {
        this->hit_point = new_hit;
    }
    void set_normal(const Vec3f& new_normal) {
        this->normal = new_normal;
    }
    void set_material(const Material& new_material) {
        this->material = new_material;
    }
};

#endif /*RAYTRACER_INTERSECTION_H*/
