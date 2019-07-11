#ifndef RAYTRACER_RAY_H
#define RAYTRACER_RAY_H

#include <geometry.h>

class Ray {
private:
    Vec3f origin;
    Vec3f direction;
public:
    Ray(const Vec3f& origin, const Vec3f& direction) : origin(origin) , direction(direction) {};
    Vec3f& get_origin() {
        return this->origin;
    }
    Vec3f& get_direction() {
        return this->direction;
    }
};

#endif /* RAYTRACER_RAY_H */
