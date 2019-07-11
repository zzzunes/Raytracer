#include <gtest/gtest.h>
#include <raytracer.h>
#include <sphere.h>

Material mirror(Vec3f(1.0, 1.0, 1.0), Vec3f(0, 10.0, 0.8), 1425.0f);

TEST(Raytracer_tests, RaytracerCreation_ReturnsValid) {
	std::unique_ptr<Raytracer> raytracer = std::make_unique<Raytracer>();
	ASSERT_NE(raytracer.get(), nullptr);
}

TEST(RayIntersect_tests, RayDefiniteMiss_ReturnsFalse) {
	Vec3f origin(0, 0, 0);
	Vec3f direction(-.37, 0, -1);
	direction.normalize();
	float object_distance = std::numeric_limits<float>::max();
	Sphere sphere(Vec3f(-6, 0, -10), 2, mirror);
	bool would_render = sphere.ray_intersect(origin, direction, object_distance);
	ASSERT_FALSE(would_render);
}

TEST(RayIntersect_tests, RayDirectHit_ReturnsTrue) {
	Vec3f origin(0, 0, 0);
	Vec3f direction(-.67, 0, -1);
	direction.normalize();
	float object_distance = std::numeric_limits<float>::max();
	Sphere sphere(Vec3f(-6, 0, -10), 2, mirror);
	bool would_render = sphere.ray_intersect(origin, direction, object_distance);
	ASSERT_TRUE(would_render);
}

TEST(RayIntersect_tests, RayDirectHit2_ReturnsTrue) {
	Vec3f origin(0, 0, 0);
	Vec3f direction(-.47, 0, -1);
	direction.normalize();
	float object_distance = std::numeric_limits<float>::max();
	Sphere sphere(Vec3f(-6, 0, -10), 2, mirror);
	bool would_render = sphere.ray_intersect(origin, direction, object_distance);
	ASSERT_TRUE(would_render);
}
