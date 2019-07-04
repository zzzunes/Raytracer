#include <Raytracer.hh>
#include <gtest/gtest.h>

TEST(Raytracer_tests, RaytracerCreation) {
	std::unique_ptr<Raytracer> raytracer = std::make_unique<Raytracer>();
	ASSERT_NE(raytracer, nullptr);
}